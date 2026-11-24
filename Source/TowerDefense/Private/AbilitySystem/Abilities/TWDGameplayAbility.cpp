// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TWDGameplayAbility.h"
#include "TWDDebugHelper.h"
#include "Components/BaseCombatComponent.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"

void UTWDGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//Debug::Print(FString::Printf(TEXT("%s Activated "), *GetName()));
}

UTWDAbilitySystemComponent* UTWDGameplayAbility::GetTWDAbilitySystemComponent() const
{
	return Cast<UTWDAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

void UTWDGameplayAbility::TrySendGameplayEffectToActor(UAbilitySystemComponent* TargetASC, FGameplayEffectContextHandle Context, TSubclassOf<UGameplayEffect> GameplayEffect, const FGameplayTag& EffectTag, float Magnitude)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();

	if (!IsValid(ASC) || !IsValid(TargetASC) || !EffectTag.IsValid() || !IsValid(GameplayEffect)) return;

	FGameplayEffectContextHandle ContextHandle = Context;

	if (!ContextHandle.IsValid())
	{
		ContextHandle = ASC->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
	}

	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffect, GetAbilityLevel(), ContextHandle);

	if (!SpecHandle.IsValid()) return;

	SpecHandle.Data->SetSetByCallerMagnitude(EffectTag, Magnitude);
	ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);


}

