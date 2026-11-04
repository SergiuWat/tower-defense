// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TWDGameplayAbility.generated.h"

class UTWDAbilitySystemComponent;
class UBaseCombatComponent;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTWDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintPure)
	UTWDAbilitySystemComponent* GetTWDAbilitySystemComponent() const;

};
