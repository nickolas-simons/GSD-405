// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Card.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "CombatDeck.h"
#include "Combatant.generated.h"

#define NUM_CARDS_DRAWN 5

DECLARE_DELEGATE(FEndTurnDelegate);

UCLASS()
class ACombatant : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatant();

	FEndTurnDelegate EndTurnDelegate;

	UFUNCTION(BlueprintCallable)
	int GetHealth();

	UFUNCTION(BlueprintCallable)
	int GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	void AddEffect(FCardEffect CardEffect);

	UFUNCTION(BlueprintCallable)
	void RemoveEffect(UEffect* Effect);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Damage(int Damage);

	UFUNCTION(BlueprintNativeEvent)
	void StartTurn();

	UFUNCTION(BlueprintNativeEvent)
	void StartCombat();

	UFUNCTION(BlueprintNativeEvent)
	void CombatEnd();

	UFUNCTION(BlueprintCallable)
	void CallCardEvents(ECardEvent Event, UObject* Payload);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void EndTurn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isAlive = true;

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCombatDeck* CombatDeck;

	UPROPERTY(BlueprintReadOnly)
	TArray<UCard*> Deck;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* StatusWidget;

	UPROPERTY(BlueprintReadOnly)
	TArray<UEffect*> Effects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MaxHealth;

	UFUNCTION(BlueprintNativeEvent)
	void AddEffectToStatusUI(UEffect* Effect);

	UFUNCTION(BlueprintNativeEvent)
	void RemoveEffectFromStatusUI(UEffect* Effect);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayCard(UCard* Card, ACombatant* Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die();

	UPROPERTY(BlueprintReadOnly)
	int Energy;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int MaxEnergy;

	UFUNCTION(BlueprintCallable)
	void RefreshEnergy();

	UFUNCTION(BlueprintNativeEvent)
	void ModifyEnergy(int modifier);

	

private:

	void CullEffects();

public:


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
