// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "Kismet/GameplayStatics.h"
#include "Item.h"
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

protected:
	UPROPERTY(EditAnywhere)
	FVector EnemySpawnLocationOffset;

	UPROPERTY(EditAnywhere)
	FVector PlayerLocation;

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
