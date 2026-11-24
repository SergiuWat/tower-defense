// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StructureDestructionComponent.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"


UStructureDestructionComponent::UStructureDestructionComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UStructureDestructionComponent::BeginDestruction(const UStaticMeshComponent* MeshComponent)
{
	if (!RubbleClass) return;

	const FTransform RubbleTransform = MeshComponent->GetComponentTransform();

	CachedRubbleActor = !IsValid(CachedRubbleActor) ? GetWorld()->SpawnActor<AGeometryCollectionActor>(RubbleClass, RubbleTransform) : CachedRubbleActor.Get();

	if (!IsValid(CachedRubbleActor)) return;

	CachedRubbleActor->GetGeometryCollectionComponent()->CrumbleActiveClusters();
}

void UStructureDestructionComponent::RemoveDestruction()
{
	if (IsValid(CachedRubbleActor))
	{
		CachedRubbleActor->Destroy();
	}
	CachedRubbleActor = nullptr;
}


