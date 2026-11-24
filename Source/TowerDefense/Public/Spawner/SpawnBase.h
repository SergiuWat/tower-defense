// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawnInTheWorld, AActor*, SpawnedActor);

class UNiagaraComponent;
class UNiagaraSystem;
class ATWDEnemyCharacter;

UCLASS()
class TOWERDEFENSE_API ASpawnBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnBase();

	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Information")
	TObjectPtr<UNiagaraSystem> SpawnerVFX;

	UPROPERTY(EditAnywhere, Category = "Spawn Information")
	TArray<TSubclassOf<ATWDEnemyCharacter>> TypesOfEnemiesToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn Information")
	float SkeliMeleeWeight;

	UPROPERTY(EditAnywhere, Category = "Spawn Information", meta = (ClampMin = "0", ClampMax = "1"))
	float MaxWeightSkeliMeleeInfluence = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Spawn Information")
	float SkeliRangeWeight;

	UPROPERTY(EditAnywhere, Category = "Spawn Information", meta = (ClampMin = "0", ClampMax = "1"))
	float MaxWeightSkeliRangeInfluence = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Spawn Information")
	float GhostHealWeight;

	UPROPERTY(EditAnywhere, Category = "Spawn Information", meta = (ClampMin = "0", ClampMax = "1"))
	float MaxWeightGhostHealInfluence = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Spawn Information")
	float WaveMaxWeight;

	UPROPERTY(EditAnywhere, Category = "Spawn Information")
	float SpawnRate = 0.2f;

	// how much does the wave number influence the maximum numbers of enemies that can spawn
	UPROPERTY(EditAnywhere, Category = "Spawn Information", meta = (ClampMin = "0", ClampMax = "1"))
	float WaveMaxWeightInfluence;

	FOnEnemySpawnInTheWorld OnEnemySpawnInTheWorld;

	void ActivateSpawn();
	void DeactivateSpawn();

	void StartSpawning(float MaxWeight);

protected:

	virtual void BeginPlay() override;

private:	

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> SpawnerVFXComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	FTimerHandle StartSpawnEnemiesTimerHandle;

	UFUNCTION()
	void SpawnEnemy();

};
