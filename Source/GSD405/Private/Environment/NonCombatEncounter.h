// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../EffectSystem/Effect.h"
#include "NonCombatEncounter.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FOutcome {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Probability;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText OutcomeText;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FEffectInstance> Consequences;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventOption {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText OptionDescription;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FOutcome> Outcomes;
};

UCLASS(Blueprintable, BlueprintType)
class UNonCombatEncounter : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText EventDescription;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FEventOption> Options;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UTexture2D* EventArt;
};
