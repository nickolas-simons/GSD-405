// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "Enemy.generated.h"


UCLASS()
class AEnemy : public ACombatant
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TArray<FSkillVariant> SkillSelection;

	virtual void InitializeSkills() override;
};
