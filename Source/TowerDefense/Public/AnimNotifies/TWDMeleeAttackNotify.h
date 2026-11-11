// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "TWDMeleeAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTWDMeleeAttackNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

private:

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDrawDebugs = true;

	UPROPERTY(EditAnywhere, Category = "Socket")
	FName SocketName;

	UPROPERTY(EditAnywhere, Category = "Socket")
	float SocketExtensionOffset;

	UPROPERTY(EditAnywhere, Category = "Trace")
	float SphereTraceRadius;

	TArray<FHitResult> PerformSphereTrace(USkeletalMeshComponent* MeshComp) const;
	void SendEventsToActors(USkeletalMeshComponent* MeshComp, const TArray<FHitResult>& Hits) const;
	
};
