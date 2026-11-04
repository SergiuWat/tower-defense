// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TWDBaseCharacter.h"

#include "TWDPlayerCharacter.generated.h"

class UAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
class UPlayerCharacterCombatComponent;
class UStartUpDatabase;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATWDPlayerCharacter : public ATWDBaseCharacter
{
	GENERATED_BODY()

public:
	ATWDPlayerCharacter();

	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerCharacterCombatComponent> CombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Database", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UStartUpDatabase> CharacterStartUpData;

public:

	
};
