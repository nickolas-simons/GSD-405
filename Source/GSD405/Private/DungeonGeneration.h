// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Character/Enemy.h"
#include "./Inventory/Item.h"
#include "DungeonGeneration.generated.h"

UENUM(BlueprintType)
enum ERoomType {
	CombatRoom = 0 UMETA(DisplayName = "CombatRoom"),
	SupplyRoom = 1 UMETA(DisplayName = "SupplyRoom"),
	BossRoom = 2 UMETA(DisplayName = "BossRoom"),
	TaskRoom = 3 UMETA(DisplayName = "TaskRoom")
};

USTRUCT(BlueprintType)
struct FEncounterTemplate {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float EncounterDistance;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int NumItems;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int NumEnemies;
};

UCLASS(Blueprintable, BlueprintType)
class URoomTemplate : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray <TSubclassOf<AEnemy>> EnemyPool;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray <UItem*> ItemPool;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int NumEnemies;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int NumItems;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FName MapName;
};

UCLASS(Blueprintable, BlueprintType)
class UHallwayTemplate : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray <TSubclassOf<AEnemy>> EnemyPool;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray <UItem*> ItemPool;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FEncounterTemplate> Encounters;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText MapName;
};

USTRUCT(Blueprintable, BlueprintType)
struct FDungeonTemplateLink {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<URoomTemplate*> RoomPool;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<UHallwayTemplate*> HallwayPool;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bHasBranch;
};

UCLASS(Blueprintable, BlueprintType)
class UDungeonTemplate : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FDungeonTemplateLink> Links;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<UDungeonTemplate*> BranchPool;
};

USTRUCT(BlueprintType, Blueprintable)
struct FRoom {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<TSubclassOf<AEnemy>> Enemies;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<UItem*> Items;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText MapName;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEncounter {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<TSubclassOf<AEnemy>> Enemies;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<UItem*> Items;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float EncounterDistance;
};

USTRUCT(BlueprintType, Blueprintable)
struct FHallway {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FEncounter> Encounters;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText MapName;
};

USTRUCT(BlueprintType, Blueprintable)
struct FDungeonLink {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FRoom Room;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FHallway Hallway;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int NextIndex;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int BranchIndex;
};

USTRUCT(BlueprintType, Blueprintable)
struct FDungeon {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FDungeonLink> Links;
};


/**
 * 
 */
class DungeonGeneration
{
public:
	DungeonGeneration();
	~DungeonGeneration();
};
