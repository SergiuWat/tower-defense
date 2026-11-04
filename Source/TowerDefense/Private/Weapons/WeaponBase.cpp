// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponBase.h"

AWeaponBase::AWeaponBase()
{

	PrimaryActorTick.bCanEverTick = true;

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponSkeletonMesh");
	SetRootComponent(WeaponSkeletalMesh);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

