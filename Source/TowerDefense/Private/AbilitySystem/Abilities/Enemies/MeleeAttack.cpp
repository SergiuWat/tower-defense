// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Enemies/MeleeAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Animation/AnimMontage.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "TWDGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Weapons/WeaponBase.h"
#include "Components/EnemyCombatComponent.h"
#include "Utils/TWDFunctionLibrary.h"


UMeleeAttack::UMeleeAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	HitActors.Reset();

	if (!IsValid(AttackMontage))
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

	WaitHitEvent->EventReceived.AddDynamic(this, &UMeleeAttack::OnHitEventReceived);
	WaitHitEvent->ReadyForActivation();

	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AttackMontage, 1.5f, NAME_None, true, 1.f, 0.f, true);

	if (!IsValid(MontageTask))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	MontageTask->OnCompleted.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerCompleted);
	MontageTask->OnBlendOut.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerCompleted);
	MontageTask->OnInterrupted.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerInterrupted);
	MontageTask->OnCancelled.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerInterrupted);

	MontageTask->ReadyForActivation();
}

void UMeleeAttack::OnPlayAndWaitTaskEventTriggerCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UMeleeAttack::OnPlayAndWaitTaskEventTriggerInterrupted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UMeleeAttack::OnHitEventReceived(FGameplayEventData Payload)
{

	bool bIsTargetHostile = UTWDFunctionLibrary::IsTargetHostile(GetAvatarActorFromActorInfo(), Payload.Target.Get());

	if (!bIsTargetHostile) return;

	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Payload.Target.Get());

	if (!IsValid(ASC) || !IsValid(TargetASC) || !IsValid(DamageEffectClass)) return;

	UEnemyCombatComponent* CombatComponent = GetAvatarActorFromActorInfo()->FindComponentByClass<UEnemyCombatComponent>();

	if (!IsValid(CombatComponent)) return;

	AWeaponBase* WeaponBase = CombatComponent->GetCharacterPrimayWeaponEquipped();

	if (!IsValid(WeaponBase)) return;

	const AActor* Target = Payload.Target.Get();
	if (!IsValid(Target)) return;

	const TWeakObjectPtr<const AActor> TargetKey(Target);

	if (HitActors.Contains(TargetKey)) return;

	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	Context.AddSourceObject(WeaponBase);

	if (const FHitResult* Hit = Payload.ContextHandle.GetHitResult())
	{
		Context.AddHitResult(*Hit);
	}

	const FGameplayTag& DamageTag = TWDGameplayTags::Weapon::Data::TWDGameplayTags_Weapon_Data_Damage;

	TrySendGameplayEffectToActor(TargetASC, Context, DamageEffectClass, DamageTag, WeaponBase->BaseDamage);

	HitActors.Add(TargetKey);
}
