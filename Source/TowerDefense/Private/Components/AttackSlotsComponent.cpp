// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttackSlotsComponent.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"

#include "DrawDebugHelpers.h"

UAttackSlotsComponent::UAttackSlotsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttackSlotsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* OwnerActor = GetOwner();

	if (!IsValid(OwnerActor)) return;

	if (IsValid(SlotsQuery))
	{
		FEnvQueryRequest Request(SlotsQuery, OwnerActor);
		const int32 RequestId = Request.Execute(EEnvQueryRunMode::AllMatching, this, &UAttackSlotsComponent::OnSlotsGenerated);

		if (RequestId == INDEX_NONE)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Requst failed"), *GetNameSafe(OwnerActor));
		}
	}
}

void UAttackSlotsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAttackSlotsComponent::OnSlotsGenerated(TSharedPtr<FEnvQueryResult> Result)
{
	if (!Result.IsValid() || !Result->IsSuccessful())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: query-ul pentru sloturi a esuat"), *GetNameSafe(GetOwner()));
		return;
	}

	TArray<FVector> SlotLocations;
	Result->GetAllAsLocations(SlotLocations);

	for (int i = 0; i < SlotLocations.Num(); i++)
	{
		FVector& Location = SlotLocations[i];
		Location.Z = SlotWorldZ;

		FSlotInfo SlotInfo;
		SlotInfo.SlotLocations = Location;
		SlotInfo.SlotID = i;

		SlotAvailabilityList.Add(SlotInfo);
	}

	UE_LOG(LogTemp, Display, TEXT("%s: %d sloturi generate"), *GetNameSafe(GetOwner()), SlotLocations.Num());
	for (const FSlotInfo& Slots : SlotAvailabilityList)
	{
		DrawDebugSphere(GetWorld(), Slots.SlotLocations, 18.f, 12, FColor::Green, false, 5000.f);
	}
}


bool UAttackSlotsComponent::AreSlotsAvailable()
{
	for (const FSlotInfo& Slots : SlotAvailabilityList)
	{
		if (!Slots.ReservedBy.IsValid())
		{
			return true;
		}
	}

	return false;
}


bool UAttackSlotsComponent::HasSlotAlreadyReserved(const APawn* PawnToCheck)
{
	for (const FSlotInfo& Slots : SlotAvailabilityList)
	{
		if (!Slots.ReservedBy.IsValid()) continue;

		if (Slots.ReservedBy == PawnToCheck)
		{
			return true;
		}
	}
	return false;
}

bool UAttackSlotsComponent::TryReserveSlotForPawn(APawn* PawnToReserve, FVector& OutLocation)
{
	if (!IsValid(PawnToReserve))
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s: query-ul pentru sloturi a esuat"), *GetNameSafe(PawnToReserve));
		return false;
	}

	if (HasSlotAlreadyReserved(PawnToReserve))
	{
		for (const FSlotInfo& Slots : SlotAvailabilityList)
		{
			if (!Slots.ReservedBy.IsValid()) continue;

			if (Slots.ReservedBy == PawnToReserve)
			{
				OutLocation = Slots.SlotLocations;
				return true;
			}
		}
	}

	if (!AreSlotsAvailable())
	{
		//UE_LOG(LogTemp, Warning, TEXT("No Slots available"));
		return false;
	}
	
	float SmallestDistance = MAX_FLT;
	FVector SlotLocation;
	int32 SlotId = INDEX_NONE;
	

	for (const FSlotInfo& Slots : SlotAvailabilityList)
	{
		if (Slots.ReservedBy.IsValid()) continue;

		float DistanceBetweenTargets = FVector::Dist2D(Slots.SlotLocations, PawnToReserve->GetActorLocation());

		if (SmallestDistance > DistanceBetweenTargets)
		{
			SmallestDistance = DistanceBetweenTargets;
			SlotLocation = Slots.SlotLocations;
			SlotId = Slots.SlotID;
		}
	}

	if (SlotId == INDEX_NONE)
	{
		return false;
	
	}

	if (SlotAvailabilityList.IsValidIndex(SlotId) && !SlotAvailabilityList[SlotId].ReservedBy.IsValid())
	{
		SlotAvailabilityList[SlotId].ReservedBy = PawnToReserve;
		OutLocation = SlotLocation;

		return true;
	}

	return false;
}

void UAttackSlotsComponent::ReleaseSlotForPawn(APawn* PawnToRelease)
{
	for (FSlotInfo& Slots : SlotAvailabilityList)
	{
		if (Slots.ReservedBy == PawnToRelease)
		{
			Slots.ReservedBy = nullptr;
			return;
		}
	}
}
