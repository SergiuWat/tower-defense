// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerCharacterAnimationData.generated.h"

class UAnimSequence;

USTRUCT(BlueprintType)
struct FAnimationData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> IdleAnim = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Walk Animation")
	TObjectPtr<UAnimSequence> WalkAnim_FWD = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Walk Animation")
	TObjectPtr<UAnimSequence> WalkAnim_BWD = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Walk Animation")
	TObjectPtr<UAnimSequence> WalkAnim_LEFT = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Walk Animation")
	TObjectPtr<UAnimSequence> WalkAnim_RIGHT = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jogging Animation")
	TObjectPtr<UAnimSequence> JogAnim_FWD = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jogging Animation")
	TObjectPtr<UAnimSequence> JogAnim_BWD = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jogging Animation")
	TObjectPtr<UAnimSequence> JogAnim_LEFT = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jogging Animation")
	TObjectPtr<UAnimSequence> JogAnim_RIGHT = nullptr;
};
UCLASS()
class TOWERDEFENSE_API UPlayerCharacterAnimationData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterAnimators")
	FAnimationData AnimationsData;

};
