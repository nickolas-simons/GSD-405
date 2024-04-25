// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "Engine/DataAsset.h"
#include "CoreMinimal.h"
#include "Item.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EItemType
{
	Helmet = 0	UMETA(DisplayName = "Helmet"),
	Armor = 1		UMETA(DisplayName = "Armor"),
	Weapon = 2		UMETA(DisplayName = "Weapon"),
	Implant = 3			UMETA(DisplayName = "Implant"),
	Legs = 4			UMETA(DisplayName = "Legs")
};

UCLASS(Blueprintable, BlueprintType)
class UItem : public UDataAsset
{
	GENERATED_BODY()

public:
	UItem();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<UCard*> Cards;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EItemType> ItemType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UTexture2D* ItemThumbnail;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText ItemName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText ItemDescription;


};
