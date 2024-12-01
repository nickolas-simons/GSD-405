// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

UCardInstance::UCardInstance(const UCardInstance& InCard)
{
	CardData = InCard.CardData;
	Genre = InCard.Genre;
}
