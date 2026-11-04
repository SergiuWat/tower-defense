// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StartUpDatabase.generated.h"


class UTWDGameplayAbility;
class UTWDAbilitySystemComponent;

UCLASS()
class TOWERDEFENSE_API UStartUpDatabase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UTWDAbilitySystemComponent* ASCToGive, int32 ApplyLevel = 1);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UTWDGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UTWDGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UTWDGameplayAbility>> AbilitiesToGive, UTWDAbilitySystemComponent* ASCToGive, int32 ApplyLevel);
	
};
