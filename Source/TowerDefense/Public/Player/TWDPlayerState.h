// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "TWDPlayerState.generated.h"


class UTWDAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATWDPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ATWDPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
private:

	UPROPERTY(VisibleAnywhere, Category = "Crash|Abilities")
	TObjectPtr<UTWDAbilitySystemComponent> AbilitySystemComponent;
};
