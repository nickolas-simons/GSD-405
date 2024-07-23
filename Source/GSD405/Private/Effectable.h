// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Effect.h"
#include "GameFramework/Actor.h"
#include "Effectable.generated.h"

// This class does not need to be modified.

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEffectDelegate, UEffect*, Effect);

UINTERFACE(MinimalAPI, NotBlueprintable)
class UEffectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IEffectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual void AddEffect(FEffectInstance CardEffect, UObject* Applier) = 0;

	UFUNCTION(BlueprintCallable)
	virtual void ClearEffects() = 0;

	virtual void CallEffectEvent(EEffectEvent Event, UObject* Payload) = 0;
protected:

	// function used to cull effects marked for removal, prevents index offset errors when removing elements during iteration
	virtual void CullEffects() = 0;
};
