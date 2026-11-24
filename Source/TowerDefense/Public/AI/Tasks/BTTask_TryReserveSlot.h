// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_TryReserveSlot.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBTTask_TryReserveSlot : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_TryReserveSlot(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Target")
	FBlackboardKeySelector InTargetActorKey;
};
