// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter() {
	CombatDeck = CreateDefaultSubobject<UCombatDeck>(TEXT("CombatDeck"));
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	CombatDeck->NumShuffles = NumShuffles;
	CombatDeck->MaxHandSize = MaxHandSize;
}
void APlayerCharacter::PlayCard_Implementation(UCardInstance* Card, USkillInstance* Skill)
{
	UE_LOG(LogTemp, Log, TEXT("PLAYING CARD..."));
	ModifyAP(-Card->CardData->ActionPointCost);
	Skill->AddActivationCard(Card);
	for (FEffectInstance Effect : Card->CardData->Effects) {
		Skill->AddEffect(Effect, this);
		UE_LOG(LogTemp, Log, TEXT("ADDING EFFECT"));
	}
	UE_LOG(LogTemp, Log, TEXT("CARD PLAYED"));
}

void APlayerCharacter::InitializeSkills()
{
	Skills.Empty();
	for (UEquipment* Item : Inventory->EquippedItems) {
		if (!Item)
			continue;
		for (FSkillVariant ItemSkill : Item->Skills) {
			USkillInstance* Skill = NewObject<USkillInstance>();
			Skill->SkillVariant = ItemSkill;
			Skill->Targeting = ItemSkill.Skill->DefaultTargeting;
			Skill->RequiredCards = ItemSkill.SkillRequirement;
			Skill->Owner = this;
			Skills.Add(Skill);
		}
	}
}

void APlayerCharacter::ResetSkills()
{
	for (USkillInstance* Skill : Skills) {
		Skill->ResetActivationCards();
	}
}

void APlayerCharacter::StartCombat_Implementation()
{
	CombatDeck->InitDeck(Inventory->ConstructDeck());
	CombatDeck->Shuffle();
	CombatDeck->Draw(NumStartingCards);
	Super::StartCombat_Implementation();
}

void APlayerCharacter::StartTurn_Implementation()
{
	if (!isAlive) {
		EndTurn();
		return;
	}
	isTurn = true;
	RefreshAP();

	ResetSkills();
	CombatDeck->Draw(NumCardsDrawn);

	CallEffectEvent(EEffectEvent::TurnStart, nullptr);
}
