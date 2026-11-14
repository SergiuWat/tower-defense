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
	
	GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, this, &UDeath::DeathDurationFinished, DeathDuration, false);

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

	MontageTask->OnInterrupted.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerInterrupted);
	MontageTask->OnCancelled.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerInterrupted);

	MontageTask->ReadyForActivation();

}

void UDeath::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetWorld()->GetTimerManager().ClearTimer(DeathTimerHandle);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UDeath::OnPlayAndWaitTaskEventTriggerInterrupted()
{
	GetAvatarActorFromActorInfo()->Destroy();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, true);
}

void UDeath::TryGrantingXP()
{
	if (ATWDEnemyCharacter* Enemy = Cast<ATWDEnemyCharacter>(GetAvatarActorFromActorInfo()))
	{

		UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
		UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(CurrentEventData.Instigator);

		if (!IsValid(ASC) || !IsValid(TargetASC)) return;

		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		Context.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(XPRewardEffectClass, GetAbilityLevel(), Context);

		if (!SpecHandle.IsValid()) return;


		const FGameplayTag& XpTag = TWDGameplayTags::Enemies::Data::TWDGameplayTags_Enemies_Data_Xp;
		SpecHandle.Data->SetSetByCallerMagnitude(XpTag, Enemy->XPReward);
		ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
	}

}


void UDeath::DeathDurationFinished()
{
	GetAvatarActorFromActorInfo()->Destroy();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

