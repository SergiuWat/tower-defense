// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/TWDFunctionLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

EHitDirection UTWDFunctionLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);

	if (Dot < -0.5f)
	{
		return EHitDirection::Back;
	}
	if (Dot < 0.5f)
	{
		const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
		if (Cross.Z < 0.f)
		{
			return EHitDirection::Left;
		}
		return EHitDirection::Right;
	}

	return EHitDirection::Front;
}

FName UTWDFunctionLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
	switch (HitDirection)
	{
	case EHitDirection::Left: return FName("Left");
	case EHitDirection::Right: return FName("Right");
	case EHitDirection::Front: return FName("Front");
	case EHitDirection::Back: return FName("Back");
	default: return FName("None");
	}
}

bool UTWDFunctionLibrary::IsTargetHostile(const AActor* InstigatorPawn, const AActor* TargetPawn)
{
	if (!IsValid(InstigatorPawn) || !IsValid(TargetPawn)) return false;

	const FGenericTeamId InstigatorId = GetTeamIDFromActor(InstigatorPawn);
	const FGenericTeamId TargetId = GetTeamIDFromActor(TargetPawn);

	return InstigatorId.GetId() != TargetId.GetId();
}

FGenericTeamId UTWDFunctionLibrary::GetTeamIDFromActor(const AActor* Actor)
{
	if (!IsValid(Actor)) return FGenericTeamId::NoTeam;

	if (const IGenericTeamAgentInterface* ActorID = Cast<IGenericTeamAgentInterface>(Actor))
	{
		return ActorID->GetGenericTeamId();
	}
	if (const APawn* Pawn = Cast<APawn>(Actor))
	{
		if (const IGenericTeamAgentInterface* PawnID = Cast<IGenericTeamAgentInterface>(Pawn->GetController()))
		{
			return PawnID->GetGenericTeamId();
		}
	}
	return FGenericTeamId::NoTeam;
}
