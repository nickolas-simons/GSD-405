// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Card.h"
#include "Components/WidgetComponent.h"
#include "Combatant.generated.h"

DECLARE_DELEGATE(FEndTurnDelegate);

UCLASS()
class ACombatant : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatant();

	FEndTurnDelegate EndTurnDelegate;

	UPROPERTY(BlueprintReadOnly)
	TArray<UEffect*> Effects;

	UFUNCTION(BlueprintCallable)
	void AddEffect(FCardEffect CardEffect);

	UFUNCTION(BlueprintCallable)
	void RemoveEffect(UEffect* Effect);

	UFUNCTION(BlueprintCallable)
	void Damage(int Damage);

	UFUNCTION(BlueprintNativeEvent)
	void StartTurn();

	UFUNCTION(BlueprintNativeEvent)
	void StartCombat();

	UFUNCTION(BlueprintCallable)
	void CallCardEvents(ECardEvent Event, UObject* Payload);

	UFUNCTION(BlueprintCallable)
	void EndTurn();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	int Health;

	UPROPERTY(BlueprintReadOnly)
	TArray<UCard*> Deck;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
