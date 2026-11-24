// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TWDGameplayAbility.h"
#include "MeleeAttack.generated.h"

class UAnimMontage;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMeleeAttack : public UTWDGameplayAbility
{
	GENERATED_BODY()

public:

	UMeleeAttack();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	TSet<TWeakObjectPtr<const AActor>> HitActors;

private:

	UFUNCTION()
	void OnPlayAndWaitTaskEventTriggerCompleted();

	UFUNCTION()
	void OnPlayAndWaitTaskEventTriggerInterrupted();

	UFUNCTION()
	void OnHitEventReceived(FGameplayEventData Payload);


};
