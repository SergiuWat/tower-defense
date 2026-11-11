// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TWDLevelSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTWDLevelSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Xp;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxXp;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData CurrentLevel;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData IncomingXp;

	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, Xp);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, MaxXp);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, CurrentLevel);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, IncomingXp);
	
};
