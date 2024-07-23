// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Effect.generated.h"

UENUM(BlueprintType)
enum EEffectEvent
{
	EffectApplied = 0	UMETA(DisplayName = "EffectApplied"),
	EffectRemoved = 1		UMETA(DisplayName = "EffectRemoved"),
	TakeDamagePreMitigation = 2		UMETA(DisplayName = "TakeDamagePreMitigation"),
	TakeDamagePostMitigation = 3	UMETA(DisplayName = "TakeDamagePostMitigation"),
	DealDamagePreMitigation = 4		UMETA(DisplayName = "DealDamagePreMitigation"),
	DealDamagePostMitigation = 5	UMETA(DisplayName = "DealDamagePostMitigation"),
	TurnStart = 6		UMETA(DisplayName = "TurnStart"),
	TurnEnd = 7			UMETA(DisplayName = "TurnEnd"),
	RoundStart = 8		UMETA(DisplayName = "RoundStart"),
	SkillUsed = 9		UMETA(DisplayName = "SkillUsed")
};

USTRUCT(BlueprintType, Blueprintable)
struct FEffectInstance
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UObject* Damaged;
};

UCLASS(BlueprintType, Blueprintable )
class UEffect : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffect();

	UFUNCTION(BlueprintCallable)
	void RemoveEffect();

	UFUNCTION(BlueprintCallable)
	void Event(EEffectEvent Event, UObject* Payload);

	UPROPERTY(BlueprintReadWrite)
	int Magnitude;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* EffectThumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int EffectSortPriority;

	UPROPERTY(BlueprintReadOnly)
	UObject* Applier;

	UPROPERTY(BlueprintReadOnly)
	UObject* Owner;

	bool MarkedForRemoval = 0;

protected:

	// Called once, when the effect is initally applied
	UFUNCTION(BlueprintNativeEvent)
	void OnEffectApplied();

	// Called when the effect is removed
	UFUNCTION(BlueprintNativeEvent)
	void OnRemoved();

	// Called before the owner of the effect takes damage
	UFUNCTION(BlueprintNativeEvent)
	void OnTakeDamagePreMitigation(UDamagePayload* DamagePayload);

	// Called after the owner of the effect has taken damage and handled mitigation
	UFUNCTION(BlueprintNativeEvent)
	void OnTakeDamagePostMitigation(UDamagePayload* DamagePayload);

	// Called before the owner of the effect deals damage
	UFUNCTION(BlueprintNativeEvent)
	void OnDealDamagePostMitigation(UDamagePayload* DamagePayload);

	// Called after the owner of the effect has dealt damage and handled mitigation
	UFUNCTION(BlueprintNativeEvent)
	void OnDealDamagePreMitigation(UDamagePayload* DamagePayload);

	// Called once the owner of the effect uses a skill
	UFUNCTION(BlueprintNativeEvent)
	void OnSkillUsed();

	// Called once per round at the start of the effect owner's turn
	UFUNCTION(BlueprintNativeEvent)
	void OnTurnStart();

	// Called once per round at the end of the effect owner's turn 
	UFUNCTION(BlueprintNativeEvent)
	void OnTurnEnd();

	// Called once at the beginning of every round
	UFUNCTION(BlueprintNativeEvent)
	void OnRoundStart();

	

};
