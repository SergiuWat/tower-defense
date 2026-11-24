// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TWDAITypes.generated.h"

USTRUCT(BlueprintType)
struct FAIProfileTest
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	bool bIsPlayerInScene = true;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	bool bConsiderThreatLevel = true;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	bool bUseEQSForStructures = false;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AggroMemorySeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	int32 MaxPlayerAttackers = 10;
};