// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TWDHud.generated.h"

class UCharacterOverlay;
class UTWDAbilitySystemComponent;
struct FOnAttributeChangeData;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATWDHud : public AHUD
{
	GENERATED_BODY()

public:


	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UTWDAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> CharacterOverlayClass;

	UPROPERTY()
	TObjectPtr<UCharacterOverlay> CharacterOverlay;

	void TryInitializeOverlay();

	void HandleHealthChange(const FOnAttributeChangeData& Data);
	void HandleManaChange(const FOnAttributeChangeData& Data);
	void HandleXpChange(const FOnAttributeChangeData& Data);


	void RefreshHUD();

	void RefreshHealth();
	void RefreshMana();
	void RefreshXp();

	//
	// Delegate Handles
	//
	FDelegateHandle HealthChangedHandle;
	FDelegateHandle MaxHealthChangedHandle;

	FDelegateHandle ManaChangedHandle;
	FDelegateHandle MaxManaChangedHandle;

	FDelegateHandle XpChangedHandle;
	FDelegateHandle MaxXpChangedHandle;
	FDelegateHandle LevelChangedHandle;
};
