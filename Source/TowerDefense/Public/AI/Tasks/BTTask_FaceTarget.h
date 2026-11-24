// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FaceTarget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBTTask_FaceTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_FaceTarget(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Target")
	float RotationInterpSpeed;

	UPROPERTY(EditAnywhere, Category = "Target")
	float RotationToTargetDegreesThreshold;

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:


};
