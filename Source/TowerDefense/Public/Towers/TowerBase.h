// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/IActorThreatInterface.h"
#include "Interfaces/TowerStateInterface.h"
#include "TowerBase.generated.h"

class UCapsuleComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class USphereComponent;
class UTWDAbilitySystemComponent;
class UAbilitySystemComponent;
class UGameplayEffect;
class UTWDHealthSet;
class UWidgetComponent;
class UAttackSlotsComponent;
class UStructureDestructionComponent;
struct FGameplayEventData;

UCLASS()
class TOWERDEFENSE_API ATowerBase : public AActor, public IGenericTeamAgentInterface, public IAbilitySystemInterface, public IIActorThreatInterface, public ITowerStateInterface
{
	GENERATED_BODY()
	
public:	
	ATowerBase();
	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual FGenericTeamId GetGenericTeamId() const override;

	virtual int32 GetThreatLevel() const override;

	UPROPERTY(EditDefaultsOnly, Category = "ThreatLevel")
	int32 ThreatLevel = 1;

	virtual bool GetIsTowerDestroyed() const override;

	bool bIsTowerDestroyed = false;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> GlobeVFX;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> LaserVFX;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> LaserHitVFX;

	FTimerHandle TickDamageHandle;
	
	UFUNCTION()
	void TryDoDamage();

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamgePerSecond = 0.5;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffect;

	void OnTowerDestruction(const FGameplayEventData* Payload);

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> GlobeVFXPosition;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> GlobeNiagaraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> LaserNiagaraComponent;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> LaserHitNiagaraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTWDAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStructureDestructionComponent> StructureDestructionComponent;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttackSlotsComponent> AttackSlots;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY()
	TObjectPtr<UTWDHealthSet> HealthSet;

	UPROPERTY(EditDefaultsOnly, Category = "Initialize Data")
	TSubclassOf<UGameplayEffect> InitialAttributesEffect;

	TArray<TWeakObjectPtr<AActor>> EnemiesInRange;

	TWeakObjectPtr<AActor> CurrentTarget;


	FGenericTeamId TowerTeamID;

	TWeakObjectPtr<AActor> GetRandomTargetFromTargetsInRange();

	UFUNCTION()
	void OnTargetDeathEventReceived(const FGameplayTag Tag, int32 NewCount);

	void SelectNewTarget();

	void UnbindTargetASC();

	FDelegateHandle DeathEventDelegate;



};
