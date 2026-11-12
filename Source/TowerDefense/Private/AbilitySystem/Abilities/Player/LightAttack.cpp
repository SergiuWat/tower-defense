// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Player/LightAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Animation/AnimMontage.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "TWDGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Weapons/WeaponBase.h"
#include "AbilitySystemGlobals.h"
#include "Components/PlayerCharacterCombatComponent.h"

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

	UAbilityTask_WaitGameplayEvent* WaitHitEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, TWDGameplayTags::Event::Weapon::TWDGameplayTags_Event_Weapon_MeleeHit, nullptr, false, true);

	if (!IsValid(WaitHitEvent))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	WaitHitEvent->EventReceived.AddDynamic(this, &ULightAttack::OnHitEventReceived);
	WaitHitEvent->ReadyForActivation();

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

void ULightAttack::OnHitEventReceived(FGameplayEventData Payload)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Payload.Target.Get());

	if (!IsValid(ASC) || !IsValid(TargetASC) || !IsValid(DamageEffectClass)) return;

	UPlayerCharacterCombatComponent* CombatComponent = GetPlayerCombatComponent();

	if (!IsValid(CombatComponent)) return;

	AWeaponBase* WeaponBase = CombatComponent->GetCharacterPrimayWeaponEquipped();

	if (!IsValid(WeaponBase)) return;


	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	Context.AddSourceObject(WeaponBase);
	if (const FHitResult* Hit = Payload.ContextHandle.GetHitResult())
	{
		Context.AddHitResult(*Hit);
	}

	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), Context);

	if (!SpecHandle.IsValid()) return;

	const FGameplayTag& DamageTag = TWDGameplayTags::Weapon::Data::TWDGameplayTags_Weapon_Data_Damage;
	SpecHandle.Data->SetSetByCallerMagnitude(DamageTag, WeaponBase->BaseDamage);
	ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);


}

