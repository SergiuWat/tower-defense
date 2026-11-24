// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TWDAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "TWDGameplayTags.h"
#include "BrainComponent.h"
#include "Utils/TWDFunctionLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Towers/StoneOfLife.h"
#include "Data/AIProfileDataBase.h"
#include "Interfaces/IActorThreatInterface.h"
#include "Interfaces/TowerStateInterface.h"
#include "Components/AttackSlotsComponent.h"

#include "TWDDebugHelper.h"

ATWDAIController::ATWDAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySensConfigSight");
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfigSight->SightRadius = 5000.f;

	//Enemies will never lose sight of our player we might want to change this
	AISenseConfigSight->LoseSightRadius = 0.f;

	//We might want to change thiss too but we need to see how it plays out
	AISenseConfigSight->PeripheralVisionAngleDegrees = 360.f;

	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyPerceptionComponent");
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	SetGenericTeamId(FGenericTeamId(1));
}

void ATWDAIController::BeginPlay()
{

	Super::BeginPlay();

	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComp->SetCrowdSimulationState(bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidanceQuality)
		{
		case 1: 
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		default:
			break;
		}

		CrowdComp->SetAvoidanceGroup(1);
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (IsValid(ASC))
	{
		ASC->RegisterGameplayTagEvent(TWDGameplayTags::State::TWDGameplayTags_State_Death, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnDeathTagReceived);
	}
}

void ATWDAIController::OnPossess(APawn* InPawn)
{

	Super::OnPossess(InPawn);

	StoneOfLife = Cast<AStoneOfLife>(UGameplayStatics::GetActorOfClass(this, AStoneOfLife::StaticClass()));

	if (!IsValid(AITestProfileDatabase)) return;
	if (!IsValid(StoneOfLife)) return;

	ProfileTest = AITestProfileDatabase->GetAIProfileTest();

	if (ProfileTest.bUseEQSForStructures)
	{
		if (UAttackSlotsComponent* AttackSlot = StoneOfLife->FindComponentByClass<UAttackSlotsComponent>())
		{
			if (AttackSlot->AreSlotsAvailable())
			{
				AddActorToPosibleTargetsList(StoneOfLife);
			}
		}
	}
	else
	{
		AddActorToPosibleTargetsList(StoneOfLife);
	}

	if (!IsValid(BehaviourTree)) return;

	RunBehaviorTree(BehaviourTree);

	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		Blackboard->SetValueAsObject(FName("TargetActor"), StoneOfLife);
	}
}

void ATWDAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!ProfileTest.bConsiderThreatLevel) return;


	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		AddActorToPosibleTargetsList(Actor);
	}
}

void ATWDAIController::OnDeathTagReceived(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount <= 0) return;

	EmptyReservedSlot();

	if (UBrainComponent* Brain = GetBrainComponent())
	{
		Brain->StopLogic(TEXT("Death"));
	}

	StopMovement();

}

AActor* ATWDAIController::EvaluateNewTarget()
{
	// We want to return from this function if the AI doesnt take into account the threat level
	// this means it will ignore all defences and the player and will only try to reach his objective in this case the stone of life
	if (ProfileTest.bConsiderThreatLevel)
	{
		AActor* BestTarget = SelectNewTarget();
		if (IsValid(BestTarget)) return BestTarget;
	}

	if (ProfileTest.bUseEQSForStructures)
	{
		if (!IsValid(StoneOfLife)) return nullptr;

		if (UAttackSlotsComponent* AttackSlot = StoneOfLife->FindComponentByClass<UAttackSlotsComponent>())
		{
			if (AttackSlot->HasSlotAlreadyReserved(GetPawn()))
			{
				return StoneOfLife.Get();
			}
			else if (!AttackSlot->AreSlotsAvailable())
			{
				return nullptr;
			}
		}
	}

	return IsValid(StoneOfLife) ? StoneOfLife.Get() : nullptr;
}

AActor* ATWDAIController::SelectNewTarget()
{
	AActor* NewTarget = nullptr;

	// we filter by attackslots if the AI profile is enable
	TArray<AActor*> TargetCandidates = ProfileTest.bUseEQSForStructures ? AttackSlotsFilter(PosibleTargets) : PosibleTargets;

	// we filter the targets by threat
	TargetCandidates = ThreatFilter(TargetCandidates);

	// we filter the targets by distance
	NewTarget = DistanceFilter(TargetCandidates);

	return NewTarget;
}

