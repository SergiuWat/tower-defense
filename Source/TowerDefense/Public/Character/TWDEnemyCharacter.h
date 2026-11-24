// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TWDBaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "TWDEnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UTWDAbilitySystemComponent;
class UTWDHealthSet;
class UWidgetComponent;
class UStartUpDatabase;
class USphereComponent;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATWDEnemyCharacter : public ATWDBaseCharacter
{
	GENERATED_BODY()

public:
	ATWDEnemyCharacter();

	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rewards")
	float XPReward = 10.f;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:
	
	void InitEnemyStartUpDataAsync();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> EnemyAggroSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnemyCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTWDAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UTWDHealthSet> HealthSet;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Database", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UStartUpDatabase> EnemyStartUpData;
};
