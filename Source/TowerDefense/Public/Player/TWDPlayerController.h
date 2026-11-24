// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "TWDPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FGameplayTag;
struct FGameplayTagContainer;

UCLASS()
class TOWERDEFENSE_API ATWDPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	ATWDPlayerController();

	// Need for AI this is from IGenericTeamAgentInterface
	virtual FGenericTeamId GetGenericTeamId() const override;

protected:

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	
	// We need this so the AI can now who is enemy and who is friendly
	FGenericTeamId PlayerCharacterTeamID;

	// Input actions and functions

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LightAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> BlockAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void StopJumping();
	void LightAttack();
	void BlockPressed();
	void BlockReleased();

	void ActivateAbility(const FGameplayTag& AbilityTag);
	void CancelAbilities(const FGameplayTagContainer& CancelAbilitiesTagContainer);

	// Input actions and functions

};
