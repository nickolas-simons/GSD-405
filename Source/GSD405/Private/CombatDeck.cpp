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
			UCardInstance* DrawnCard = DrawDeck.Pop();
			Hand.Add(DrawnCard);
			DrawDelegate.Broadcast(DrawnCard);
		}
	}
}

void UCombatDeck::Discard(UCardInstance* Card)
{
	Hand.RemoveSingle(Card);
	DiscardDeck.Add(Card);
}

void UCombatDeck::DiscardHand()
{
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

TArray<UCardInstance*> UCombatDeck::GetHand()
{
	return Hand;
}

void UCombatDeck::InitDeck(TArray<UCardInstance*> Deck)
{
	DiscardHand();
	DiscardDeck.Empty();
	DrawDeck = Deck;
}