TArray<AActor*> ATWDAIController::AttackSlotsFilter(const TArray<AActor*> ListToFilter)
{
	TArray<AActor*> TargetCandidates = ListToFilter;

	for (AActor* Candidate : ListToFilter)
	{
		if (!IsValid(Candidate))
		{
			TargetCandidates.Remove(Candidate);
			continue;
		}

		if (ITowerStateInterface* TowerState = Cast<ITowerStateInterface>(Candidate))
		{
			if (TowerState->GetIsTowerDestroyed())
			{
				TargetCandidates.Remove(Candidate);
			}
		}

		if (UAttackSlotsComponent* AttackSlot = Candidate->FindComponentByClass<UAttackSlotsComponent>())
		{
			if (!AttackSlot->HasSlotAlreadyReserved(GetPawn()) && !AttackSlot->AreSlotsAvailable())
			{
				TargetCandidates.Remove(Candidate);
			}
		}
	}

	return TargetCandidates;
}

TArray<AActor*> ATWDAIController::ThreatFilter(const TArray<AActor*> ListToFilter)
{

	int CurrentThreatLevel = 0;

	TArray<AActor*> TargetCandidates;

	for (AActor* Candidate : ListToFilter)
	{
		if (!IsValid(Candidate)) continue;

		if (ITowerStateInterface* TowerState = Cast<ITowerStateInterface>(Candidate))
		{
			if (TowerState->GetIsTowerDestroyed()) continue;
		}

		if (IIActorThreatInterface* ActorThreatLevel = Cast<IIActorThreatInterface>(Candidate))
		{
			
			if (CurrentThreatLevel < ActorThreatLevel->GetThreatLevel())
			{
				CurrentThreatLevel = ActorThreatLevel->GetThreatLevel();
				TargetCandidates.Reset();
				TargetCandidates.Add(Candidate);
				continue;
			}
			else if(CurrentThreatLevel == ActorThreatLevel->GetThreatLevel())
			{
				TargetCandidates.Add(Candidate);
			}
		}
	}

	return TargetCandidates;
}

AActor* ATWDAIController::DistanceFilter(const TArray<AActor*> ListToFilter)
{
	AActor* PosibileTarget = nullptr;

	if (ListToFilter.Num() <= 0) return PosibileTarget;
	if (ListToFilter.Num() == 1) return ListToFilter[0];

	APawn* OwnerPawn = GetPawn();
	if (!IsValid(OwnerPawn)) return PosibileTarget;

	FVector ActorLocation = OwnerPawn->GetActorLocation();
	float DistanceFromTarget = MAX_flt;

	for (AActor* Candidate : ListToFilter)
	{

		if (ITowerStateInterface* TowerState = Cast<ITowerStateInterface>(Candidate))
		{
			if (TowerState->GetIsTowerDestroyed()) continue;
		}

		if (DistanceFromTarget > FVector::Distance(ActorLocation, Candidate->GetActorLocation()))
		{
			DistanceFromTarget = FVector::Distance(ActorLocation, Candidate->GetActorLocation());
			PosibileTarget = Candidate;
		}
	}
	return PosibileTarget;
}


void ATWDAIController::AddActorToPosibleTargetsList(AActor* NewActor)
{
	if (!IsValid(NewActor)) return;

	PosibleTargets.AddUnique(NewActor);
}

void ATWDAIController::RemoveActorFromPosibleTargetsList(AActor* ActorToRemove)
{
	if (!IsValid(ActorToRemove)) return;

	PosibleTargets.Remove(ActorToRemove);
}

void ATWDAIController::EmptyReservedSlot()
{
	if (ProfileTest.bUseEQSForStructures)
	{
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			AActor* CurrentTarget = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName("TargetActor")));
			if (!IsValid(CurrentTarget)) return;

			UAttackSlotsComponent* AttackSlot = CurrentTarget->FindComponentByClass<UAttackSlotsComponent>();
			if (!IsValid(AttackSlot)) return;

			AttackSlot->ReleaseSlotForPawn(GetPawn());
		}
	}	
}

ETeamAttitude::Type ATWDAIController::GetTeamAttitudeTowards(const AActor& Other) const
{

	if (UTWDFunctionLibrary::IsTargetHostile(this, &Other))
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Friendly;
}


bool ATWDAIController::ActivateAbility(const FGameplayTag& AbilityTag)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC)) return false;

	return ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());

}

void ATWDAIController::CancelAbilities(const FGameplayTagContainer& CancelAbilitiesTagContainer)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC)) return;

	ASC->CancelAbilities(&CancelAbilitiesTagContainer);
}
