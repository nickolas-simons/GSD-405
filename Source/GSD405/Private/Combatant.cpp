// Fill out your copyright notice in the Description page of Project Settings.


#include "Combatant.h"

// Sets default values
ACombatant::ACombatant()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	StatusWidget->SetupAttachment(GetCapsuleComponent(), FName("StatusWidget"));
	StatusWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCapsuleHalfHeight(64);
	


}

int ACombatant::GetHealth()
{
	return Health;
}

int ACombatant::GetMaxHealth()
{
	return MaxHealth;
}

void ACombatant::AddEffect(FCardEffect CardEffect)
{
	UActorComponent* EffectComponent = AddComponentByClass(CardEffect.Effect, false, FTransform(), false);
	UEffect* Effect = Cast<UEffect>(EffectComponent);
	Effects.Add(Effect);
	AddEffectToStatusUI(Effect);
	Effect->RemovalDelegate.BindUFunction(this, FName("RemoveEffect"));
	Effect->Magnitude = CardEffect.Magnitude;
	Effect->Event(ECardEvent::EffectApplied, nullptr);
}

void ACombatant::RemoveEffect(UEffect* Effect)
{
	RemoveEffectFromStatusUI(Effect);
	Effects.Remove(Effect);
}



void ACombatant::Damage(int Damage)
{
	UDamagePayload* DamagePayload = NewObject<UDamagePayload>();
	DamagePayload->Damage = Damage;
	UE_LOG(LogTemp, Log, TEXT("Damage %d"), Damage);
	CallCardEvents(ECardEvent::TakeDamage,DamagePayload);

	Health -= DamagePayload->Damage;
}

void ACombatant::EndTurn()
{
	CallCardEvents(ECardEvent::TurnEnd, nullptr);
	EndTurnDelegate.ExecuteIfBound();
}

void ACombatant::StartTurn_Implementation()
{
	CallCardEvents(ECardEvent::TurnStart, nullptr);
}

void ACombatant::CallCardEvents(ECardEvent Event, UObject* Payload)
{
	for (int i = 0; i < Effects.Num(); i++) {
		Effects[i]->Event(Event, Payload);
	}
}

// Called when the game starts or when spawned
void ACombatant::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACombatant::StartCombat_Implementation()
{
}

void ACombatant::AddEffectToStatusUI_Implementation(UEffect* Effect)
{
}

void ACombatant::RemoveEffectFromStatusUI_Implementation(UEffect* Effect)
{
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

