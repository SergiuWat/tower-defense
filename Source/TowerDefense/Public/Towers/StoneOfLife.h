// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/IActorThreatInterface.h"
#include "StoneOfLife.generated.h"

class USphereComponent;
class UTWDAbilitySystemComponent;
class UTWDHealthSet;
class UGameplayEffect;
class UWidgetComponent;
class UAttackSlotsComponent;
class UStructureDestructionComponent;
struct FGameplayEventData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStoneOfLifeDestroyed);

UCLASS()
class TOWERDEFENSE_API AStoneOfLife : public AActor, public IGenericTeamAgentInterface, public IAbilitySystemInterface, public IIActorThreatInterface
{
	GENERATED_BODY()
	
public:	

	AStoneOfLife();
	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual FGenericTeamId GetGenericTeamId() const override;

	UPROPERTY(EditDefaultsOnly, Category = "Initialize Data")
	TSubclassOf<UGameplayEffect> InitialAttributesEffect;

	virtual int32 GetThreatLevel() const override;

	UPROPERTY(EditDefaultsOnly, Category = "ThreatLevel")
	int32 ThreatLevel = 0;

	void OnStoneOfLifeDestruction(const FGameplayEventData* Payload);

	FOnStoneOfLifeDestroyed OnStoneOfLifeDestroyed;

protected:
	virtual void BeginPlay() override;

private:	

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTWDAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttackSlotsComponent> AttackSlots;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStructureDestructionComponent> StructureDestructionComponent;

	UPROPERTY()
	TObjectPtr<UTWDHealthSet> HealthSet;

	FGenericTeamId StoneOfLifeID;
};
