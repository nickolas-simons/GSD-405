// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Effect.h"
#include "Effectable.h"
#include "../Deck/Card.h"
#include "Skill.generated.h"

class UItemInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimpleBlueprintDelegate);


UENUM(BlueprintType)
enum ETargetingType
{
	Self = 0 UMETA(DisplayName = "Self"),
	All = 1 UMETA(DisplayName = "All"),
	Left = 3 UMETA(DisplayName = "Left"),
	Right = 4 UMETA(DisplayName = "Right"),
	MostHealth = 6 UMETA(DisplayName = "MostHealh"),
	LeastHealth = 7 UMETA(DisplayName = "LeastHealth")
};

USTRUCT(BlueprintType)
struct FCardGenreCount
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EGenre> Genre;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Count;
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
	TSubclassOf<UEffect> Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETargetingType> DefaultTargeting;
};

USTRUCT(Blueprintable, BlueprintType)
struct FSkillVariant
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkill* Skill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Magnitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCardGenreCount> SkillRequirement;
};

UCLASS(Blueprintable, BlueprintType)
class USkillInstance : public UObject, public IEffectable
{
	GENERATED_BODY()

public:
	USkillInstance();

	UPROPERTY(BlueprintReadOnly)
	int Stat = 0;

	UPROPERTY(BlueprintReadOnly)
	UObject* Owner;

	UPROPERTY(BlueprintReadOnly)
	FSkillVariant SkillVariant;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<ETargetingType> Targeting;

	UPROPERTY(BlueprintReadOnly)
	TArray<UCardInstance*> ActivationCards;

	UPROPERTY(BlueprintReadOnly)
	int TimesRequirementFulfilled;

	UPROPERTY(BlueprintReadOnly)
	int TimesPlayed;

	UPROPERTY(BlueprintReadOnly)
	TArray<FCardGenreCount> RequiredCards;

	UFUNCTION(BlueprintCallable)
	bool RequirementsFulfilled();

	UFUNCTION()
	void AddActivationCard(UCardInstance* Card);

	UFUNCTION()
	void ResetActivationCards();

	UFUNCTION(BlueprintCallable)
	void AddEffect(FEffectInstance CardEffect, UObject* Applier) override;

	UFUNCTION(BlueprintCallable)
	void ModifyStat(int Modifier);

	UFUNCTION(BlueprintCallable)
	void ModifyTimesPlayed(int Modifier);

	UFUNCTION(BlueprintCallable)
	void ClearEffects() override;

	UFUNCTION(BlueprintCallable)
	void CallEffectEvent(EEffectEvent Event, UObject* Payload) override;

protected:
	void CullEffects();

	UPROPERTY(BlueprintReadOnly)
	TArray<UEffect*> Effects;

	UPROPERTY(BlueprintAssignable)
	FEffectDelegate OnAddEffect;

	UPROPERTY(BlueprintAssignable)
	FEffectDelegate OnRemoveEffect;

	UPROPERTY(BlueprintAssignable)
	FSimpleBlueprintDelegate OnUpdate;

private:
	void CalculateRequirements();
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