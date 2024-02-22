// Fill out your copyright notice in the Description page of Project Settings.


#include "Combatant.h"

// Sets default values
ACombatant::ACombatant()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACombatant::AddEffect(FCardEffect CardEffect)
{
	UActorComponent* EffectComponent = AddComponentByClass(CardEffect.Effect, false, FTransform(), false);
	UEffect* Effect = Cast<UEffect>(EffectComponent);
	Effects.Add(Effect);
	Effect->RemovalDelegate.BindUFunction(this, FName("RemoveEffect"));
	Effect->Magnitude = CardEffect.Magnitude;
	Effect->Event(ECardEvent::EffectApplied, nullptr);
}

void ACombatant::RemoveEffect(UEffect* Effect)
{
	Effects.Remove(Effect);
}



void ACombatant::Damage(int Damage)
{
	UDamagePayload* DamagePayload = NewObject<UDamagePayload>();
	DamagePayload->Damage = Damage;
	CallCardEvents(ECardEvent::TakeDamage,DamagePayload);
}

// Called when the game starts or when spawned
void ACombatant::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACombatant::CallCardEvents(ECardEvent Event, UObject* Payload)
{
	for (UEffect* Effect : Effects) {
		Effect->Event(Event, Payload);
	}
}

// Called every frame
void ACombatant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACombatant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

