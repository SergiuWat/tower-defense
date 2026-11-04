// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TWDPlayerState.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"

ATWDPlayerState::ATWDPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTWDAbilitySystemComponent>("AbilitySystemComponent");

}

UAbilitySystemComponent* ATWDPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
