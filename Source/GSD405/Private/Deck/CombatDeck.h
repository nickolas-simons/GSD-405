// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.h"
#include "CombatDeck.generated.h"

/**
 * 
 */

#define DEFAULT_MAX_HAND_SIZE 7
#define DEFAULT_NUM_SHUFFLES 1

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDrawCardDelegate, UCardInstance*, Card);

UCLASS(BlueprintType, Blueprintable)
class UCombatDeck : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	int MaxHandSize = DEFAULT_MAX_HAND_SIZE;

	UPROPERTY(EditDefaultsOnly)
	int NumShuffles = DEFAULT_NUM_SHUFFLES;

	UFUNCTION(BlueprintCallable)
	void Draw(int NumCards);

	UFUNCTION(BlueprintCallable)
	void Discard(UCardInstance* Card);

	UFUNCTION()
	void DiscardHand();

	UFUNCTION()
	void Shuffle();

	UFUNCTION()
	void InitDeck(TArray<UCardInstance*> Deck);

	UFUNCTION(BlueprintCallable)
	TArray<UCardInstance*> GetHand();

	UPROPERTY(BlueprintAssignable)
	FDrawCardDelegate DrawDelegate;
	
private:
	UPROPERTY()
	TArray<UCardInstance*> DrawDeck;

	UPROPERTY()
	TArray<UCardInstance*> DiscardDeck;

	UPROPERTY()
	TArray<UCardInstance*> Hand;
};
