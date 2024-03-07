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
	
	CombatDeck = CreateDefaultSubobject<UCombatDeck>(TEXT("CombatDeck"));
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
	CullEffects();
}

void ACombatant::RemoveEffect(UEffect* Effect)
{
	Effect->MarkedForRemoval = 1;
	UE_LOG(LogTemp, Log, TEXT("MARKED"));
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
	CombatDeck->Draw(NUM_CARDS_DRAWN);
}

void ACombatant::CallCardEvents(ECardEvent Event, UObject* Payload)
{
	for (int i = 0; i < Effects.Num(); i++) {
			Effects[i]->Event(Event, Payload);
			UE_LOG(LogTemp, Log, TEXT("NUM EFFECTS : %d"), Effects.Num());
	}

	switch (Event) {
		case ECardEvent::RoundStart:
		case ECardEvent::TurnEnd:
		case ECardEvent::TurnStart:
			CullEffects();
		default:
			break;
	}
}

// Called when the game starts or when spawned
void ACombatant::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACombatant::StartCombat_Implementation()
{
	CombatDeck->InitDeck(Deck);
	RefreshEnergy();
}

void ACombatant::AddEffectToStatusUI_Implementation(UEffect* Effect)
{
}

void ACombatant::RemoveEffectFromStatusUI_Implementation(UEffect* Effect)
{
}

void ACombatant::PlayCard_Implementation(UCard* Card, ACombatant* Target)
{
	ModifyEnergy(-Card->CardCost);
	CombatDeck->Discard(Card);
	for (FCardEffect Effect : Card->Effects) {
		Target->AddEffect(Effect);
	}
}

void ACombatant::RefreshEnergy()
{
	Energy = MaxEnergy;
}

void ACombatant::ModifyEnergy_Implementation(int modifier)
{
	Energy = FMath::Clamp(Energy +modifier, 0, MaxEnergy);
}

void ACombatant::CullEffects()
{
	UE_LOG(LogTemp, Log, TEXT("CULLING"));
	for (int i = 0; i < Effects.Num();) {
		if (Effects[i]->MarkedForRemoval) {
			RemoveEffectFromStatusUI(Effects[i]);
			Effects[i]->DestroyComponent();
			Effects.RemoveAt(i);
		}
		else {
			i++;
		}
		UE_LOG(LogTemp, Log, TEXT("i : %d"), i);
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


