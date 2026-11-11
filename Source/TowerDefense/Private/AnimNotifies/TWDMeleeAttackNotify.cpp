// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/TWDMeleeAttackNotify.h"

void UTWDMeleeAttackNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!IsValid(MeshComp)) return;
	if (!IsValid(MeshComp->GetOwner())) return;


}

TArray<FHitResult> UTWDMeleeAttackNotify::PerformSphereTrace(USkeletalMeshComponent* MeshComp) const
{
	return TArray<FHitResult>();
}

void UTWDMeleeAttackNotify::SendEventsToActors(USkeletalMeshComponent* MeshComp, const TArray<FHitResult>& Hits) const
{}
