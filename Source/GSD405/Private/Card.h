// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Containers/Map.h"
#include "Effect.h"
#include "Card.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum ETargetingType
{
	Targeted = 0	UMETA(DisplayName = "Targeted"),
	Self = 1 UMETA(DisplayName = "Self"),
	AllOpposing = 2 UMETA(DisplayName = "AllOpposing")
};

UCLASS(Blueprintable, BlueprintType)
class UCard : public UDataAsset
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CardName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* CardThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CardDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int CardCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCardEffect> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETargetingType> TargetingType;

};


