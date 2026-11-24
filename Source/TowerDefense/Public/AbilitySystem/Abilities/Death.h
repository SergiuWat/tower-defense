// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TWDGameplayAbility.h"
#include "Death.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UDeath : public UTWDGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Rewards")
	TSubclassOf<UGameplayEffect> XPRewardEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Death", meta = (ClampMin = "0.1"))
	float DeathDuration = 5.f;

	void TryGrantingXP();

};
