// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMods/TWDGameModeBase.h"
#include "Towers/StoneOfLife.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "Spawner/SpawnBase.h"

void ATWDGameModeBase::StartPlay()
{

	CachedStoneOfLife = Cast<AStoneOfLife>(UGameplayStatics::GetActorOfClass(this, AStoneOfLife::StaticClass()));

	if (IsValid(CachedStoneOfLife))
	{
		CachedStoneOfLife->OnStoneOfLifeDestroyed.AddUniqueDynamic(this, &ATWDGameModeBase::HandleStoneOfLifeDestruction);
	}

	UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPointsForSpawner);

	checkf(!TargetPointsForSpawner.IsEmpty(), TEXT("No valid Target Points"));
	
	for (const AActor* TargetPoint : TargetPointsForSpawner)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(TargetPoint->GetActorLocation());
		SpawnTransform.SetRotation(FQuat(TargetPoint->GetActorRotation()));
		SpawnTransform.SetScale3D(FVector(1.f, 1.f, 1.f));

		ASpawnBase* Spawner = GetWorld()->SpawnActor<ASpawnBase>(SpawnerClass, SpawnTransform);

		if (!IsValid(Spawner)) continue;

		Spawner->ActivateSpawn();
		Spawner->OnEnemySpawnInTheWorld.AddUniqueDynamic(this, &ThisClass::OnEnemySpawnInTheWorld);
		
		CachedSpawnwers.AddUnique(Spawner);		
	}

	NextWaveSecondsPassed = SecondsBetweenWaves;

	GetWorld()->GetTimerManager().SetTimer(UpdateUITimerHandle, this, &ThisClass::UpdateUITimerFinished, 1.f, true);
	 
	Super::StartPlay();
}

void ATWDGameModeBase::HandleStoneOfLifeDestruction()
{
	UE_LOG(LogTemp, Warning, TEXT("Stone of Life destroyed - defeat"));
}

void ATWDGameModeBase::OnEnemySpawnInTheWorld(AActor* SpawnedActor)
{
	if (!IsValid(SpawnedActor)) return;

	EnemiesInTheWorld.AddUnique(SpawnedActor);
}

void ATWDGameModeBase::UpdateUITimerFinished()
{
	NextWaveSecondsPassed--;
	UE_LOG(LogTemp, Warning, TEXT("Seconde Until Next Wave: %f"), NextWaveSecondsPassed);

	if (NextWaveSecondsPassed <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave Spawned"));

		MaxWeight = MaxWeight * (WaveNumber * WaveMaxWeightInfluence);



		GetWorld()->GetTimerManager().ClearTimer(UpdateUITimerHandle);
	}
	
}
