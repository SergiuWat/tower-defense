// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TWDPlayerState.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/TWDHealthSet.h"
#include "AbilitySystem/AttributeSets/TWDManaSet.h"
#include "AbilitySystem/AttributeSets/TWDLevelSet.h"

ATWDPlayerState::ATWDPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTWDAbilitySystemComponent>("AbilitySystemComponent");

	HealthSet = CreateDefaultSubobject<UTWDHealthSet>("HealthSet");
	ManaSet = CreateDefaultSubobject<UTWDManaSet>("ManaSet");
	LevelSet = CreateDefaultSubobject<UTWDLevelSet>("LevelSet");
}

UAbilitySystemComponent* ATWDPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
