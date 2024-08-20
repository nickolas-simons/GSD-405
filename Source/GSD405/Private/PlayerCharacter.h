// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

#define DEFAULT_NUM_CARDS_DRAWN 1

UCLASS()
class APlayerCharacter : public ACombatant
{
	GENERATED_BODY()
public:
	APlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCombatDeck* CombatDeck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventory* Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int NumCardsDrawn = DEFAULT_NUM_CARDS_DRAWN;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxHandSize = DEFAULT_MAX_HAND_SIZE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int NumShuffles = DEFAULT_NUM_SHUFFLES;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayCard(UCardInstance* Card, UItemInstance* Item);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UseSkill(USkillInstance* Skill);

public:
	virtual void StartCombat_Implementation() override;

	virtual void StartTurn_Implementation() override;

	void CallEffectEvent(EEffectEvent Event, UObject* Payload) override;
};

