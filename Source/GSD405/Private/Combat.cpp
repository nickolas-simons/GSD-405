// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat.h"

UCombat::UCombat()
{
	
}

void UCombat::StartCombat()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (PlayerCharacter) {
		ACombatant* PlayerRef = Cast<ACombatant>(PlayerCharacter);
		TurnOrder.Add(PlayerRef);
	}
	SpawnEnemies();
	Setup();

	NextTurn();
}

void UCombat::NextTurn()
{
	if (TurnOrder.IsEmpty())
		return;

	Current++;
	Current %= TurnOrder.Num();

	if (Current == 0)
		RoundStart();
	
	UE_LOG(LogTemp, Log, TEXT("TURN %d"), Current);
	ACombatant* CurrentCombatant = TurnOrder[Current];
	if (CurrentCombatant->isAlive)
		CurrentCombatant->StartTurn();
	else
		NextTurn();
}

void UCombat::RoundStart()
{
	for (ACombatant* Combatant : TurnOrder) {
		Combatant->CallEffectEvent(EEffectEvent::RoundStart, nullptr);
	}
}

void UCombat::EndCombat()
{
	TurnOrder.Empty();
	Current = -1;
	ACombatant* Player = Cast<ACombatant>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	Player->CombatEnd();
}

 void UCombat::GetTargetArray(ACombatant* Focus, TArray<ACombatant*>& ReturnArray)
{
	ReturnArray.Append(TurnOrder);
	if (Focus == TurnOrder[0]) {
		return;
	}
	ReturnArray.RemoveAt(0);
	ReturnArray.Remove(Focus);
	ReturnArray.Add(Focus);
	ReturnArray.Add(TurnOrder[0]);
	return;

}

 TArray<ACombatant*> UCombat::GetAdjacent(ACombatant* Target)
 {
	TArray<ACombatant*> ReturnArray;
	int i = TurnOrder.Find(Target);
	if (i == 0)
		 return ReturnArray;
	if (i + 1 < TurnOrder.Num())
		 ReturnArray.Add(TurnOrder[i + 1]);
	if (i - 1 > 0)
		ReturnArray.Add(TurnOrder[i - 1]);
	return ReturnArray;
 }

void UCombat::DistributeRewards_Implementation()
{
}

bool UCombat::AreEnemiesDefeated()
{
	ACombatant* Player = Cast<ACombatant>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	for (ACombatant* Combatant : TurnOrder) {
		if (Player != Combatant) {
			if (Combatant->isAlive)
				return false;
		}
	}
	return true;
}



bool UCombat::IsPlayerDefeated()
{
	ACombatant* Player = Cast<ACombatant>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player->isAlive)
		return true;
	return false;
}

void UCombat::CheckGameEnd()
{
	if (IsPlayerDefeated()) {
		EndCombat();
		return;
	}

	if (AreEnemiesDefeated()) {
		DistributeRewards();
		EndCombat();
		return;
	}
}

void UCombat::Setup()
{
	for (ACombatant* Combatant : TurnOrder) {
		Combatant->StartCombat();
		Combatant->EndTurnDelegate.BindUObject(this, &UCombat::NextTurn);
		Combatant->DeathDelegate.BindUObject(this, &UCombat::CheckGameEnd);
		Combatant->GetTargetsDelegate.BindUObject(this, &UCombat::GetTargetArray);
	}
}

void UCombat::SpawnEnemies()
{
	FVector SpawnLocation = GetOwner()->GetActorLocation();
	for (TSubclassOf<ACombatant> EnemyClass : Enemies) {
		FActorSpawnParameters SpawnParams;
		FRotator SpawnRotation = FRotator(0,180,0);
		SpawnLocation += EnemySpawnLocationOffset;

		ACombatant* Enemy = GetWorld()->SpawnActor<ACombatant>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParams);
		TurnOrder.Add(Enemy);
	}
}

