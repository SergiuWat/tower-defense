// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "BaseCombatComponent.generated.h"

class AWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UBaseCombatComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	
	bool RegisterSpawnedWeapon(FGameplayTag WeaponTagToRegister, AWeaponBase* WeaponToRegister, bool bRegisterAsEquippedWeapon = false, bool bIsWeaponPrimary = false);
	AWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag WeapontTagToGet) const;
	AWeaponBase* GetCharacterPrimayWeaponEquipped() const;
	AWeaponBase* GetCharacterSecundaryWeaponEquipped() const;

	FGameplayTag PrimaryCurrentEquippedWeaponTag;
	FGameplayTag SecundaryCurrentEquippedWeaponTag;
protected:

private:

	UPROPERTY()
	TMap<FGameplayTag, AWeaponBase*> CharacterCarriedWeaponMap;

		
};
