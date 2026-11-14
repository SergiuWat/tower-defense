// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TWDBaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "TWDEnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UTWDAbilitySystemComponent;
class UTWDHealthSet;
class UWidgetComponent;
class UStartUpDatabase;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATWDEnemyCharacter : public ATWDBaseCharacter
{
	GENERATED_BODY()

public:
	ATWDEnemyCharacter();

	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rewards")
	float XPReward = 10.f;
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnemyCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTWDAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UTWDHealthSet> HealthSet;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Database", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UStartUpDatabase> EnemyStartUpData;
};
