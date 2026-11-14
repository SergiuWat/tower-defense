// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/TWDHealthSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "TWDGameplayTags.h"

void UTWDHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);


	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float Damage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (Damage <= 0.f || GetHealth() <= 0.f) return;
		SetHealth(FMath::Clamp(GetHealth() - Damage, 0.f, GetMaxHealth()));

		if (GetHealth() <= 0.f)
		{
			// handle death
		    // Send the payload (xp, instigator trough gameplay events)

			// Send Death event
			const FGameplayEffectContextHandle& ContextHandle = Data.EffectSpec.GetContext();

			FGameplayEventData PayLoad;

			PayLoad.EventTag = TWDGameplayTags::Event::TWDGameplayTags_Event_Death;

			UAbilitySystemComponent* SourceASC = ContextHandle.GetOriginalInstigatorAbilitySystemComponent();

			if (IsValid(SourceASC))
			{
				PayLoad.Instigator = SourceASC->GetAvatarActor();
			}

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.Target.GetAvatarActor(), PayLoad.EventTag, PayLoad);
		}
		else
		{

			AActor* Target = Data.Target.GetAvatarActor();

			if (!IsValid(Target)) return;

			const FGameplayEffectContextHandle& ContextHandle = Data.EffectSpec.GetContext();
			FGameplayEventData PayLoad;
			PayLoad.EventTag = TWDGameplayTags::Event::TWDGameplayTags_Event_HitReact;

			// we need to do this because the player character has the ASC on player state and we need the avator actor
			UAbilitySystemComponent* SourceASC = ContextHandle.GetOriginalInstigatorAbilitySystemComponent();
			if (IsValid(SourceASC))
			{
				PayLoad.Instigator = SourceASC->GetAvatarActor();
			}
			
			PayLoad.Target = Target;
			PayLoad.ContextHandle = ContextHandle;
			
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Target, PayLoad.EventTag, PayLoad);

		}
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

}
