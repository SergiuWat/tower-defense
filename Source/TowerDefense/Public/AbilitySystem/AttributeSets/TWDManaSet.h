// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TWDManaSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTWDManaSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData IncomingManaSpending;

	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, Mana);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, MaxMana);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, IncomingManaSpending);
};
