// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Player/PlayerCharacterGameplayAbility.h"
#include "LightAttack.generated.h"


class UAnimMontage;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ULightAttack : public UPlayerCharacterGameplayAbility
{
	GENERATED_BODY()

public:

	ULightAttack();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	TMap<int32, UAnimMontage*> LightAttackAnimMontagesMap;

	UPROPERTY(EditDefaultsOnly, Category = "Combo")
	float ComboProgressWindow = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

private:

	int32 CountComboAttack = 1;

	// Created to make sure that is sending the gameplay effect once per hit actor and not multiple times
	TSet<TWeakObjectPtr<const AActor>> HitActors;

	UFUNCTION()
	void OnPlayAndWaitTaskEventTriggerCompleted();

	UFUNCTION()
	void OnPlayAndWaitTaskEventTriggerInterrupted();
	
	UFUNCTION()
	void OnHitEventReceived(FGameplayEventData Payload);

	UFUNCTION()
	void ResetComboCount();

	FTimerHandle ComboTimerHandle;

	
};
