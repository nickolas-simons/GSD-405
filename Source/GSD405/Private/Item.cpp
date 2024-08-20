// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
}

void UItemInstance::ConstructSkillInstances()
{
	SkillInstances.Empty();
	for (FItemSkill ItemSkill : ItemInfo->Skills) {
		USkillInstance* SkillInstance = NewObject<USkillInstance>(this);
		SkillInstance->Item = this;
		SkillInstance->ItemSkill = ItemSkill;
		SkillInstances.Add(SkillInstance);
	}
	
}

void UItemInstance::CalculateSkillActivationPoints()
{
	for (USkillInstance* SkillInstance : SkillInstances) {
		SkillInstance->ResetActivationPoints();
		for (FCardTypeCount ActivationPointType : ActivationPoints) {
			SkillInstance->AddActivationPoints(ActivationPointType.Genre, ActivationPointType.Count);
		}
	}
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
	UEffect* Effect = NewObject<UEffect>( this,CardEffect.Effect);
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

void UItemInstance::ModifyActivationPoints(EGenre Genre, int ActivationPointModifier)
{
	bool bNewType = true;
	for (int i = 0; i < ActivationPoints.Num(); i++) {
		if (ActivationPoints[i].Genre == Genre) {
			ActivationPoints[i].Count += ActivationPointModifier;
			bNewType = false;
		}
	}
	if (bNewType) {
		FCardTypeCount NewType;
		NewType.Genre = Genre;
		NewType.Count = ActivationPointModifier;
		ActivationPoints.Add(NewType);
	}

	CalculateSkillActivationPoints();
	OnActivationPointModify.Broadcast();
}

void UItemInstance::ResetActivationPoints()
{
	
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
