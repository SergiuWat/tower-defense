// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Player/PlayerCharacterGameplayAbility.h"
#include "Block.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBlock : public UPlayerCharacterGameplayAbility
{
	GENERATED_BODY()
	
public:

	UBlock();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	TObjectPtr<UAnimMontage> BlockMontage;

private:

	UFUNCTION()
	void OnPlayAndWaitTaskEventTriggerInterrupted();
};
