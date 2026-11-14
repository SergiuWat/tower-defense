// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace TWDGameplayTags
{
	namespace Abilities
	{

		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Abilities_ActivateOnGiven);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Abilities_HitReact);

		namespace Attack
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Abilities_Attack_Light);
		}

		namespace Block
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Abilities_Block);
		}

		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Abilties_Player_Equip_Hammer);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Abilities_Player_Equip_Shield);
		}
	}

	namespace Event
	{
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Event_Player_Equip_Hammer);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Event_Player_Equip_Shield);
		}

		namespace Weapon
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Event_Weapon_MeleeHit);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Event_Weapon_Shield_Block);
		}

		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Event_HitReact);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Event_Death);
	}

	namespace Weapon
	{
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Weapon_Player_Hammer);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Weapon_Player_Shield);
		}
		namespace Data
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Weapon_Data_Damage);
		}
		
	}

	namespace Enemies
	{
		namespace Data
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Enemies_Data_Xp);
		}
	}

	namespace State
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_State_Death);
	}
}
