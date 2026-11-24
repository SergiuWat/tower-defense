// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IActorThreatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIActorThreatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENSE_API IIActorThreatInterface
{
	GENERATED_BODY()


public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual int32 GetThreatLevel() const = 0;
};
