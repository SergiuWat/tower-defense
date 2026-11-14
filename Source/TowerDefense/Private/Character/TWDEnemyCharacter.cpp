// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TWDEnemyCharacter.h"
#include "Components/EnemyCombatComponent.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/TWDHealthSet.h"
#include "Components/WidgetComponent.h"
#include "UI/EnemiesResourcesBar.h"
#include "Data/StartUpDatabase.h"

ATWDEnemyCharacter::ATWDEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTWDAbilitySystemComponent>("AbilitySystemComponent");
	CombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("CombatComponent");
	HealthSet = CreateDefaultSubobject<UTWDHealthSet>("HealthSet");

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("ResourcesBar");
	WidgetComponent->SetupAttachment(GetRootComponent());
}

void ATWDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (!EnemyStartUpData.IsNull())
	{
		if (UStartUpDatabase* LoadedData = EnemyStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(Cast<UTWDAbilitySystemComponent>(GetAbilitySystemComponent()));
		}
	}

	WidgetComponent->InitWidget();

	if (UEnemiesResourcesBar* ResourceWidget = Cast<UEnemiesResourcesBar>(WidgetComponent->GetUserWidgetObject()))
	{
		ResourceWidget->InitializeWithASC(AbilitySystemComponent);
	}
}

UAbilitySystemComponent* ATWDEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
