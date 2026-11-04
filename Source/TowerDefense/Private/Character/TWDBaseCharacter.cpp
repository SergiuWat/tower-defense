// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TWDBaseCharacter.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"

ATWDBaseCharacter::ATWDBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;


}

UAbilitySystemComponent* ATWDBaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

