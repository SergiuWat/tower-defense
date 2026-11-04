// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Player/EquipWeapon.h"
#include "Weapons/WeaponBase.h"
#include "Character/TWDPlayerCharacter.h"
#include "Components/PlayerCharacterCombatComponent.h"
#include "TWDGameplayTags.h"

#include "TWDDebugHelper.h"

void UEquipWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
	checkf(IsValid(WeaponToEquip), TEXT("Please provide a valid Weapon class"));

	if (!IsValid(WeaponToEquip) || !GetPlayerCharacterFromActorInfo())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetAvatarActorFromActorInfo()->GetActorLocation());
	SpawnTransform.SetRotation(FQuat(FRotator(0.f, 0.f, 0.f)));

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Owner = GetPlayerCharacterFromActorInfo();

	AWeaponBase* SpawnedWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponToEquip, SpawnTransform, SpawnParameters);

	if (!IsValid(SpawnedWeapon))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	FAttachmentTransformRules AttachmentRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
	);

	checkf(GetPlayerCharacterFromActorInfo()->GetMesh(), TEXT("Mesh is not valid on Player Character"));
	if (!IsValid(GetPlayerCharacterFromActorInfo()->GetMesh()))
	{
		SpawnedWeapon->Destroy();
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}


	bool bWasSuccesfull = SpawnedWeapon->AttachToComponent(GetPlayerCharacterFromActorInfo()->GetMesh(), AttachmentRules, SpawnedWeapon->GetSocketToAttach());

	if (!bWasSuccesfull)
	{
		SpawnedWeapon->Destroy();
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	UPlayerCharacterCombatComponent* CombatComponent = GetPlayerCombatComponent();

	checkf(CombatComponent, TEXT("Combat component is not valid on Player Character"));
	if (!IsValid(CombatComponent))
	{
		SpawnedWeapon->Destroy();
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	bool bWeaponIsRegistered = CombatComponent->RegisterSpawnedWeapon(SpawnedWeapon->WeaponTag, SpawnedWeapon, true, SpawnedWeapon->bIsWeaponPrimary);

	if (!bWeaponIsRegistered)
	{
		SpawnedWeapon->Destroy();
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
