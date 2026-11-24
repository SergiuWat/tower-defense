// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AI/TWDAITypes.h"
#include "AIProfileDataBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UAIProfileDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FAIProfileTest AIProfileTest;

	FAIProfileTest GetAIProfileTest();
	
};
