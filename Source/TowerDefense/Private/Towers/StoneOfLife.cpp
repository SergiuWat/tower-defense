// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/StoneOfLife.h"
#include "Components/SphereComponent.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/TWDHealthSet.h"
#include "Components/WidgetComponent.h"
#include "UI/EnemiesResourcesBar.h"
#include "Components/AttackSlotsComponent.h"
#include "Components/StructureDestructionComponent.h"
#include "TWDGameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"

AStoneOfLife::AStoneOfLife()
{

	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Tower Range Collision");
	SetRootComponent(SphereCollision);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Tower Mesh");
	MeshComponent->SetupAttachment(GetRootComponent());

	AbilitySystemComponent = CreateDefaultSubobject<UTWDAbilitySystemComponent>("AbilitySystemComponent");

	HealthSet = CreateDefaultSubobject<UTWDHealthSet>("HealthSet");

	AttackSlots = CreateDefaultSubobject<UAttackSlotsComponent>("AttackSlotsComponent");

	StructureDestructionComponent = CreateDefaultSubobject<UStructureDestructionComponent>("Structure Destruction Component");

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("ResourcesBar");
	WidgetComponent->SetupAttachment(GetRootComponent());

	StoneOfLifeID = FGenericTeamId(0);
}


void AStoneOfLife::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(TWDGameplayTags::Event::TWDGameplayTags_Event_Death).AddUObject(this, &AStoneOfLife::OnStoneOfLifeDestruction);

	if (InitialAttributesEffect)
	{
		AbilitySystemComponent->TrySendIntialAttributeGameplayEffectToSelf(FGameplayEffectContextHandle(), InitialAttributesEffect, 1);
	}

	WidgetComponent->InitWidget();

	if (UEnemiesResourcesBar* ResourceWidget = Cast<UEnemiesResourcesBar>(WidgetComponent->GetUserWidgetObject()))
	{
		ResourceWidget->InitializeWithASC(AbilitySystemComponent);
	}
}

void AStoneOfLife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStoneOfLife::OnStoneOfLifeDestruction(const FGameplayEventData* Payload)
{
	OnStoneOfLifeDestroyed.Broadcast();
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetVisibility(false);
	WidgetComponent->SetVisibility(false);
	StructureDestructionComponent->BeginDestruction(MeshComponent);
}


UAbilitySystemComponent* AStoneOfLife::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FGenericTeamId AStoneOfLife::GetGenericTeamId() const
{
	return StoneOfLifeID;
}

int32 AStoneOfLife::GetThreatLevel() const
{
	return ThreatLevel;
}

