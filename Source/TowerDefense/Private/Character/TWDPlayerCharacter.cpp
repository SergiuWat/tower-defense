// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TWDPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystem/TWDAbilitySystemComponent.h"
#include "Player/TWDPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PlayerCharacterCombatComponent.h"
#include "Data/StartUpDatabase.h"
#include "AbilitySystem/AttributeSets/TWDHealthSet.h"
#include "UI/TWDHud.h"

#include "TWDDebugHelper.h"

ATWDPlayerCharacter::ATWDPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	CombatComponent = CreateDefaultSubobject<UPlayerCharacterCombatComponent>("CombatComponent");

	GetCharacterMovement()->bOrientRotationToMovement = false;

}

void ATWDPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* ATWDPlayerCharacter::GetAbilitySystemComponent() const
{
	ATWDPlayerState* PS = Cast<ATWDPlayerState>(GetPlayerState());
	if (!IsValid(PS)) return nullptr;

	return PS->GetAbilitySystemComponent();
}


void ATWDPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	if (!IsValid(ASC)) return;

	ASC->InitAbilityActorInfo(GetPlayerState(), this);

	if (!CharacterStartUpData.IsNull())
	{
		if (UStartUpDatabase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(Cast<UTWDAbilitySystemComponent>(GetAbilitySystemComponent()));
		}
	}
	
}
