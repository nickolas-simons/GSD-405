// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "CoreMinimal.h"
#include "Misc/Crc.h"
#include "Item.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable, BlueprintType)
struct FItemDimension {
	GENERATED_BODY()
public:
	FItemDimension(int InWidth, int InHeight): Width(InWidth), Height(InHeight){}

	FItemDimension() : Width(1), Height(1) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Width;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Height;
};

UCLASS(Blueprintable, BlueprintType)
class UItem : public UDataAsset
{
	GENERATED_BODY()

public:

	UItem();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FItemDimension ItemSize;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UTexture2D* ItemThumbnail;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText ItemName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText ItemDescription;
};


