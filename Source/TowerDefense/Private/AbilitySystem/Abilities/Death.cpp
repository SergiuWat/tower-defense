// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Death.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystemComponent.h"
#include "TWDGameplayTags.h"
#include "Character/TWDEnemyCharacter.h"
#include "AbilitySystemGlobals.h"

void UDeath::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//
	// Send gameplay effect
	//

	if (TriggerEventData)
	{
		TryGrantingXP();
	}

	checkf(IsValid(DeathMontage), TEXT("Please provide a valid HitReactMontage"));
	
	GetAvatarActorFromActorInfo()->SetLifeSpan(DeathDuration);

	if (!IsValid(DeathMontage))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, DeathMontage, 1.f, NAME_None, true, 1.f, 0.f, false);
	
	if (!IsValid(MontageTask))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	MontageTask->ReadyForActivation();

}

void UDeath::TryGrantingXP()
{
	if (ATWDEnemyCharacter* Enemy = Cast<ATWDEnemyCharacter>(GetAvatarActorFromActorInfo()))
	{

		UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(CurrentEventData.Instigator);

		const FGameplayTag& XpTag = TWDGameplayTags::Enemies::Data::TWDGameplayTags_Enemies_Data_Xp;

		TrySendGameplayEffectToActor(TargetASC, FGameplayEffectContextHandle(), XPRewardEffectClass, XpTag, Enemy->XPReward);
		
	}

}
