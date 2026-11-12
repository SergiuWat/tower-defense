// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/TWDPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"


void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	PlayerCharacter = Cast<ATWDPlayerCharacter>(TryGetPawnOwner());
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Cast<ATWDPlayerCharacter>(TryGetPawnOwner());
	}
	if (PlayerCharacter == nullptr) return;

	FVector Velocity2D = PlayerCharacter->GetVelocity();
	Velocity2D.Z = 0;
	GroundSpeed = Velocity2D.Size2D();

	
	Direction = CalculateDirection(Velocity2D, PlayerCharacter->GetActorRotation());
	VelocityLocomotionDirection = CalculateLocomotionDirection(Direction, VelocityLocomotionDirection);

	//YawOffset = CalculateYawOffset(Velocity2D, DeltaTime);
	OrientationAngle = CalculateOrientationAngle();

}

ELocomotionDirections UPlayerCharacterAnimInstance::CalculateLocomotionDirection(float LocomotionAngle, ELocomotionDirections LocomotionDirection)
{
	switch (LocomotionDirection)
	{
	case ELocomotionDirections::ELD_Forward:
		if (LocomotionAngle >= ForwardAngleMin - DeadZoneLocomotionDirection && LocomotionAngle <= ForwardAngleMax + DeadZoneLocomotionDirection)
		{
			return ELocomotionDirections::ELD_Forward;
		}
		break;
	case ELocomotionDirections::ELD_Backward:
		if (LocomotionAngle < BackwardAngleMin + DeadZoneLocomotionDirection || LocomotionAngle > BackwardAngleMax - DeadZoneLocomotionDirection)
		{
			return ELocomotionDirections::ELD_Backward;
		}
		break;
	case ELocomotionDirections::ELD_Left:
		if (LocomotionAngle <= ForwardAngleMin + DeadZoneLocomotionDirection && LocomotionAngle > BackwardAngleMin - DeadZoneLocomotionDirection)
		{
			return ELocomotionDirections::ELD_Left;
		}
		break;
	case ELocomotionDirections::ELD_Right:
		if (LocomotionAngle >= ForwardAngleMax - DeadZoneLocomotionDirection && LocomotionAngle <= BackwardAngleMax + DeadZoneLocomotionDirection)
		{
			return ELocomotionDirections::ELD_Right;
		}
		break;
	default:
		break;
	}

	if (LocomotionAngle > BackwardAngleMax || LocomotionAngle < BackwardAngleMin) return ELocomotionDirections::ELD_Backward;
	else if (LocomotionAngle < ForwardAngleMax && LocomotionAngle > ForwardAngleMin) return ELocomotionDirections::ELD_Forward;
	else if (LocomotionAngle > 0.f) return ELocomotionDirections::ELD_Right;
	else return ELocomotionDirections::ELD_Left;
}

//float UPlayerCharacterAnimInstance::CalculateYawOffset(FVector Velocity, float DeltaTime)
//{
//	FRotator AimRotation = PlayerCharacter->GetBaseAimRotation();
//	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
//	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
//	DeltaRotation = UKismetMathLibrary::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 25.f);
//	
//	return DeltaRotation.Yaw;
//
//}

float UPlayerCharacterAnimInstance::CalculateOrientationAngle() const
{
	float AnimationDirection = 0.f;

	switch (VelocityLocomotionDirection)
	{
	case ELocomotionDirections::ELD_Forward:
		AnimationDirection = 0.f;
		break;

	case ELocomotionDirections::ELD_Backward:
		AnimationDirection = 180.f;
		break;

	case ELocomotionDirections::ELD_Left:
		AnimationDirection = -90.f;
		break;

	case ELocomotionDirections::ELD_Right:
		AnimationDirection = 90.f;
		break;

	default:
		return 0.f;
	}

	return FRotator::NormalizeAxis(Direction - AnimationDirection);
}
