// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

void AEnemy::UseAction_Implementation(FAction Action)
{
	TArray<ACombatant*> Targets;
	GetTargets(Action.TargetingType, Targets);

	USkillInstance* SkillInstance = NewObject<USkillInstance>();
	SkillInstance->Item = nullptr;
	SkillInstance->ItemSkill = Action.Skill;

	USkillPayload* SkillPayload = NewObject<USkillPayload>();
	SkillPayload->Skill = SkillInstance;
	for (ACombatant* Target : Targets)
		SkillPayload->Targets.Add(Target);

	ModifyAP(-Action.ActionCost);

	CallEffectEvent(EEffectEvent::SkillUsed, SkillPayload);

	for (ACombatant* Target : Targets) {
		FEffectInstance EffectInstance;
		EffectInstance.Effect = Action.Skill.Skill->EffectType;
		EffectInstance.Magnitude = Action.Skill.Magnitude;
		Target->AddEffect(EffectInstance, this);
	}
}
