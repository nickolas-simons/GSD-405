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
	Ranged = 4 UMETA(DisplayName = "Ranged")
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ChargeNeeded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEffectInstance> Effects;
};

USTRUCT(Blueprintable, BlueprintType)
struct FSkillInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkill* Skill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemInstance* Item;
};