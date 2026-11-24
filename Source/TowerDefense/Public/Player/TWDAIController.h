// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI/TWDAITypes.h"
#include "TWDAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class AStoneOfLife;
class UBehaviorTree;
class UAIProfileDataBase;
struct FGameplayTag;
struct FGameplayTagContainer;


/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATWDAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATWDAIController(const FObjectInitializer& ObjectInitializer);

	// This function is from IGenericTeamAgentInterface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;


	bool ActivateAbility(const FGameplayTag& AbilityTag);
	void CancelAbilities(const FGameplayTagContainer& CancelAbilitiesTagContainer);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree> BehaviourTree;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAIProfileDataBase> AITestProfileDatabase;

	FAIProfileTest ProfileTest;

	void AddActorToPosibleTargetsList(AActor* NewActor);
	void RemoveActorFromPosibleTargetsList(AActor* ActorToRemove);
	void EmptyReservedSlot();

	AActor* EvaluateNewTarget();

	
protected:

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Sight> AISenseConfigSight;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);


private:

	UPROPERTY(Transient)
	TObjectPtr<AStoneOfLife> StoneOfLife;

	UPROPERTY()
	TArray<AActor*> PosibleTargets;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config")
	bool bEnableDetourCrowdAvoidance = true;

	// that editcondition lets us to edit this variable only when bEnableDetourCrowdAvoidance is true
	// that UIMin and UIMax is letting us having a slider in the editor with the interval of UIMin and UIMax
	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance", UIMin= "1", UIMax="4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.f;

	FDelegateHandle DeathHandle;

	UFUNCTION()
	void OnDeathTagReceived(const FGameplayTag Tag, int32 NewCount);

	AActor* SelectNewTarget();

	TArray<AActor*> AttackSlotsFilter(const TArray<AActor*> ListToFilter);
	TArray<AActor*> ThreatFilter(const TArray<AActor*> ListToFilter);
	AActor* DistanceFilter(const TArray<AActor*> ListToFilter);
};
