// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TWDAbilitySystemComponent.h"
#include "TWDGameplayTags.h"

#include "TWDDebugHelper.h"

void UTWDAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	HandleActivateOnGiven(AbilitySpec);
}

FGameplayAbilitySpecHandle UTWDAbilitySystemComponent::GiveAbilityIfMissing(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!IsValid(AbilitySpec.Ability)) return FGameplayAbilitySpecHandle();

	if (const FGameplayAbilitySpec* ExistingSpec = FindAbilitySpecFromClass(AbilitySpec.Ability->GetClass()))
	{
		return ExistingSpec->Handle;
	}

	return GiveAbility(AbilitySpec);

}

void UTWDAbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
	if (!IsValid(GetAvatarActor()) || Level <= 0) return;

	if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass))
	{
		AbilitySpec->Level = Level;		
	}
}

void UTWDAbilitySystemComponent::AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
	if (!IsValid(GetAvatarActor()) || Level <= 0) return;

	if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass))
	{
		AbilitySpec->Level += Level;
	}
}



void UTWDAbilitySystemComponent::HandleActivateOnGiven(const FGameplayAbilitySpec & AbilitySpec)
{
	if (!IsValid(AbilitySpec.Ability)) return;

	for (const FGameplayTag& Tag : AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTagExact(TWDGameplayTags::Abilities::TWDGameplayTags_Abilities_ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);
			return;
		}
	}
	
}
