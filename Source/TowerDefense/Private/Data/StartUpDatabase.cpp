// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/StartUpDatabase.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/TWDGameplayAbility.h"
#include "GameplayEffect.h"

void UStartUpDatabase::GiveToAbilitySystemComponent(UTWDAbilitySystemComponent* ASCToGive, int32 ApplyLevel)
{
	checkf(ASCToGive, TEXT("ASC is not valid In GiveToAbilitySystemComponent"));

	if (InitialAttributesEffect)
	{
		ASCToGive->TrySendIntialAttributeGameplayEffectToSelf(FGameplayEffectContextHandle(), InitialAttributesEffect, 1);
	}

	GrantAbilities(ActivateOnGivenAbilities, ASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, ASCToGive, ApplyLevel);
}

void UStartUpDatabase::GrantAbilities(const TArray<TSubclassOf<UTWDGameplayAbility>> AbilitiesToGive, UTWDAbilitySystemComponent * ASCToGive, int32 ApplyLevel)
{
	if (AbilitiesToGive.IsEmpty()) return;

	for (const TSubclassOf<UTWDGameplayAbility>& Ability : AbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = ASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		ASCToGive->GiveAbilityIfMissing(AbilitySpec);
	}
}
