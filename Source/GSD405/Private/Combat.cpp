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
	Current++;
	Current %= TurnOrder.Num();

	if (Current == 0)
		RoundStart();

	if (AreEnemiesDefeated()) {
		EndCombat();
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("TURN %d"), Current);
	ACombatant* CurrentCombatant = TurnOrder[Current];
	CurrentCombatant->StartTurn();
}

void UCombat::RoundStart()
{
	for (ACombatant* Combatant : TurnOrder) {
		Combatant->CallCardEvents(ECardEvent::RoundStart, nullptr);
	}
}

void UCombat::EndCombat()
{
	TurnOrder.Empty();
	Current = -1;
	ACombatant* Player = Cast<ACombatant>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	Player->CombatEnd();
}

bool UCombat::AreEnemiesDefeated()
{
	ACombatant* Player = Cast<ACombatant>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player->isAlive)
		return true;

	for (ACombatant* Combatant : TurnOrder) {
		if (Player != Combatant && Combatant->isAlive)
			return false;
	}
	return true;
}

void UCombat::Setup()
{
	for (ACombatant* Combatant : TurnOrder) {
		Combatant->StartCombat();
		Combatant->EndTurnDelegate.BindUFunction(this, FName("NextTurn"));
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
