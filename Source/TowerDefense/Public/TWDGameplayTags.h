// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace TWDGameplayTags
{
	namespace Abilities
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Abilities_ActivateOnGiven);

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
	}

	namespace Weapon
	{
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Weapon_Player_Hammer);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TWDGameplayTags_Weapon_Player_Shield);
		}
	}
}
