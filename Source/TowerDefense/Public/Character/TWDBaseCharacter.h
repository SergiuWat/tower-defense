// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/IActorThreatInterface.h"
#include "TWDBaseCharacter.generated.h"

class UTWDAbilitySystemComponent;

UCLASS()
class TOWERDEFENSE_API ATWDBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IIActorThreatInterface
{
	GENERATED_BODY()

public:

	ATWDBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual int32 GetThreatLevel() const override;

	UPROPERTY(EditDefaultsOnly, Category = "ThreatLevel")
	int32 ThreatLevel = 1;
protected:



public:


};
