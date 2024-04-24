// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Effect.generated.h"

DECLARE_DELEGATE_OneParam(FRemovalDelegate, UEffect*);

UENUM(BlueprintType)
enum ECardEvent
{
	EffectApplied = 0	UMETA(DisplayName = "EffectApplied"),
	TakeDamagePreMitigation = 1		UMETA(DisplayName = "TakeDamagePreMitigation"),
	TakeDamagePostMitigation = 2 UMETA(DisplayName = "TakeDamagePostMitigation"),
	DealDamagePreMitigation = 3		UMETA(DisplayName = "DealDamagePreMitigation"),
	DealDamagePostMitigation = 4		UMETA(DisplayName = "DealDamagePostMitigation"),
	TurnStart = 5		UMETA(DisplayName = "TurnStart"),
	TurnEnd = 6			UMETA(DisplayName = "TurnEnd"),
	RoundStart = 7		UMETA(DisplayName = "RoundStart"),
	Removed = 8		UMETA(DisplayName = "Removed")
};

USTRUCT(BlueprintType, Blueprintable)
struct FCardEffect
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UEffect> Effect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Magnitude;
};

UCLASS(Blueprintable, BlueprintType)
class UDamagePayload : public UObject
{
	GENERATED_BODY()

	public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UObject* Responsible;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class UEffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffect();

	UFUNCTION(BlueprintCallable)
	void RemoveEffect();

	UFUNCTION(BlueprintCallable)
	void Event(ECardEvent Event, UObject* Payload);

	UPROPERTY(BlueprintReadWrite)
	int Magnitude;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* StatusTexture;

	UPROPERTY(BlueprintReadOnly)
	AActor* Applier;

	bool MarkedForRemoval = 0;

	FRemovalDelegate RemovalDelegate;

protected:

	// Called once, when the effect is initally applied
	UFUNCTION(BlueprintNativeEvent)
	void OnEffectApplied();

	// Called when the owner of the effect takes damage
	// NEEDS DAMAGE PAYLOAD IMPLEMENTATION
	UFUNCTION(BlueprintNativeEvent)
	void OnTakeDamagePreMitigation(UDamagePayload* DamagePayload);

	UFUNCTION(BlueprintNativeEvent)
	void OnTakeDamagePostMitigation(UDamagePayload* DamagePayload);

	// Called when the owner of the effect deals damage
	// NEEDS DAMAGE PAYLOAD IMPLEMENTATION
	UFUNCTION(BlueprintNativeEvent)
	void OnDealDamagePostMitigation(UDamagePayload* DamagePayload);

	UFUNCTION(BlueprintNativeEvent)
	void OnDealDamagePreMitigation(UDamagePayload* DamagePayload);

	// Called once per round at the start of the effect owner's turn
	UFUNCTION(BlueprintNativeEvent)
	void OnTurnStart();

	// Called once per round at the end of the effect owner's turn 
	UFUNCTION(BlueprintNativeEvent)
	void OnTurnEnd();

	// Called once at the beginning of every round
	UFUNCTION(BlueprintNativeEvent)
	void OnRoundStart();

	// Called when the effect is removed (Destructor called)
	UFUNCTION(BlueprintNativeEvent)
	void OnRemoved();

};
