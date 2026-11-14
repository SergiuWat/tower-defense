// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/TWDLevelSet.h"
#include "GameplayEffectExtension.h"

void UTWDLevelSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetIncomingXpAttribute())
	{
		const float XpIncoming = GetIncomingXp();
		SetIncomingXp(0.f);
		SetXp(GetXp() + XpIncoming);

		if (GetXp() >= GetMaxXp())
		{
			SetCurrentLevel(GetCurrentLevel() + 1);
			const float XpLeft = GetXp() - GetMaxXp();
			SetXp(XpLeft);
		}

	}

	if (Data.EvaluatedData.Attribute == GetXpAttribute())
	{
		SetXp(FMath::Clamp(GetXp(), 0.f, GetMaxXp()));
	}
}
