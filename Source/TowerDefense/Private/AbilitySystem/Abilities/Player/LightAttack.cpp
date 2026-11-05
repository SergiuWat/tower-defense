// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Player/LightAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Animation/AnimMontage.h"

ULightAttack::ULightAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULightAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);

	if (LightAttackAnimMontagesMap.IsEmpty())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	UAnimMontage* const* FoundMontage = LightAttackAnimMontagesMap.Find(CountComboAttack);
	UAnimMontage* AttackMontage = FoundMontage ? *FoundMontage : nullptr;

	if (!IsValid(AttackMontage))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AttackMontage, 1.5f, NAME_None, true, 1.f, 0.f, true);

	if (!IsValid(MontageTask))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (CountComboAttack >= LightAttackAnimMontagesMap.Num())
	{
		ResetComboCount();
	}
	else
	{
		CountComboAttack++;
	}

	MontageTask->OnCompleted.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerCompleted);
	MontageTask->OnBlendOut.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerCompleted);
	MontageTask->OnInterrupted.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerInterrupted);
	MontageTask->OnCancelled.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerInterrupted);

	MontageTask->ReadyForActivation();
}

void ULightAttack::OnPlayAndWaitTaskEventTriggerCompleted()
{

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

	GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ThisClass::ResetComboCount, ComboProgressWindow, false);
}

void ULightAttack::ResetComboCount()
{
	CountComboAttack = 1;
}

void ULightAttack::OnPlayAndWaitTaskEventTriggerInterrupted()
{
	ResetComboCount();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

