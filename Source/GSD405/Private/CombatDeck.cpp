// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatDeck.h"

void UCombatDeck::Draw(int NumCards)
{
	int HandSize = Hand.Num();
	int CardsToBeDrawn = (MAX_HAND_SIZE - HandSize > NumCards) ? NumCards : MAX_HAND_SIZE - HandSize;
	for (int i = 0; i < CardsToBeDrawn; i++) {
		if (DrawDeck.IsEmpty()) 
			Shuffle();
		if (DrawDeck.IsEmpty()) {
			
		}
		else {
			UCard* DrawnCard = DrawDeck.Pop();
			Hand.Add(DrawnCard);
			DrawDelegate.Broadcast(DrawnCard);
		}
	}
}

void UCombatDeck::Discard(UCard* Card)
{
	Hand.RemoveSingle(Card);
	DiscardDeck.Add(Card);
}

void UCombatDeck::DiscardHand()
{
	verify(0);
	DiscardDeck.Append(Hand);
	Hand.Empty();
}

void UCombatDeck::Shuffle()
{
	DrawDeck.Append(DiscardDeck);
	DiscardDeck.Empty();

	for (int _ = 0; _ < NUM_SHUFFLES; _++) {
		for (int i = 0; i < DrawDeck.Num(); i++) {
			int SwapIndex = FMath::RandRange(i, DrawDeck.Num() - 1);
			DrawDeck.Swap(i, SwapIndex);
		}
	}

}

TArray<UCard*> UCombatDeck::GetHand()
{
	return Hand;
}

void UCombatDeck::InitDeck(TArray<UCard*> Deck)
{
	DrawDeck = Deck;
	DiscardDeck.Empty();
	Hand.Empty();
}
