// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructureDestructionComponent.generated.h"

class UAttackSlotsComponent;
class AGeometryCollectionActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UStructureDestructionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UStructureDestructionComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Desturction")
	TSubclassOf<AGeometryCollectionActor> RubbleClass;

	void BeginDestruction(const UStaticMeshComponent* MeshComponent);
	void RemoveDestruction();

private:

	UPROPERTY()
	TObjectPtr<AGeometryCollectionActor> CachedRubbleActor;
};
