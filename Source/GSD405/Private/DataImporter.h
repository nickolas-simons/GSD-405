// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EffectSystem/Effect.h"
#include "Deck/Card.h"
#include "Inventory/Equipment.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "DataImporter.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EDataAssetType {
	Card,
	Item,
	Equipment,
	Skill
};

UCLASS()
class UDataImporter : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void ImportCSVToDataAssets(const FString& FilePath, TEnumAsByte<EDataAssetType> Type);

	UFUNCTION(BlueprintCallable)
	static void InitCard(const FString& ParseString);
	static void InitSkill(const FString& ParseString);
	static void InitEquipment(const FString& ParseString);

	static void SaveAsset(UObject* Asset, const FString& AssetPath, const FString& AssetFileName);

	UFUNCTION(BlueprintCallable)
	static FString OpenCSVFileDialog();

	static TArray<FEffectInstance> ParseEffects(const FString& EffectString);
	static TArray<FSkillVariant> ParseSkills(const FString& EffectString);
	static TSubclassOf<UEffect> LoadEffectClass(const FString& EffectPath);
	static TArray<FItemCard> ParseCards(const FString& EffectString);
};


