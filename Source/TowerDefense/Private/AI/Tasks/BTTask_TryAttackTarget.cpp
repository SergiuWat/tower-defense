// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_TryAttackTarget.h"
#include "AbilitySystemComponent.h"
#include "Player/TWDAIController.h"
#include "TWDGameplayTags.h"

UBTTask_TryAttackTarget::UBTTask_TryAttackTarget()
{
	NodeName = TEXT("Try Attack Target");
	
}

EBTNodeResult::Type UBTTask_TryAttackTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ATWDAIController* Controller = Cast<ATWDAIController>(OwnerComp.GetAIOwner());
	if (!IsValid(Controller)) return EBTNodeResult::Failed;

	return Controller->ActivateAbility(AttackMeleeTag) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
