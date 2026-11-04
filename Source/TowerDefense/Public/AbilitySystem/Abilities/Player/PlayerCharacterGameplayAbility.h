// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TWDGameplayAbility.h"
#include "PlayerCharacterGameplayAbility.generated.h"

class ATWDPlayerCharacter;
class ATWDPlayerController;
class UPlayerCharacterCombatComponent;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UPlayerCharacterGameplayAbility : public UTWDGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	ATWDPlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	ATWDPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UPlayerCharacterCombatComponent* GetPlayerCombatComponent() const;


private:

	TWeakObjectPtr<ATWDPlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<ATWDPlayerController> CachedPlayerController;
};
