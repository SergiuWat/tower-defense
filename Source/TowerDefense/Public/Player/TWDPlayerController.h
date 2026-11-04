// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TWDPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FGameplayTag;

UCLASS()
class TOWERDEFENSE_API ATWDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void SetupInputComponent() override;
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void StopJumping();

	void ActivateAbility(const FGameplayTag& AbilityTag);

};
