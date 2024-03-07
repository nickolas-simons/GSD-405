// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.h"
#include "CombatDeck.generated.h"

/**
 * 
 */

#define MAX_HAND_SIZE 10
#define NUM_SHUFFLES 1

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDrawCardDelegate, UCard*, Card);

UCLASS(BlueprintType, Blueprintable)
class UCombatDeck : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Draw(int NumCards);

	UFUNCTION()
	void Discard(UCard* Card);

	UFUNCTION()
	void DiscardHand();

	UFUNCTION()
	void Shuffle();

	UFUNCTION()
	void InitDeck(TArray<UCard*> Deck);

	UFUNCTION()
	TArray<UCard*> GetHand();

	UPROPERTY(BlueprintAssignable)
	FDrawCardDelegate DrawDelegate;
	
private:
	UPROPERTY()
	TArray<UCard*> DrawDeck;

	UPROPERTY()
	TArray<UCard*> DiscardDeck;

	UPROPERTY()
	TArray<UCard*> Hand;
};
