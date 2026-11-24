// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TWDGameModeBase.generated.h"


class AStoneOfLife;
class ASpawnBase;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATWDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawn Information")
	TArray<AActor*> TargetPointsForSpawner;

	void ActivateSpawner();
	void DeactivateSpawner();

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Information")
	float SecondsBetweenWaves = 60;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Information")
	float MaxWeight = 20;

	// how much does the wave number influence the maximum numbers of enemies that can spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawn Information", meta = (ClampMin = "0", ClampMax = "1"))
	float WaveMaxWeightInfluence = 0.75f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Information")
	TSubclassOf<ASpawnBase> SpawnerClass;

private:

	UFUNCTION()
	void HandleStoneOfLifeDestruction();
	void HandleSpawnWave();

	UFUNCTION()
	void OnEnemySpawnInTheWorld(AActor* SpawnedActor);
	

	UFUNCTION()
	void UpdateUITimerFinished();

	UPROPERTY()
	TObjectPtr<AStoneOfLife> CachedStoneOfLife;

	UPROPERTY()
	TArray<ASpawnBase*> CachedSpawnwers;

	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> EnemiesInTheWorld;

	int32 WaveNumber = 1;

	FTimerHandle UpdateUITimerHandle;

	float NextWaveSecondsPassed;


public:

	FORCEINLINE int32 GetWaveNumber() const { return WaveNumber; } 
	
};
