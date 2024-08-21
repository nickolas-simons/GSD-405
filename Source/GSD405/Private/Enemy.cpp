// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

void AEnemy::UseAction_Implementation(FAction Action)
{
	TArray<ACombatant*> Targets;
	GetTargets(Action.TargetingType, Targets);

	ModifyAP(-Action.ActionCost);

	for (ACombatant* Target : Targets) {
		for (FEffectInstance Effect : Action.Effects) {
			Target->AddEffect(Effect, this);
		}
	}
}
