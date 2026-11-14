// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemiesResourcesBar.generated.h"

class UProgressBar;
class UTWDHealthSet;
class UTWDManaSet;
class UAbilitySystemComponent;
struct FOnAttributeChangeData;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UEnemiesResourcesBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ManaBar;

	FDelegateHandle HealthChangedHandle;
	FDelegateHandle MaxHealthChangedHandle;

	FDelegateHandle ManaChangedHandle;
	FDelegateHandle MaxManaChangedHandle;

	bool bHasManaBar = false;;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> CacheAbilitySystemComponent;

	void InitializeWithASC(UAbilitySystemComponent* ASC);
	
	void HandleHealthChange(const FOnAttributeChangeData& Data);
	void HandleManaChange(const FOnAttributeChangeData& Data);

	void RefreshProgressBars();
	void RefreshHealth();
	void RefreshMana();

	void UpdateHealth(float Health, float MaxHealth);
	void UpdateMana(float Mana, float MaxMana);
	
protected:
	virtual void NativeOnInitialized() override;
};
