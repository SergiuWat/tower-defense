// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "TWDBaseCharacter.generated.h"

class UTWDAbilitySystemComponent;

UCLASS()
class TOWERDEFENSE_API ATWDBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ATWDBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

public:


};
