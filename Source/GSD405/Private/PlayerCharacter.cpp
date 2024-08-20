// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter() {
	CombatDeck = CreateDefaultSubobject<UCombatDeck>(TEXT("CombatDeck"));
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	CombatDeck->NumShuffles = NumShuffles;
	CombatDeck->MaxHandSize = MaxHandSize;
}
void APlayerCharacter::PlayCard_Implementation(UCardInstance* Card, UItemInstance* Item)
{
	ModifyAP(-Card->CardData->ActionPointCost);
	Item->ModifyActivationPoints(Card->Genre, Card->CardData->ActivationPoints);
	for (FEffectInstance Effect : Card->CardData->Effects) {
		Item->AddEffect(Effect, this);
	}
}

void APlayerCharacter::UseSkill_Implementation(USkillInstance* SkillInstance)
{
	TArray<ACombatant*> Targets;
	GetTargets(SkillInstance->Item->TargetingType, Targets);

	USkillPayload* SkillPayload = NewObject<USkillPayload>();
	SkillPayload->Skill = SkillInstance;
	for (ACombatant* Target : Targets)
		SkillPayload->Targets.Add(Target);

	SkillInstance->Item->CallEffectEvent(EEffectEvent::SkillUsed, SkillPayload);
	CallEffectEvent(EEffectEvent::SkillUsed, SkillPayload);

	for (ACombatant* Target : Targets) {
		FEffectInstance EffectInstance;
		EffectInstance.Effect = SkillInstance->ItemSkill.Skill->EffectType;
		EffectInstance.Magnitude = SkillInstance->ItemSkill.Magnitude;
		Target->AddEffect(EffectInstance, SkillInstance->Item);
	}
}

void APlayerCharacter::StartCombat_Implementation()
{
	ClearEffects();
	Inventory->InitItemInstances();
	CombatDeck->InitDeck(Inventory->ConstructDeck());
	CombatDeck->Shuffle();
}

void APlayerCharacter::StartTurn_Implementation()
{
	if (!isAlive) {
		EndTurn();
		return;
	}
	isTurn = true;
	RefreshAP();

	CombatDeck->Draw(NumCardsDrawn);

	Inventory->ResetSkillRequirements();
	Inventory->ResetStats();
	Inventory->ResetItemUse();

	CallEffectEvent(EEffectEvent::TurnStart, nullptr);
}

void APlayerCharacter::CallEffectEvent(EEffectEvent Event, UObject* Payload)
{
	for (int i = 0; i < Effects.Num(); i++) {
		Effects[i]->Event(Event, Payload);
		UE_LOG(LogTemp, Log, TEXT("NUM EFFECTS : %d"), Effects.Num());
	}

	switch (Event) {
	case EEffectEvent::RoundStart:
	case EEffectEvent::TurnEnd:
	case EEffectEvent::TurnStart:
	case EEffectEvent::SkillUsed:
		CullEffects();
	case EEffectEvent::TakeDamagePostMitigation:
	case EEffectEvent::TakeDamagePreMitigation:
		for (UItemInstance* Item : Inventory->ItemInstances)
			if (Item)
				Item->CallEffectEvent(Event, Payload);
	default:
		break;
	}
}
