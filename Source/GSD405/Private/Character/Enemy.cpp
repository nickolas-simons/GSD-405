// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

void AEnemy::InitializeSkills()
{
	Skills.Empty();
	for (FEnemyAction SkillInfo : SkillSelection) {
			USkillInstance* Skill = NewObject<USkillInstance>();
			Skill->Targeting = SkillInfo.Skill.Skill->DefaultTargeting;
			Skill->SkillVariant = SkillInfo.Skill;
			Skill->Owner = this;
			Skills.Add(Skill);
	}
}
