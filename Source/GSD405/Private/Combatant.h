// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Card.h"
#include "Combatant.generated.h"

UCLASS()
class ACombatant : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatant();

	UFUNCTION(BlueprintCallable)
	void AddEffect(FCardEffect CardEffect);

	UFUNCTION(BlueprintCallable)
	void RemoveEffect(UEffect* Effect);

	UFUNCTION(BlueprintCallable)
	void Damage(int Damage);

	UPROPERTY(BlueprintReadOnly)
	TArray<UEffect*> Effects;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	int Health;

	UPROPERTY(BlueprintReadOnly)
	TArray<UCard*> Deck;

	UFUNCTION(BlueprintCallable)
	void CallCardEvents(ECardEvent Event, UObject* Payload);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
