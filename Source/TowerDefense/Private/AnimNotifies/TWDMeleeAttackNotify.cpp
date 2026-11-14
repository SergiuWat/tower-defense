// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/TWDMeleeAttackNotify.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"
#include "KismetTraceUtils.h"
#include "Character/TWDPlayerCharacter.h"
#include "TWDGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/BaseCombatComponent.h"
#include "Weapons/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"

void UTWDMeleeAttackNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!IsValid(MeshComp)) return;
	if (!IsValid(MeshComp->GetOwner())) return;

	TArray<FHitResult> Hits = PerformSphereTrace(MeshComp);
	SendEventsToActors(MeshComp, Hits);

}

TArray<FHitResult> UTWDMeleeAttackNotify::PerformSphereTrace(USkeletalMeshComponent* MeshComp) const
{

	TArray<FHitResult> OutHits;

	AActor* Attacker = MeshComp->GetOwner();
	if (!IsValid(Attacker)) return OutHits;

	UBaseCombatComponent* CombatComponent = Attacker->FindComponentByClass<UBaseCombatComponent>();

	if(!IsValid(CombatComponent)) return OutHits;

	AWeaponBase* Weapon = CombatComponent->GetCharacterPrimayWeaponEquipped();

	if (!IsValid(Weapon)) return OutHits;


	const FTransform SocketTransform = Weapon->GetWeaponMesh()->GetSocketTransform(SocketName);
	const FVector Start = SocketTransform.GetLocation();
	const FVector ExtendedSocketDirection = UKismetMathLibrary::GetForwardVector(SocketTransform.GetRotation().Rotator()) * SocketExtensionOffset;
	const FVector End = Start - ExtendedSocketDirection;

	// might have to change this for when enemies will use it because it might hit other enemies and we dont want that
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(MeshComp->GetOwner());

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

	UWorld* World = GEngine->GetWorldFromContextObject(MeshComp, EGetWorldErrorMode::LogAndReturnNull);

	if (!IsValid(World)) return OutHits;

	bool bHit = World->SweepMultiByChannel(OutHits, Start, End, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(SphereTraceRadius), Params, ResponseParams);

	if (bDrawDebugs)
	{
		DrawDebugSphereTraceMulti(
			World,
			Start,
			End,
			SphereTraceRadius,
			EDrawDebugTrace::ForDuration,
			bHit,
			OutHits,
			FColor::Red,
			FColor::Green,
			5.f);
	}

	return OutHits;

}

void UTWDMeleeAttackNotify::SendEventsToActors(USkeletalMeshComponent* MeshComp, const TArray<FHitResult>& Hits) const
{
	AActor* Attacker = MeshComp->GetOwner();
	if (!IsValid(Attacker)) return;
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Attacker);
	if (!IsValid(ASC)) return;
	
	for (const FHitResult& Hit : Hits)
	{
		AActor* Target = Hit.GetActor();
		if (!IsValid(Target)) continue;
		

		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
		if (!IsValid(TargetASC)) continue;

		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		ContextHandle.AddHitResult(Hit);

		FGameplayEventData Payload;
		Payload.Target = Target;
		Payload.Instigator = Attacker;
		Payload.ContextHandle = ContextHandle;
		Payload.Instigator = MeshComp->GetOwner();


		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Attacker, TWDGameplayTags::Event::Weapon::TWDGameplayTags_Event_Weapon_MeleeHit, Payload);
	}
	
}
