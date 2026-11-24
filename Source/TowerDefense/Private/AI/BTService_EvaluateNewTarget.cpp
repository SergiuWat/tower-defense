// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_EvaluateNewTarget.h"
#include "Player/TWDAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_EvaluateNewTarget::UBTService_EvaluateNewTarget()
{
	NodeName = TEXT("Native Evaluate New Target");

	INIT_SERVICE_NODE_NOTIFY_FLAGS();
	bNotifyTick = true;
	Interval = 0.2f;
	RandomDeviation = 0.f;

	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());

}


void UBTService_EvaluateNewTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ATWDAIController* OwnerController = Cast<ATWDAIController>(OwnerComp.GetAIOwner());

	if (OwnerController)
	{
		AActor* NewTarget = OwnerController->EvaluateNewTarget();
		UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName);
		AActor* TargetActor = Cast<AActor>(ActorObject);
		
		if (NewTarget == TargetActor) return;

		OwnerController->EmptyReservedSlot();
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("AttackLocation"));

		if (IsValid(NewTarget))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(InTargetActorKey.SelectedKeyName, NewTarget);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->ClearValue(InTargetActorKey.SelectedKeyName);
		}
	}
}

void UBTService_EvaluateNewTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetActorKey.ResolveSelectedKey(*BBAsset);
	}
}

FString UBTService_EvaluateNewTarget::GetStaticDescription() const
{
	return FString("Evaluate New Targets");
}