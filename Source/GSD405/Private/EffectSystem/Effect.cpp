// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect.h"

// Sets default values for this component's properties
UEffect::UEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}


void UEffect::Event(EEffectEvent Event, UObject* Payload)
{
	if (MarkedForRemoval)
		return;

	switch (Event) {
		case EEffectEvent::EffectApplied:
			OnEffectApplied();
			break;

		case EEffectEvent::TakeDamagePreMitigation:
			if (UDamagePayload* DamagePayload = Cast<UDamagePayload>(Payload))
				OnTakeDamagePreMitigation(DamagePayload);
			break;

		case EEffectEvent::TakeDamagePostMitigation:
			if (UDamagePayload* DamagePayload = Cast<UDamagePayload>(Payload))
				OnTakeDamagePostMitigation(DamagePayload);
			break;

		case EEffectEvent::DealDamagePreMitigation:
			if(UDamagePayload* DamagePayload = Cast<UDamagePayload>(Payload))
				OnDealDamagePreMitigation(DamagePayload);
			break;

		case EEffectEvent::DealDamagePostMitigation:
			if (UDamagePayload* DamagePayload = Cast<UDamagePayload>(Payload))
				OnDealDamagePostMitigation(DamagePayload);
			break;

		case EEffectEvent::TurnStart:
			OnTurnStart();
			break;

		case EEffectEvent::TurnEnd:
			OnTurnEnd();
			break;

		case EEffectEvent::RoundStart:
			OnRoundStart();
			break;

		case EEffectEvent::SkillUsed:
			OnSkillUsed(Payload);
			break;

		case EEffectEvent::EffectRemoved:
			OnRemoved();
			break;
	}
	return;
}

void UEffect::OnEffectApplied_Implementation()
{
}

void UEffect::OnTakeDamagePreMitigation_Implementation(UDamagePayload* DamagePayload)
{
}

void UEffect::OnTakeDamagePostMitigation_Implementation(UDamagePayload* DamagePayload)
{
}

void UEffect::OnDealDamagePreMitigation_Implementation(UDamagePayload* DamagePayload)
{
}

void UEffect::OnDealDamagePostMitigation_Implementation(UDamagePayload* DamagePayload)
{
}

void UEffect::OnSkillUsed_Implementation(UObject* Skill)
{
}

void UEffect::OnTurnStart_Implementation()
{
}

void UEffect::OnTurnEnd_Implementation()
{
}

void UEffect::OnRoundStart_Implementation()
{
}

void UEffect::OnRemoved_Implementation()
{
}

void UEffect::RemoveEffect()
{
	Event(EEffectEvent::EffectRemoved, nullptr);
	MarkedForRemoval = true;
}
