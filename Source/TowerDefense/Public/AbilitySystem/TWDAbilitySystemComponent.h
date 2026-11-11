// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TWDAbilitySystemComponent.generated.h"


/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTWDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;

	FGameplayAbilitySpecHandle GiveAbilityIfMissing(const FGameplayAbilitySpec& AbilitySpec);
	
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 1);

private:

	void HandleActivateOnGiven(const FGameplayAbilitySpec& AbilitySpec);
};
