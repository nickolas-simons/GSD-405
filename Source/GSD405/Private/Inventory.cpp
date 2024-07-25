// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::OpenInventory_Implementation()
{
}

void UInventory::CloseInventory_Implementation()
{
}

UItem* UInventory::GetItem(EEquipmentSlot Slot)
{
	return EquippedItems[Slot];
}

void UInventory::InitItemInstances()
{
	ItemInstances.Empty();
	for (UItem* Item : EquippedItems) {
		if (Item) {
			UItemInstance* ItemInstance = NewObject<UItemInstance>();
			ItemInstance->Item = Item;
			ItemInstance->Owner = GetOwner();
			ItemInstance->TargetingType = Item->DefaultTargetingType;
			ItemInstances.Add(ItemInstance);
		}
		else
			ItemInstances.Add(nullptr);
	}
}

void UInventory::WipeCharge()
{
	for (UItemInstance* Item : ItemInstances) {
		if(Item)
			Item->ModifyCharge(-Item->Item->MaxCharge);
	}
}

void UInventory::ResetStats()
{
	for (UItemInstance* Item : ItemInstances) {
		if (Item) {
			Item->ResetStat();
		}
	}
}

void UInventory::ResetItemUse()
{
	for (UItemInstance* Item : ItemInstances) {
		if (Item) {
			Item->IsUsed = false;
		}
	}
}

TArray<UCardInstance*> UInventory::ConstructDeck()
{
	TArray<UCardInstance*> CardArray;
	for (UItem* Item : EquippedItems) {
		if(Item)
			for (UCard* CardData : Item->Cards) {
				UCardInstance* Card = NewObject<UCardInstance>();
				Card->CardData = CardData;
				Card->Genre = Item->Genre;
				CardArray.Add(Card);
			}
	}
	return CardArray;
}
