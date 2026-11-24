// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterOverlay.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UCharacterOverlay : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ManaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> XpBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelText;

	void UpdateHealth(float Health, float MaxHealth);
	void UpdateMana(float Mana, float MaxMana);
	void UpdateXp(float Xp, float MaxXp);
	void UpdateLevelText(float CurrentLevel);
};
