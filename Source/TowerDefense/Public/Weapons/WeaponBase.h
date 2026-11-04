// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "WeaponBase.generated.h"

UCLASS()
class TOWERDEFENSE_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	FGameplayTag WeaponTag;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	bool bIsWeaponPrimary;
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	FName SocketToAttach;


private:

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* WeaponSkeletalMesh;

public:
	FORCEINLINE FName GetSocketToAttach() const { return SocketToAttach; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponSkeletalMesh; }


	

};
