// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TWDGameplayAbility.h"
#include "TWDDebugHelper.h"
#include "Components/BaseCombatComponent.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"

void UTWDGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Debug::Print(FString::Printf(TEXT("%s Activated "), *GetName()));
}

UTWDAbilitySystemComponent* UTWDGameplayAbility::GetTWDAbilitySystemComponent() const
{
	return Cast<UTWDAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

