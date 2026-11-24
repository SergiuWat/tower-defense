// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/BTDecorator_TargetHasAttackSlots.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/AttackSlotsComponent.h"
#include "Player/TWDAIController.h"
#include "AI/TWDAITypes.h"

UBTDecorator_TargetHasAttackSlots::UBTDecorator_TargetHasAttackSlots(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	NodeName = TEXT("Target Has Attack Slots");
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, BlackboardKey), AActor::StaticClass());
}

bool UBTDecorator_TargetHasAttackSlots::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard)) return false;


	ATWDAIController* Controller = Cast<ATWDAIController>(OwnerComp.GetAIOwner());


	const AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject(GetSelectedBlackboardKey()));
	return IsValid(Target) && IsValid(Target->FindComponentByClass<UAttackSlotsComponent>()) && IsValid(Controller) && Controller->ProfileTest.bUseEQSForStructures ;
}
