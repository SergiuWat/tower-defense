// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TWDPlayerCombatSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTWDPlayerCombatSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData AttackPower;

	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, AttackPower);
	
};
