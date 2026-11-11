// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterOverlay.h"
#include "Components/ProgressBar.h"

void UCharacterOverlay::UpdateHealth(float Health, float MaxHealth)
{
	if (!IsValid(HealthBar) || MaxHealth <= 0) return;
	float HealthPercent = FMath::Clamp(Health / MaxHealth, 0, 1);
	HealthBar->SetPercent(HealthPercent);

}

void UCharacterOverlay::UpdateMana(float Mana, float MaxMana)
{
	if (!IsValid(ManaBar) || MaxMana <= 0) return;
	float ManaPercent = FMath::Clamp(Mana / MaxMana, 0, 1);
	ManaBar->SetPercent(ManaPercent);
}

void UCharacterOverlay::UpdateXp(float Xp, float MaxXp)
{
	if (!IsValid(XpBar) || MaxXp <= 0) return;
	float XpPercent = FMath::Clamp(Xp / MaxXp, 0, 1);
	XpBar->SetPercent(XpPercent);
}
