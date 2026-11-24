// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/SpawnBase.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ASpawnBase::ASpawnBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);

	SpawnerVFXComponent = CreateDefaultSubobject<UNiagaraComponent>("Globe Niagara Component");
	SpawnerVFXComponent->SetupAttachment(GetRootComponent());
	SpawnerVFXComponent->SetAutoActivate(false);
}

void ASpawnBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(SpawnerVFX))
	{
		SpawnerVFXComponent->SetAsset(SpawnerVFX);
	}
}

void ASpawnBase::SpawnEnemy()
{
	// calculate base on the weight of every type of enemy, gonna need to thing how to unlock new types of enemies base on the round number every 5 waves another type of enemy should be unlocked
}

void ASpawnBase::ActivateSpawn()
{
	SpawnerVFXComponent->Activate();

}

void ASpawnBase::DeactivateSpawn()
{
	SpawnerVFXComponent->Deactivate();
}

void ASpawnBase::StartSpawning(float MaxWeight)
{
	
	ActivateSpawn();

	WaveMaxWeight = MaxWeight;
	SkeliMeleeWeight = MaxWeight * MaxWeightSkeliMeleeInfluence;
	SkeliRangeWeight = MaxWeight * MaxWeightSkeliRangeInfluence;
	GhostHealWeight = MaxWeight * MaxWeightGhostHealInfluence;

	GetWorld()->GetTimerManager().SetTimer(StartSpawnEnemiesTimerHandle, this, &ThisClass::SpawnEnemy, SpawnRate, true);
}
