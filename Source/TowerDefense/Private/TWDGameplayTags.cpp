// Fill out your copyright notice in the Description page of Project Settings.


#include "TWDGameplayTags.h"

namespace TWDGameplayTags
{
	namespace Abilities
	{

		UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Abilities_ActivateOnGiven, "TWDGameplayTags.Abilities.ActivateOnGiven");
		UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Abilities_HitReact, "TWDGameplayTags.Abilities.HitReact");

		namespace Attack
		{
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Abilities_Attack_Light, "TWDGameplayTags.Abilities.Attack.Light");
		}

		namespace Block
		{
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Abilities_Block, "TWDGameplayTags.Abilities.Block");
		}

		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Abilties_Player_Equip_Hammer, "TWDGameplayTags.Abilities.Player.Equip.Hammer");
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Abilities_Player_Equip_Shield, "TWDGameplayTags.Abilities.Player.Equip.Shield");
		}
	}

	namespace Event
	{
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Event_Player_Equip_Hammer, "TWDGameplayTags.Event.Player.Equip.Hammer");
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Event_Player_Equip_Shield, "TWDGameplayTags.Event.Player.Equip.Shield");
		}
		namespace Weapon
		{
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Event_Weapon_MeleeHit, "TWDGameplayTags.Event.Weapon.MeleeHit");
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Event_Weapon_Shield_Block, "TWDGameplayTags.Event.Weapon.Shield.Block");
		}
		UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Event_HitReact, "TWDGameplayTags.Event.HitReact");
		UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Event_Death, "TWDGameplayTags.Event.Death");
	}

	namespace Weapon
	{
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Weapon_Player_Hammer, "TWDGameplayTags.Weapon.Player.Hammer");
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Weapon_Player_Shield, "TWDGameplayTags.Weapon.Player.Shield");
		}

		namespace Data
		{
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Weapon_Data_Damage, "TWDGameplayTags.Weapon.Data.Damage");
		}
	}

	namespace Enemies
	{
		namespace Data
		{
			UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_Enemies_Data_Xp, "TWDGameplayTags.Enemies.Data.Xp");
		}
	}

	namespace State
	{
		UE_DEFINE_GAMEPLAY_TAG(TWDGameplayTags_State_Death, "TWDGameplayTags.State.Death");
	}
}