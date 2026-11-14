// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemiesResourcesBar.h"
#include "Components/ProgressBar.h"
#include "AbilitySystem/AttributeSets/TWDHealthSet.h"
#include "AbilitySystem/AttributeSets/TWDManaSet.h"
#include "AbilitySystemComponent.h"

void UEnemiesResourcesBar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ManaBar->SetVisibility(ESlateVisibility::Hidden);
}


void UEnemiesResourcesBar::InitializeWithASC(UAbilitySystemComponent* ASC)
{
	if (!IsValid(ASC)) return;

	CacheAbilitySystemComponent = ASC;

	bHasManaBar = CacheAbilitySystemComponent->GetSet<UTWDManaSet>() != nullptr;

	bool bAreHealthHandlesValid = HealthChangedHandle.IsValid() && MaxHealthChangedHandle.IsValid();

	bool bAreManaHandlesValid = ManaChangedHandle.IsValid() && MaxManaChangedHandle.IsValid();

	if (bAreHealthHandlesValid)
	{
		RefreshHealth();

		if (bAreManaHandlesValid)
		{
			RefreshMana();
		}

		return;
	}

	HealthChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDHealthSet::GetHealthAttribute()).AddUObject(this, &UEnemiesResourcesBar::HandleHealthChange);
	MaxHealthChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDHealthSet::GetMaxHealthAttribute()).AddUObject(this, &UEnemiesResourcesBar::HandleHealthChange);

	if (bHasManaBar)
	{
		ManaBar->SetVisibility(ESlateVisibility::Visible);

		ManaChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDManaSet::GetManaAttribute()).AddUObject(this, &UEnemiesResourcesBar::HandleManaChange);
		MaxManaChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDManaSet::GetMaxManaAttribute()).AddUObject(this, &UEnemiesResourcesBar::HandleManaChange);

	}
	
	RefreshProgressBars();
}

void UEnemiesResourcesBar::HandleHealthChange(const FOnAttributeChangeData& Data)
{
	RefreshHealth();
}

void UEnemiesResourcesBar::HandleManaChange(const FOnAttributeChangeData& Data)
{
	RefreshMana();
}

void UEnemiesResourcesBar::RefreshProgressBars()
{
	RefreshHealth();

	if (bHasManaBar)
	{
		RefreshMana();
	}
}

void UEnemiesResourcesBar::RefreshHealth()
{
	if (!IsValid(CacheAbilitySystemComponent)) return;

	const UTWDHealthSet* HealthSet = CacheAbilitySystemComponent->GetSet<UTWDHealthSet>();
	if (!IsValid(HealthSet)) return;

	UpdateHealth(HealthSet->GetHealth(), HealthSet->GetMaxHealth());
}

void UEnemiesResourcesBar::RefreshMana()
{

	if (!IsValid(CacheAbilitySystemComponent)) return;

	const UTWDManaSet* ManaSet = CacheAbilitySystemComponent->GetSet<UTWDManaSet>();
	if (!IsValid(ManaSet)) return;

	UpdateMana(ManaSet->GetMana(), ManaSet->GetMaxMana());
}


void UEnemiesResourcesBar::UpdateHealth(float Health, float MaxHealth)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy UI: Widget=%s HealthBar=%s Health=%.2f MaxHealth=%.2f"), *GetNameSafe(this), *GetNameSafe(HealthBar), Health, MaxHealth);
	if (!IsValid(HealthBar) || MaxHealth <= 0) return;
	float HealthPercent = FMath::Clamp(Health / MaxHealth, 0, 1);
	HealthBar->SetPercent(HealthPercent);

}

void UEnemiesResourcesBar::UpdateMana(float Mana, float MaxMana)
{
	if (!IsValid(ManaBar) || MaxMana <= 0) return;
	float ManaPercent = FMath::Clamp(Mana / MaxMana, 0, 1);
	ManaBar->SetPercent(ManaPercent);
}

