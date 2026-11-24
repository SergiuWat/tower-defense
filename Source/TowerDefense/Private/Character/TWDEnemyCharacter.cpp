// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TWDEnemyCharacter.h"
#include "Components/EnemyCombatComponent.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/TWDHealthSet.h"
#include "Components/WidgetComponent.h"
#include "UI/EnemiesResourcesBar.h"
#include "Data/StartUpDatabase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"
#include "Data/StartUpDatabase.h"
#include "Components/SphereComponent.h"
#include "Player/TWDAIController.h"

ATWDEnemyCharacter::ATWDEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	AbilitySystemComponent = CreateDefaultSubobject<UTWDAbilitySystemComponent>("AbilitySystemComponent");
	CombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("CombatComponent");
	HealthSet = CreateDefaultSubobject<UTWDHealthSet>("HealthSet");

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("ResourcesBar");
	WidgetComponent->SetupAttachment(GetRootComponent());

	EnemyAggroSphereCollision = CreateDefaultSubobject<USphereComponent>("Enemy Aggro Collision");
	EnemyAggroSphereCollision->SetupAttachment(GetRootComponent());

	EnemyAggroSphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	EnemyAggroSphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	EnemyAggroSphereCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	Tags.Add(FName("Enemy"));

}

void ATWDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitEnemyStartUpDataAsync();
	WidgetComponent->InitWidget();

	if (UEnemiesResourcesBar* ResourceWidget = Cast<UEnemiesResourcesBar>(WidgetComponent->GetUserWidgetObject()))
	{
		ResourceWidget->InitializeWithASC(AbilitySystemComponent);
	}

	EnemyAggroSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ATWDEnemyCharacter::OnOverlapBegin);
	EnemyAggroSphereCollision->OnComponentEndOverlap.AddDynamic(this, &ATWDEnemyCharacter::OnOverlapEnd);
}

UAbilitySystemComponent* ATWDEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATWDEnemyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor)) return;

	if (OtherActor->ActorHasTag("Player") || OtherActor->ActorHasTag("Enemy")) return;

	ATWDAIController* AIController = Cast<ATWDAIController>(GetController());
	if (AIController)
	{
		AIController->AddActorToPosibleTargetsList(OtherActor);
	}
}

void ATWDEnemyCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	if (!IsValid(OtherActor)) return;

	if (OtherActor->ActorHasTag("Player") || OtherActor->ActorHasTag("Enemy"))  return;

	ATWDAIController* AIController = Cast<ATWDAIController>(GetController());
	if (AIController)
	{
		AIController->RemoveActorFromPosibleTargetsList(OtherActor);
	}
}

void ATWDEnemyCharacter::InitEnemyStartUpDataAsync()
{
	if (EnemyStartUpData.IsNull()) return;

	//Loading the data async for the enemy because we dont want to block the main thread

	UAssetManager::GetStreamableManager().RequestAsyncLoad(EnemyStartUpData.ToSoftObjectPath(), 
		FStreamableDelegate::CreateLambda([this]()
		{
				if (UStartUpDatabase* LoadedData = EnemyStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(AbilitySystemComponent);
				}
		}));
}
