// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

UENUM(BlueprintType)
enum EEquipmentSlot
{
	Head = 0			UMETA(DisplayName = "Head"),
	Chest = 1			UMETA(DisplayName = "Chest"),
	Legs = 2			UMETA(DisplayName = "Legs"),
	LeftWeapon = 3		UMETA(DisplayName = "LeftWeapon"),
	RightWeapon = 4		UMETA(DisplayName = "RightWeapon"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FVector2D, UItem*> PositionItemMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int NumColumns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int NumRows;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenInventory();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CloseInventory();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddItemSelection(UPARAM(ref) TArray<UItem*>& Items);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<UEquipment*> EquippedItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsOpen;

	UFUNCTION(BlueprintCallable)
	UEquipment* GetItem(EEquipmentSlot Slot);

	UFUNCTION(BlueprintCallable)
	TArray<UCardInstance*> ConstructDeck();
};


