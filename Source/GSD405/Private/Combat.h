// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "Kismet/GameplayStatics.h"
#include "Combat.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)
class UCombat : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UCombat();

	UFUNCTION(BlueprintCallable)
	void StartCombat();

	UFUNCTION()
	void NextTurn();

	UFUNCTION()
	void RoundStart();

protected:
	UPROPERTY(EditAnywhere)
	FVector EnemySpawnLocationOffset;

	UPROPERTY(EditAnywhere)
	FVector PlayerLocation;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ACombatant>> Enemies;

private:
	UPROPERTY()
	int Current = -1;

	UPROPERTY()
	TArray<ACombatant*> TurnOrder;

	void Setup();

	void SpawnEnemies();
};
