// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Player/PlayerCharacterGameplayAbility.h"
#include "Character/TWDPlayerCharacter.h"
#include "Player/TWDPlayerController.h"
#include "Components/PlayerCharacterCombatComponent.h"

ATWDPlayerCharacter* UPlayerCharacterGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<ATWDPlayerCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

ATWDPlayerController* UPlayerCharacterGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<ATWDPlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UPlayerCharacterCombatComponent* UPlayerCharacterGameplayAbility::GetPlayerCombatComponent() const
{
	return GetAvatarActorFromActorInfo() ? GetAvatarActorFromActorInfo()->FindComponentByClass<UPlayerCharacterCombatComponent>() : nullptr;
}
