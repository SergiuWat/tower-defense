// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_TryReserveSlot.h"
#include "Components/AttackSlotsComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"

UBTTask_TryReserveSlot::UBTTask_TryReserveSlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_TryReserveSlot, BlackboardKey));
	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_TryReserveSlot::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (!IsValid(Blackboard)) return EBTNodeResult::Failed;

	AAIController* Controller = OwnerComp.GetAIOwner();
	APawn* PawnToReserve = Controller->GetPawn();

	if (!IsValid(PawnToReserve)) return EBTNodeResult::Failed;

	const AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject(InTargetActorKey.SelectedKeyName));

	if (!IsValid(TargetActor)) return EBTNodeResult::Failed;

	if (UAttackSlotsComponent* SlotComponent = TargetActor->FindComponentByClass<UAttackSlotsComponent>())
	{
		FVector SlotLocation;
		bool bIsSlotReserved = SlotComponent->TryReserveSlotForPawn(PawnToReserve, SlotLocation);
	
		if (bIsSlotReserved)
		{
			Blackboard->SetValueAsVector(BlackboardKey.SelectedKeyName, SlotLocation);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
