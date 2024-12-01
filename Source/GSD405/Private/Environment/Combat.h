// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Character/Combatant.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/Item.h"
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

	UFUNCTION()
	void EndCombat();

	UFUNCTION()
	void GetTargetArray(ACombatant* Focus, TArray<ACombatant*>& ReturnArray);

	UFUNCTION(BlueprintCallable)
	TArray<ACombatant*> GetAdjacent(ACombatant* Target);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector EnemySpawnLocationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector PlayerOffset;


protected:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ACombatant>> Enemies;

	UFUNCTION(BlueprintNativeEvent)
	void DistributeRewards();

	UPROPERTY(BlueprintReadOnly)
	TArray<ACombatant*> TurnOrder;


private:
	UPROPERTY()
	int Current = -1;

	UFUNCTION()
	bool AreEnemiesDefeated();

	UFUNCTION()
	bool IsPlayerDefeated();

	UFUNCTION()
	void CheckGameEnd();

	void Setup();

	void SpawnEnemies();
};
