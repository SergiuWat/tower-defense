// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TWDFunctionLibrary.generated.h"


UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Left,
	Right,
	Front,
	Back
};

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTWDFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);
	static FName GetHitDirectionName(const EHitDirection& HitDirection);
};
