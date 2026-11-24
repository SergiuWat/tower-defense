// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackSlotsComponent.generated.h"

class UEnvQuery;
class ATWDEnemyCharacter;
struct FEnvQueryResult;

USTRUCT(BlueprintType)
struct FSlotInfo
{
	GENERATED_BODY()

public:

	FVector SlotLocations;

	int32 SlotID = 0;

	UPROPERTY()
	TWeakObjectPtr<APawn> ReservedBy;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UAttackSlotsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAttackSlotsComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float SlotWorldZ = 10.f;
protected:

	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UEnvQuery> SlotsQuery;

	TArray<FSlotInfo> SlotAvailabilityList;

	void OnSlotsGenerated(TSharedPtr<FEnvQueryResult> Result);


public:

	bool HasSlotAlreadyReserved(const APawn* PawnToCheck);
	bool AreSlotsAvailable();
	bool TryReserveSlotForPawn(APawn* PawnToReserve, FVector& OutLocation);
	void ReleaseSlotForPawn(APawn* PawnToRelease);
		
};
