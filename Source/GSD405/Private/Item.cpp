// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
}

void UItemInstance::CullEffects()
{
	UE_LOG(LogTemp, Log, TEXT("CULLING"));
	for (int i = Effects.Num() - 1; i >= 0; i--) {
		if (Effects[i]->MarkedForRemoval) {
			OnRemoveEffect.Broadcast(Effects[i]);
			Effects[i]->ConditionalBeginDestroy();
			Effects.RemoveAt(i);
		}
		UE_LOG(LogTemp, Log, TEXT("i : %d"), i);
	}
}

UItemInstance::UItemInstance()
{
}

void UItemInstance::AddEffect(FEffectInstance CardEffect, UObject* Applier)
{
	UEffect* Effect = NewObject<UEffect>(this, CardEffect.Effect);
	Effects.Add(Effect);
	Effect->Magnitude = CardEffect.Magnitude;
	Effect->Owner = this;
	Effect->Applier = Applier;
	Effect->Event(EEffectEvent::EffectApplied, nullptr);
	OnAddEffect.Broadcast(Effect);
	CullEffects();
}

void UItemInstance::ClearEffects()
{
	for (UEffect* Effect : Effects) {
		Effect->RemoveEffect();
	}
}

void UItemInstance::AddActivationPoint(EGenre Genre, int ActivationPointIncrease)
{
	for (FItemSkill Skill : Item->Skills) {
		for (FSkillPrereq SkillRequirement : Skill.SkillRequirement) {

		}
	}


	for (FSkillPrereq CardType : CardTypesPlayed) {
		if (CardType.Genre == Genre) {
			CardType.Count+= ActivationPointIncrease;
			OnActivationPointModify.Broadcast();
			return;
		}
	}
	FSkillPrereq NewGenre;
	NewGenre.Genre = Genre;
	NewGenre.Count = 1;
	CardTypesPlayed.Add(NewGenre);
	OnActivationPointModify.Broadcast();
}

void UItemInstance::ResetActivationPoints()
{
	CardTypesPlayed.Empty();
}

void UItemInstance::ModifyStat(int Modifier)
{
	Stat = Stat + Modifier;
}

void UItemInstance::ResetStat()
{
	Stat = 0;
}

void UItemInstance::CallEffectEvent(EEffectEvent Event, UObject* Payload)
{
	for (int i = 0; i < Effects.Num(); i++) {
		Effects[i]->Event(Event, Payload);
		UE_LOG(LogTemp, Log, TEXT("NUM EFFECTS : %d"), Effects.Num());
	}

	switch (Event) {
	case EEffectEvent::RoundStart:
	case EEffectEvent::TurnEnd:
	case EEffectEvent::TurnStart:
		CullEffects();
		break;
	case DealDamagePostMitigation:
	case DealDamagePreMitigation:
		if (Owner && Owner->Implements<UEffectable>()) {
			IEffectable* InterfaceInstance = Cast<IEffectable>(Owner);
			InterfaceInstance->CallEffectEvent(Event, Payload);
		}
		break;
	default:
		break;
	}
}
