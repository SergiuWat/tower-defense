// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Player/PlayerCharacterGameplayAbility.h"
#include "EquipWeapon.generated.h"

class AWeaponBase;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UEquipWeapon : public UPlayerCharacterGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<AWeaponBase> WeaponToEquip;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;


};
