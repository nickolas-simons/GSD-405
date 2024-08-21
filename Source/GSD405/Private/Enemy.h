// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "Enemy.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEffectInstance> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETargetingType> TargetingType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ActionCost;
};

UCLASS()
class AEnemy : public ACombatant
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UseAction(FAction Action);
};
