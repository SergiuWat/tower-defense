// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TWDPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "UI/TWDHud.h"

#include "TWDGameplayTags.h"

void ATWDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem)) return;

	InputSubsystem->AddMappingContext(InputMappingContexts, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Triggered, this, &ThisClass::LightAttack);
	EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Started, this, &ThisClass::BlockPressed);
	EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Completed, this, &ThisClass::BlockReleased);

}

void ATWDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ATWDHud* HUD = Cast<ATWDHud>(GetHUD());
	if (IsValid(HUD))
	{
		HUD->TryInitializeOverlay();
	}

}

void ATWDPlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	// Find which way is forward
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void ATWDPlayerController::Look(const FInputActionValue & Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ATWDPlayerController::Jump()
{
	if (!IsValid(GetCharacter())) return;

	GetCharacter()->Jump();
}

void ATWDPlayerController::StopJumping()
{
	if (!IsValid(GetCharacter())) return;

	GetCharacter()->StopJumping();
}

void ATWDPlayerController::LightAttack()
{
	ActivateAbility(TWDGameplayTags::Abilities::Attack::TWDGameplayTags_Abilities_Attack_Light);
}

void ATWDPlayerController::BlockPressed()
{
	ActivateAbility(TWDGameplayTags::Abilities::Block::TWDGameplayTags_Abilities_Block);
}


void ATWDPlayerController::BlockReleased()
{
	FGameplayTagContainer BlockTags;
	BlockTags.AddTag(TWDGameplayTags::Abilities::Block::TWDGameplayTags_Abilities_Block);
	CancelAbilities(BlockTags);
}


void ATWDPlayerController::ActivateAbility(const FGameplayTag& AbilityTag)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC)) return;

	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
	
}

void ATWDPlayerController::CancelAbilities(const FGameplayTagContainer& CancelAbilitiesTagContainer)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC)) return;

	ASC->CancelAbilities(&CancelAbilitiesTagContainer);
}
