// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TWDGameplayAbility.h"
#include "HitReact.generated.h"

class UAnimMontage;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UHitReact : public UTWDGameplayAbility
{
	GENERATED_BODY()
	

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UFUNCTION()
	void OnPlayAndWaitTaskEventTriggerCompleted();

	UFUNCTION()
	void OnPlayAndWaitTaskEventTriggerInterrupted();

};
