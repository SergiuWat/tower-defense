// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Utils/TWDFunctionLibrary.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "TWDGameplayTags.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/AttributeSets/TWDHealthSet.h"
#include "UI/EnemiesResourcesBar.h"
#include "Components/AttackSlotsComponent.h"
#include "Components/StructureDestructionComponent.h"

ATowerBase::ATowerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capseule Component");
	SetRootComponent(CapsuleComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Tower Mesh");
	MeshComponent->SetupAttachment(GetRootComponent());

	GlobeVFXPosition = CreateDefaultSubobject<USceneComponent>("Globe Position");
	GlobeVFXPosition->SetupAttachment(MeshComponent);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Tower Range Collision");
	SphereCollision->SetupAttachment(GetRootComponent());
	
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

	GlobeNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("Globe Niagara Component");
	GlobeNiagaraComponent->SetupAttachment(GlobeVFXPosition);

	LaserNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("Laser Niagara Component");
	LaserNiagaraComponent->SetupAttachment(GlobeVFXPosition);

	LaserNiagaraComponent->SetAutoActivate(false);

	LaserHitNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("Laser Hit Niagara Component");
	LaserHitNiagaraComponent->SetAutoActivate(false);

	AbilitySystemComponent = CreateDefaultSubobject<UTWDAbilitySystemComponent>("AbilitySystemComponent");

	StructureDestructionComponent = CreateDefaultSubobject<UStructureDestructionComponent>("Structure Destruction Component");

	HealthSet = CreateDefaultSubobject<UTWDHealthSet>("HealthSet");

	AttackSlots = CreateDefaultSubobject<UAttackSlotsComponent>("AttackSlotsComponent");

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("ResourcesBar");
	WidgetComponent->SetupAttachment(GetRootComponent());

	TowerTeamID = FGenericTeamId(0);
}

void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(TWDGameplayTags::Event::TWDGameplayTags_Event_Death).AddUObject(this, &ATowerBase::OnTowerDestruction);

	if (InitialAttributesEffect)
	{
		AbilitySystemComponent->TrySendIntialAttributeGameplayEffectToSelf(FGameplayEffectContextHandle(), InitialAttributesEffect, 1);	
	}

	WidgetComponent->InitWidget();


	if (UEnemiesResourcesBar* ResourceWidget = Cast<UEnemiesResourcesBar>(WidgetComponent->GetUserWidgetObject()))
	{
		ResourceWidget->InitializeWithASC(AbilitySystemComponent);
	}

	if (IsValid(GlobeVFX))
	{
		GlobeNiagaraComponent->SetAsset(GlobeVFX);
		
		GlobeNiagaraComponent->Activate();
	}

	if (IsValid(LaserVFX))
	{
		LaserNiagaraComponent->SetAsset(LaserVFX);
	}

	if (IsValid(LaserHitVFX))
	{
		LaserHitNiagaraComponent->SetAsset(LaserHitVFX);
	}

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ATowerBase::OnOverlapEnd);
}

void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTarget.IsValid())
	{
		LaserNiagaraComponent->SetNiagaraVariableVec3(FString("User.LaserEnd"), FVector(CurrentTarget->GetActorLocation()));
		LaserHitNiagaraComponent->SetWorldLocation(CurrentTarget->GetActorLocation());
	}

}


UAbilitySystemComponent* ATowerBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATowerBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor)) return;

	if (UTWDFunctionLibrary::IsTargetHostile(this, OtherActor))
	{
		EnemiesInRange.AddUnique(OtherActor);

		if (!CurrentTarget.IsValid())
		{
			SelectNewTarget();
		}
	}
}

void ATowerBase::OnTowerDestruction(const FGameplayEventData* Payload)
{
	if (bIsTowerDestroyed) return;
	bIsTowerDestroyed = true;

	UnbindTargetASC();
	CurrentTarget.Reset();
	EnemiesInRange.Reset();
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GlobeNiagaraComponent->Deactivate();
	LaserNiagaraComponent->Deactivate();
	LaserHitNiagaraComponent->Deactivate();

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetVisibility(false);

	WidgetComponent->SetVisibility(false);

	StructureDestructionComponent->BeginDestruction(MeshComponent);

}

void ATowerBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UTWDFunctionLibrary::IsTargetHostile(this, OtherActor))
	{
		EnemiesInRange.Remove(OtherActor);

		if (CurrentTarget == OtherActor)
		{
			UnbindTargetASC();
			SelectNewTarget();
		}
	}
}

TWeakObjectPtr<AActor> ATowerBase::GetRandomTargetFromTargetsInRange()
{
	if (EnemiesInRange.Num() <= 0) return nullptr;
	if (EnemiesInRange.Num() == 1) return EnemiesInRange[0].IsValid() ? EnemiesInRange[0] : nullptr;

	TWeakObjectPtr<AActor> NewTarget = EnemiesInRange[FMath::RandRange(0, EnemiesInRange.Num() - 1)];
	return NewTarget.IsValid() ? NewTarget : nullptr;

}

void ATowerBase::OnTargetDeathEventReceived(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount <= 0) return;

	EnemiesInRange.Remove(CurrentTarget);
	UnbindTargetASC();
	SelectNewTarget();
}

void ATowerBase::SelectNewTarget()
{
	if (bIsTowerDestroyed) return;

	LaserHitNiagaraComponent->Deactivate();
	LaserNiagaraComponent->Deactivate();
	CurrentTarget = GetRandomTargetFromTargetsInRange();
	if (!CurrentTarget.IsValid()) return;

	TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(CurrentTarget.Get());

	if (IsValid(TargetASC))
	{
		DeathEventDelegate = TargetASC->RegisterGameplayTagEvent(TWDGameplayTags::State::TWDGameplayTags_State_Death, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ATowerBase::OnTargetDeathEventReceived);
	}

	GetWorld()->GetTimerManager().SetTimer(TickDamageHandle, this, &ATowerBase::TryDoDamage, DamgePerSecond, true);

	LaserNiagaraComponent->Activate();
	LaserHitNiagaraComponent->Activate();

	LaserNiagaraComponent->SetNiagaraVariableVec3(FString("User.LaserEnd"), FVector(CurrentTarget->GetActorLocation()));
	LaserHitNiagaraComponent->SetWorldLocation(CurrentTarget->GetActorLocation());
}


void ATowerBase::UnbindTargetASC()
{
	GetWorld()->GetTimerManager().ClearTimer(TickDamageHandle);
	if (IsValid(TargetASC))
	{
		TargetASC->RegisterGameplayTagEvent(TWDGameplayTags::State::TWDGameplayTags_State_Death, EGameplayTagEventType::NewOrRemoved).Remove(DeathEventDelegate);
		DeathEventDelegate.Reset();
		TargetASC = nullptr;
	}
}

void ATowerBase::TryDoDamage()
{
	if (!IsValid(TargetASC) || !CurrentTarget.IsValid()) return;

	FGameplayEffectContextHandle ContextHandle;

	ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1, ContextHandle);

	if (!SpecHandle.IsValid()) return;
	SpecHandle.Data->SetSetByCallerMagnitude(TWDGameplayTags::Tower::Data::TWDGameplayTags_Tower_Data_Damage, Damage);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
}

FGenericTeamId ATowerBase::GetGenericTeamId() const
{
	return TowerTeamID;
}

int32 ATowerBase::GetThreatLevel() const
{
	return ThreatLevel;
}

bool ATowerBase::GetIsTowerDestroyed() const
{
	return bIsTowerDestroyed;
}

