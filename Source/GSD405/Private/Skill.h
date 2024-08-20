// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Effect.h"
#include "Skill.generated.h"

class UItemInstance;

UENUM(BlueprintType)
enum ETargetingType
{
	Self = 0 UMETA(DisplayName = "Self"),
	AllOpposing = 1 UMETA(DisplayName = "AllOpposing"),
	All = 2 UMETA(DisplayName = "All"),
	Melee = 3 UMETA(DisplayName = "Melee"),
	Ranged = 4 UMETA(DisplayName = "Ranged"),
	MostHealth = 5 UMETA(DisplayName = "MostHealth")
};

UCLASS(Blueprintable, BlueprintType)
class USkill : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* SkillThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEffect> EffectType;
};

USTRUCT(Blueprintable, BlueprintType)
struct FCardTypeCount
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EGenre> Genre;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Count;
};

USTRUCT(Blueprintable, BlueprintType)
struct FItemSkill
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkill* Skill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Magnitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCardTypeCount> SkillRequirement;
};

UCLASS(Blueprintable, BlueprintType)
class USkillInstance : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UItemInstance* Item;

	UPROPERTY(BlueprintReadOnly)
	TArray<FCardTypeCount> ActivationPoints;

	UPROPERTY(BlueprintReadOnly)
	FItemSkill ItemSkill;

	UFUNCTION()
	void AddActivationPoints(TEnumAsByte<EGenre> Genre, int ActivationPointIncrease);

	UFUNCTION()
	int GetActivationPoints(TEnumAsByte<EGenre> Genre);

	UFUNCTION()
	void ResetActivationPoints();

private:
	UFUNCTION()
	void AddToActivationPointCount(TEnumAsByte<EGenre> Genre, int ActivationPointIncrease);
};


UCLASS(Blueprintable, BlueprintType)
class USkillPayload : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkillInstance* Skill;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray <UObject*> Targets;
};