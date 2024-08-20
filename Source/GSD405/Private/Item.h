// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "CoreMinimal.h"
#include "Skill.h"
#include "Card.h"
#include "Effectable.h"
#include "Misc/Crc.h"
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
	LegArmor = 3			UMETA(DisplayName = "Legs")
};

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
	TArray<UCard*> Cards;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EItemType> ItemType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UTexture2D* ItemThumbnail;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText ItemName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FItemSkill> Skills;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EGenre> Genre;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<ETargetingType> DefaultTargetingType;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMulticastDynamicDelegate);

UCLASS(Blueprintable, BlueprintType)
class UItemInstance : public UObject, public IEffectable
{
	GENERATED_BODY()

public:

	UItemInstance();


protected:
	UPROPERTY(BlueprintReadOnly)
	int Stat;

	UPROPERTY(BlueprintReadOnly)
	TArray<UEffect*> Effects;

	UPROPERTY()
	TArray<FCardTypeCount> ActivationPoints;

public:
	UPROPERTY(BlueprintReadOnly)
	UItem* ItemInfo;

	UPROPERTY(BlueprintReadOnly)
	TArray<USkillInstance*> SkillInstances;

	UPROPERTY(BlueprintReadOnly)
	UObject* Owner;

	UFUNCTION()
	void ConstructSkillInstances();

	UFUNCTION(BlueprintCallable)
	void AddEffect(FEffectInstance CardEffect, UObject* Applier) override;

	UFUNCTION(BlueprintCallable)
	void ClearEffects() override;

	UFUNCTION(BlueprintCallable)
	void ModifyActivationPoints(EGenre Genre, int ActivationPointModifier);

	UFUNCTION(BlueprintCallable)
	void ResetActivationPoints();

	UFUNCTION(BlueprintCallable)
	void ModifyStat(int Modifier);

	UFUNCTION(BlueprintCallable)
	void ResetStat();

	void CallEffectEvent(EEffectEvent Event, UObject* Payload) override;

	UPROPERTY(BlueprintAssignable)
	FMulticastDynamicDelegate OnActivationPointModify;

	UPROPERTY(BlueprintAssignable)
	FEffectDelegate OnAddEffect;

	UPROPERTY(BlueprintAssignable)
	FEffectDelegate OnRemoveEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETargetingType> TargetingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsUsed;
private:

	void CalculateSkillActivationPoints();

	void CullEffects() override;
};
