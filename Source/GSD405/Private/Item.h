// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
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
	R_Weapon = 2		UMETA(DisplayName = "R_Weapon"),
	L_Weapon = 3		UMETA(DisplayName = "L_Weapon"),
	Implant = 4			UMETA(DisplayName = "Implant")
};

UCLASS(Blueprintable, BlueprintType)
class UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<UCard*> Cards;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EItemType> ItemType;
};
