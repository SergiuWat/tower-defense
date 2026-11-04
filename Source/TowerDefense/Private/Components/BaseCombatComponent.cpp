// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseCombatComponent.h"
#include "Weapons/WeaponBase.h"
#include "TWDDebugHelper.h"

bool UBaseCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTagToRegister, AWeaponBase* WeaponToRegister, bool bRegisterAsEquippedWeapon, bool bIsWeaponPrimary)
{
	if (!IsValid(WeaponToRegister) || !WeaponTagToRegister.IsValid()) return false;

	CharacterCarriedWeaponMap.Emplace(WeaponTagToRegister, WeaponToRegister);

	if (bRegisterAsEquippedWeapon)
	{
		if (bIsWeaponPrimary)
		{
			PrimaryCurrentEquippedWeaponTag = WeaponTagToRegister;
		}
		else
		{
			SecundaryCurrentEquippedWeaponTag = WeaponTagToRegister;
		}
	}

	const FString WeaponString = FString::Printf(TEXT("A weapon named: %s has been registered using the tag %s"), *WeaponToRegister->GetName(), *WeaponTagToRegister.ToString());
	Debug::Print(WeaponString);
	return true;
}


AWeaponBase* UBaseCombatComponent::GetCharacterPrimayWeaponEquipped() const
{
	if (!PrimaryCurrentEquippedWeaponTag.IsValid()) return nullptr;

	return GetCharacterCarriedWeaponByTag(PrimaryCurrentEquippedWeaponTag);
}

AWeaponBase* UBaseCombatComponent::GetCharacterSecundaryWeaponEquipped() const
{
	if (!SecundaryCurrentEquippedWeaponTag.IsValid()) return nullptr;

	return GetCharacterCarriedWeaponByTag(SecundaryCurrentEquippedWeaponTag);
}

AWeaponBase* UBaseCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag WeapontTagToGet) const
{

	if (AWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(WeapontTagToGet))
	{
		return *FoundWeapon;
	}

	return nullptr;
}
