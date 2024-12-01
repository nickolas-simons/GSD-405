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
	bIsOpen = true;
}

void UInventory::CloseInventory_Implementation()
{
	bIsOpen = false;
}

void UInventory::AddItemSelection_Implementation(UPARAM(ref) TArray<UItem*>& Items)
{
}


UEquipment* UInventory::GetItem(EEquipmentSlot Slot)
{
	return EquippedItems[Slot];
}

TArray<UCardInstance*> UInventory::ConstructDeck()
{
	TArray<UCardInstance*> CardArray;
	for (UEquipment* Item : EquippedItems) {
		if(Item)
			for (FItemCard CardData : Item->Cards) {
				UCardInstance* Card = NewObject<UCardInstance>();
				Card->CardData = CardData.Card;
				Card->Genre = CardData.Genre;
				CardArray.Add(Card);
			}
	}
	return CardArray;
}
