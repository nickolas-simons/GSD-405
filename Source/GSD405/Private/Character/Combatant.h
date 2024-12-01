// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "../EffectSystem/Effectable.h"
#include "../EffectSystem/Skill.h"
#include "Combatant.generated.h"

DECLARE_DELEGATE_TwoParams(FGetTargetsDelegate, ACombatant*, TArray<ACombatant*>&);


UCLASS()
class ACombatant : public APaperZDCharacter, public IEffectable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatant();

	FSimpleDelegate DeathDelegate;

	FSimpleDelegate EndTurnDelegate;

	FGetTargetsDelegate GetTargetsDelegate;

	UFUNCTION(BlueprintCallable)
	int GetHealth();

	UFUNCTION(BlueprintCallable)
	int GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	void AddEffect(FEffectInstance CardEffect, UObject* Applier) override;

	UFUNCTION(BlueprintCallable)
	void ClearEffects() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UseSkill(USkillInstance* Skill);

	UFUNCTION(BlueprintCallable)
	void CallEffectEvent(EEffectEvent Event, UObject* Payload) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Damage(int Damage, UObject* Responsible);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Heal(int HealAmount);

	UFUNCTION(BlueprintNativeEvent)
	void StartTurn();

	UFUNCTION(BlueprintNativeEvent)
	void StartCombat();

	UFUNCTION(BlueprintNativeEvent)
	void CombatEnd();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void EndTurn();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ModifyAP(int Modifier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isAlive = true;

	UPROPERTY(BlueprintReadOnly)
	bool isTurn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* StatusWidget;

	UPROPERTY(BlueprintReadOnly)
	TArray<UEffect*> Effects;

	UPROPERTY(BlueprintReadOnly)
	int Health;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int MaxHealth;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int ActionPoints;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int MaxActionPoints;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<USkillInstance*> Skills;

	UPROPERTY(BlueprintAssignable)
	FEffectDelegate OnAddEffect;

	UPROPERTY(BlueprintAssignable)
	FEffectDelegate OnRemoveEffect;

	UFUNCTION()
	void GetTargets(TEnumAsByte<ETargetingType> TargetingType, TArray<ACombatant*>& ReturnByRef);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintCallable)
	void RefreshAP();

	UFUNCTION()
	virtual void InitializeSkills();

	void CullEffects();
	

public:


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
