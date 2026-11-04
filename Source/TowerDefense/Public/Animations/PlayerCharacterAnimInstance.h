// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TWDCharacterTypes/PlayerCharacterTypes.h"
#include "PlayerCharacterAnimInstance.generated.h"

class UPlayerCharacterAnimationData;
class ATWDBaseCharacter;
class UPlayerCharacterAnimationData;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
private:


	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ATWDBaseCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerCharacterAnimationData> AnimationDataSet;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float OrientationAngle;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	FRotator DeltaRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float ForwardAngleMax = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float ForwardAngleMin = -50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float BackwardAngleMax = 130.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float BackwardAngleMin = -130.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float DeadZoneLocomotionDirection = 20;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	ELocomotionDirections VelocityLocomotionDirection = ELocomotionDirections::ELD_Forward;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	ELocomotionDirections LastFrameVelocityLocomotionDirection = ELocomotionDirections::ELD_Forward;

	ELocomotionDirections CalculateLocomotionDirection(float LocomotionAngle, ELocomotionDirections LocomotionDirection);

	// this should be deleted
	//float CalculateYawOffset(FVector Velocity, float DeltaTime);
	float CalculateOrientationAngle() const;
};
