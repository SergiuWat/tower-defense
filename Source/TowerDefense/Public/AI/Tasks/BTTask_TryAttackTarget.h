// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TryAttackTarget.generated.h"

struct FGameplayTag;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBTTask_TryAttackTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_TryAttackTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
	UPROPERTY(EditAnywhere, Category = "Tag")
	FGameplayTag AttackMeleeTag;
};
