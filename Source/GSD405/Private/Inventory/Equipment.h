#pragma once
#include "CoreMinimal.h"
#include "../EffectSystem/Effect.h"
#include "../Deck/Card.h"
#include "Item.h"
#include "../EffectSystem/Skill.h"
#include "Equipment.generated.h"

UENUM(BlueprintType)
enum EEquipmentType
{
	Helmet = 0	UMETA(DisplayName = "Helmet"),
	Armor = 1		UMETA(DisplayName = "Armor"),
	Weapon = 2		UMETA(DisplayName = "Weapon"),
	LegArmor = 3			UMETA(DisplayName = "Legs")
};

UCLASS(Blueprintable, BlueprintType)
class UEquipment : public UItem
{
	GENERATED_BODY()

public:

	UEquipment();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FItemCard> Cards;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EEquipmentType> Type;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FSkillVariant> Skills;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EGenre> Genre;
};
