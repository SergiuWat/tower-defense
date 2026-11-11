// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TWDHud.h"
#include "Blueprint/UserWidget.h"
#include "UI/CharacterOverlay.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"
#include "Character/TWDPlayerCharacter.h"
#include "AbilitySystem/AttributeSets/TWDHealthSet.h"
#include "AbilitySystem/AttributeSets/TWDManaSet.h"
#include "AbilitySystem/AttributeSets/TWDLevelSet.h"

void ATWDHud::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetOwningPlayerController();
	if (PC && CharacterOverlayClass)
	{
		CharacterOverlay = CreateWidget<UCharacterOverlay>(PC, CharacterOverlayClass);
		if (CharacterOverlay)
		{
			TryInitializeOverlay();
			CharacterOverlay->AddToViewport();
		}
	}
}

void ATWDHud::TryInitializeOverlay()
{
	if (!IsValid(CharacterOverlay)) return;
	
	APlayerController* PC = GetOwningPlayerController();

	if (!IsValid(PC)) return;

	ATWDPlayerCharacter* PlayerCharacter = Cast<ATWDPlayerCharacter>(PC->GetPawn());

	if(!IsValid(PlayerCharacter)) return;

	ASC = IsValid(ASC) ? ASC.Get() : Cast<UTWDAbilitySystemComponent>(PlayerCharacter->GetAbilitySystemComponent());

	if (!IsValid(ASC)) return;
	if (!ASC->GetSet<UTWDHealthSet>()) return;

	bool bAreHandlesValid = HealthChangedHandle.IsValid() &&
							MaxHealthChangedHandle.IsValid() &&
							ManaChangedHandle.IsValid() &&
							MaxManaChangedHandle.IsValid() &&
							XpChangedHandle.IsValid() &&
							MaxXpChangedHandle.IsValid() &&
							LevelChangedHandle.IsValid();

	if (bAreHandlesValid)
	{
		RefreshHUD();
		return;
	}

	HealthChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDHealthSet::GetHealthAttribute()).AddUObject(this, &ATWDHud::HandleHealthChange);
	MaxHealthChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDHealthSet::GetMaxHealthAttribute()).AddUObject(this, &ATWDHud::HandleHealthChange);

	ManaChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDManaSet::GetManaAttribute()).AddUObject(this, &ATWDHud::HandleManaChange);
	MaxManaChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDManaSet::GetMaxManaAttribute()).AddUObject(this, &ATWDHud::HandleManaChange);

	XpChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDLevelSet::GetXpAttribute()).AddUObject(this, &ATWDHud::HandleXpChange);
	MaxXpChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDLevelSet::GetMaxXpAttribute()).AddUObject(this, &ATWDHud::HandleXpChange);
	LevelChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(UTWDLevelSet::GetCurrentLevelAttribute()).AddUObject(this, &ATWDHud::HandleXpChange);

	RefreshHUD();
}

void ATWDHud::HandleHealthChange(const FOnAttributeChangeData& Data)
{
	RefreshHealth();
}

void ATWDHud::HandleManaChange(const FOnAttributeChangeData& Data)
{
	RefreshMana();
}

void ATWDHud::HandleXpChange(const FOnAttributeChangeData& Data)
{
	RefreshXp();
}

void ATWDHud::RefreshHUD()
{
	RefreshHealth();
	RefreshMana();
	RefreshXp();
}

void ATWDHud::RefreshHealth()
{
	if (!IsValid(ASC) || !IsValid(CharacterOverlay)) return;

	const UTWDHealthSet* HealthSet = ASC->GetSet<UTWDHealthSet>();
	if (!IsValid(HealthSet)) return;

	CharacterOverlay->UpdateHealth(HealthSet->GetHealth(), HealthSet->GetMaxHealth());
}

void ATWDHud::RefreshMana()
{

	if (!IsValid(ASC) || !IsValid(CharacterOverlay)) return;

	const UTWDManaSet* ManaSet = ASC->GetSet<UTWDManaSet>();
	if (!IsValid(ManaSet)) return;

	CharacterOverlay->UpdateMana(ManaSet->GetMana(), ManaSet->GetMaxMana());
}

void ATWDHud::RefreshXp()
{

	if (!IsValid(ASC) || !IsValid(CharacterOverlay)) return;

	const UTWDLevelSet* LevelSet = ASC->GetSet<UTWDLevelSet>();
	if (!IsValid(LevelSet)) return;

	CharacterOverlay->UpdateXp(LevelSet->GetXp(), LevelSet->GetMaxXp());
}
