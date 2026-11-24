// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_TargetHasAttackSlots.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBTDecorator_TargetHasAttackSlots : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTDecorator_TargetHasAttackSlots(const FObjectInitializer& ObjectInitializer);

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
