// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "Enemy.generated.h"

USTRUCT(Blueprintable)
struct FEnemyAction {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FSkillVariant Skill;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int ActionPointCost;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<ETargetingType> Targeting;
};


UCLASS()
class AEnemy : public ACombatant
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TArray<FEnemyAction> SkillSelection;

	virtual void InitializeSkills() override;
};
