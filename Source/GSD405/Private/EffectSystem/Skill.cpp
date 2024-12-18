// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"

void USkillInstance::CallEffectEvent(EEffectEvent Event, UObject* Payload)
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

void USkillInstance::CullEffects()
{
	UE_LOG(LogTemp, Log, TEXT("CULLING..."));
	for (int i = Effects.Num() - 1; i >= 0; i--) {
		if (Effects[i]->MarkedForRemoval) {
			OnRemoveEffect.Broadcast(Effects[i]);
			Effects[i]->ConditionalBeginDestroy();
			Effects.RemoveAt(i);
		}
		UE_LOG(LogTemp, Log, TEXT("i : %d"), i);
	}
	UE_LOG(LogTemp, Log, TEXT("CULL COMPLETE"));
}

void USkillInstance::CalculateRequirements()
{
	RequiredCards = SkillVariant.SkillRequirement;

	TimesRequirementFulfilled = 0;
	int UniversalCards = 0;
	for (UCardInstance* Card : ActivationCards) {
		if (Card->Genre == Universal)
			UniversalCards++;
		else {
			bool bCardUsed = false;
			for (int i = 0; i < RequiredCards.Num(); i++) {
				if (Card->Genre == RequiredCards[i].Genre && RequiredCards[i].Count > 0) {
					RequiredCards[i].Count--;
					bCardUsed = true;
					if (RequirementsFulfilled()) {
						TimesRequirementFulfilled++;
						RequiredCards = SkillVariant.SkillRequirement;
					}
					break;
				}
			}

			if(!bCardUsed)
				for (int i = 0; i < RequiredCards.Num(); i++) {
					if (RequiredCards[i].Genre == Universal && RequiredCards[i].Count > 0) {
						RequiredCards[i].Count--;
						if (RequirementsFulfilled()) {
							TimesRequirementFulfilled++;
							RequiredCards = SkillVariant.SkillRequirement;
						}
						break;
					}
				}
		}
	}

	while (UniversalCards > 0) {
		for (int i = 0; i < RequiredCards.Num(); i++) {
			if (RequiredCards[i].Count > 0) {
				RequiredCards[i].Count--;
				UniversalCards--;
				if (RequirementsFulfilled()) {
					TimesRequirementFulfilled++;
					RequiredCards = SkillVariant.SkillRequirement;
				}
				break;
			}
		}
	}
	return;
}

bool USkillInstance::RequirementsFulfilled()
{
	for (FCardGenreCount Requirement : RequiredCards) {
		if (Requirement.Count > 0)
			return false;
	}
	return true;
}

USkillInstance::USkillInstance()
{
}

void USkillInstance::AddActivationCard(UCardInstance* Card)
{
	UE_LOG(LogTemp, Log, TEXT("ADDING ACTIVATION CARD..."));
	if(Card)
		ActivationCards.Add(Card);

	CalculateRequirements();
	OnUpdate.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("ACTIVATION CARD ADDED"));
	return;
}

void USkillInstance::ResetActivationCards()
{
	ActivationCards.Empty();
	RequiredCards = SkillVariant.SkillRequirement;
	TimesRequirementFulfilled = 0;
	TimesPlayed = 0;
	OnUpdate.Broadcast();
}

void USkillInstance::AddEffect(FEffectInstance CardEffect, UObject* Applier)
{
	UEffect* Effect = NewObject<UEffect>(this, CardEffect.Effect);

	switch (Effect->EffectCombinationType) {
		case Additive:
		case Maximum:
		case Minimum:
			for (UEffect* CurrEffect : Effects) {
				if (CurrEffect->IsA(CardEffect.Effect)) {
					if (Effect->EffectCombinationType == Additive)
						CurrEffect->Magnitude += CardEffect.Magnitude;
					else if (Effect->EffectCombinationType == Maximum && CardEffect.Magnitude > CurrEffect->Magnitude)
						CurrEffect->Magnitude = CardEffect.Magnitude;
					else if (Effect->EffectCombinationType == Minimum && CardEffect.Magnitude < CurrEffect->Magnitude)
						CurrEffect->Magnitude = CardEffect.Magnitude;

					Effect->Event(EEffectEvent::EffectApplied, nullptr);
					CullEffects();
					return;
				}
			}
		default:
			break;
	};

	Effects.Add(Effect);
	Effect->Magnitude = CardEffect.Magnitude;
	Effect->Owner = this;
	Effect->Applier = Applier;

	Effect->Event(EEffectEvent::EffectApplied, nullptr);
	OnAddEffect.Broadcast(Effect);
	CullEffects();
}

void USkillInstance::ModifyStat(int Modifier)
{
	Stat = Stat + Modifier;
}

void USkillInstance::ModifyTimesPlayed(int Modifier)
{
	TimesPlayed += Modifier;
	OnUpdate.Broadcast();
}

void USkillInstance::ClearEffects()
{
	for (UEffect* Effect : Effects)
		Effect->RemoveEffect();
}
