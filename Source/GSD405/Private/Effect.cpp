// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect.h"

// Sets default values for this component's properties
UEffect::UEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UEffect::Event(ECardEvent Event, UObject* Payload)
{
	if (MarkedForRemoval)
		return;

	switch (Event) {
		case ECardEvent::EffectApplied:
			OnEffectApplied();
			break;

		case ECardEvent::TakeDamagePreMitigation:
			if (UDamagePayload* DamagePayload = Cast<UDamagePayload>(Payload))
				OnTakeDamagePreMitigation(DamagePayload);
			break;

		case ECardEvent::TakeDamagePostMitigation:
			if (UDamagePayload* DamagePayload = Cast<UDamagePayload>(Payload))
				OnTakeDamagePreMitigation(DamagePayload);
			break;

		case ECardEvent::DealDamagePreMitigation:
			if(UDamagePayload* DamagePayload = Cast<UDamagePayload>(Payload))
				OnDealDamagePreMitigation(DamagePayload);
			break;

		case ECardEvent::DealDamagePostMitigation:
			if (UDamagePayload* DamagePayload = Cast<UDamagePayload>(Payload))
				OnDealDamagePostMitigation(DamagePayload);
			break;

		case ECardEvent::TurnStart:
			OnTurnStart();
			break;

		case ECardEvent::TurnEnd:
			OnTurnEnd();
			break;

		case ECardEvent::RoundStart:
			OnRoundStart();
			break;

		case ECardEvent::Removed:
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
	Event(ECardEvent::Removed, nullptr);
	RemovalDelegate.ExecuteIfBound(this);
}


