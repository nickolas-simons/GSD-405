// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Containers/Map.h"
#include "Effect.h"
#include "Card.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum ETargetingType
{
	NonTargeted = 0	UMETA(DisplayName = "NonTargeted"),
	
	Targeted = 1 UMETA(DisplayName = "Targeted")
};

USTRUCT(BlueprintType)
struct FCardEffect
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UEffect> Effect;

	UPROPERTY(BlueprintReadWrite)
	int Magnitude;
};

UCLASS()
class UCard : public UDataAsset
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere)
	FText CardName;

	UPROPERTY(EditAnywhere)
	UTexture2D* CardThumbnail;

	UPROPERTY(EditAnywhere)
	FText CardDescription;

	UPROPERTY(EditAnywhere)
	uint32 CardCost;

	UPROPERTY(EditAnywhere)
	// Array of Effects formatted in ( <Effect Class> , <Magnitude> )
	TArray<FCardEffect> Effects;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETargetingType> TargetingType;

};
