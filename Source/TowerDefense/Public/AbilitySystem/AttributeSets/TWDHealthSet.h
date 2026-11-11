// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TWDHealthSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTWDHealthSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData IncomingDamage;

	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, Health);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, MaxHealth);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, IncomingDamage);
};
