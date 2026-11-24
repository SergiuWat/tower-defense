// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_FaceTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"

UBTTask_FaceTarget::UBTTask_FaceTarget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyTick = true;
	NodeName = FString("Face Target Task");

	RotationInterpSpeed = 5.f;
	RotationToTargetDegreesThreshold = 5.f;

	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FaceTarget, BlackboardKey), AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_FaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject);

	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!IsValid(OwningPawn) || !IsValid(TargetActor))
	{
		return EBTNodeResult::Failed;
	}

	const float ToTargetYawRotation = (TargetActor->GetActorLocation() - OwningPawn ->GetActorLocation()).Rotation().Yaw;
	const float OwningPawnYawRotation = OwningPawn->GetActorRotation().Yaw;

	float RemainingYawRotation = FMath::Abs(FMath::FindDeltaAngleDegrees(OwningPawnYawRotation, ToTargetYawRotation));

	if (RemainingYawRotation <= RotationToTargetDegreesThreshold)
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_FaceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject);

	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!IsValid(OwningPawn) || !IsValid(TargetActor))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (OwningPawn && TargetActor)
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());
		const FRotator TargetRot = FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRot, DeltaSeconds, RotationInterpSpeed);

		OwningPawn->SetActorRotation(TargetRot);
	}

	if (!IsValid(OwningPawn) || !IsValid(TargetActor))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	const float ToTargetYawRotation = (TargetActor->GetActorLocation() - OwningPawn->GetActorLocation()).Rotation().Yaw;
	const float OwningPawnYawRotation = OwningPawn->GetActorRotation().Yaw;

	float RemainingYawRotation = FMath::Abs(FMath::FindDeltaAngleDegrees(OwningPawnYawRotation, ToTargetYawRotation));

	if (RemainingYawRotation <= RotationToTargetDegreesThreshold)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
