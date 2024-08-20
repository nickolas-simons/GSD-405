// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"

void USkillInstance::AddActivationPoints(TEnumAsByte<EGenre> Genre, int ActivationPointIncrease)
{
	bool bIsUniversal = true;
	int UniversalCardOverflow = 0;

	for (FCardTypeCount ActivationPointReq : ItemSkill.SkillRequirement) {
		int CurrActivationPoints = GetActivationPoints(Genre);
		if (Genre == ActivationPointReq.Genre && CurrActivationPoints < ActivationPointReq.Count) {
			bIsUniversal = false;
			UniversalCardOverflow = CurrActivationPoints + ActivationPointIncrease - ActivationPointReq.Count;
			ActivationPointIncrease -= UniversalCardOverflow;
			break;
		}
	}

	TEnumAsByte<EGenre> ModifiedActivationPointType = bIsUniversal ? Universal : Genre;
	AddToActivationPointCount(ModifiedActivationPointType, ActivationPointIncrease);
	if (UniversalCardOverflow)
		AddToActivationPointCount(Universal, UniversalCardOverflow);
}


int USkillInstance::GetActivationPoints(TEnumAsByte<EGenre> Genre)
{
	for (FCardTypeCount ActivationPointType : ActivationPoints) {
		if (Genre == ActivationPointType.Genre)
			return ActivationPointType.Count;
	}
	return 0;
}

void USkillInstance::ResetActivationPoints()
{
	ActivationPoints.Empty();
}

void USkillInstance::AddToActivationPointCount(TEnumAsByte<EGenre> Genre, int ActivationPointIncrease)
{
	for (int i = 0; i < ActivationPoints.Num(); i++){
		if (ActivationPoints[i].Genre == Genre) {
			ActivationPoints[i].Count += ActivationPointIncrease;
			return;
		}
	}
	FCardTypeCount NewType;
	NewType.Genre = Genre;
	NewType.Count = ActivationPointIncrease;
	ActivationPoints.Add(NewType);
}

