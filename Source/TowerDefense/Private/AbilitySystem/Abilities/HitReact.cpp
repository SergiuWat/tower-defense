// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HitReact.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Animation/AnimMontage.h"
#include "TWDGameplayTags.h"
#include "Utils/TWDFunctionLibrary.h"

void UHitReact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// The ability is activated base on Game event trigger set in the editor in Trigger Source

	if (!TriggerEventData)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	checkf(IsValid(HitReactMontage), TEXT("Please provide a valid HitReactMontage"));

	if (!IsValid(HitReactMontage))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	const AActor* Instigator = TriggerEventData->Instigator.Get();
	const AActor* Target = TriggerEventData->Target.Get();

	if (!IsValid(Instigator) || !IsValid(Target))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	const FHitResult* Hit = TriggerEventData->ContextHandle.GetHitResult();
	const FVector ToInstigator = (Instigator->GetActorLocation() - Target->GetActorLocation()).GetSafeNormal();

	EHitDirection HitDirection = UTWDFunctionLibrary::GetHitDirection(Target->GetActorForwardVector().GetSafeNormal(), ToInstigator);
	FName HitDirectioName = UTWDFunctionLibrary::GetHitDirectionName(HitDirection);

	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, HitReactMontage, 1.f, HitDirectioName, true, 1.f, 0.f, true);

	if (!IsValid(MontageTask))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	MontageTask->OnCompleted.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerCompleted);
	MontageTask->OnBlendOut.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerCompleted);
	MontageTask->OnInterrupted.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerInterrupted);
	MontageTask->OnCancelled.AddDynamic(this, &ThisClass::OnPlayAndWaitTaskEventTriggerInterrupted);

	MontageTask->ReadyForActivation();

}

void UHitReact::OnPlayAndWaitTaskEventTriggerCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UHitReact::OnPlayAndWaitTaskEventTriggerInterrupted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
