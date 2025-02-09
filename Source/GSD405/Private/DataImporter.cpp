#include "DataImporter.h"

void UDataImporter::ImportCSVToDataAssets(const FString& FilePath, TEnumAsByte<EDataAssetType> Type)
{
    TArray<FString> FileLines;
    if (!FFileHelper::LoadFileToStringArray(FileLines, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load CSV file: %s"), *FilePath);
        return;
    }

    // Skip header row and process lines
    for (int32 i = 1; i < FileLines.Num(); i++)
    {
        switch (Type)
        {
        case Card:      InitCard(FileLines[i]); break;
        case Equipment: InitEquipment(FileLines[i]); break;
        case Skill:     InitSkill(FileLines[i]); break;
        default:
            UE_LOG(LogTemp, Warning, TEXT("Unknown Data Asset Type"));
            break;
        }
    }
}

void UDataImporter::InitCard(const FString& ParseString)
{
    TArray<FString> Columns;
    ParseString.ParseIntoArray(Columns, TEXT(","), true);

    if (Columns.Num() < 6) // Ensure sufficient columns
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Card Data Format"));
        return;
    }

    // Extract values
    FString AssetFileName = Columns[0];
    FText CardName = FText::FromString(Columns[1]);
    FString TexturePath = FString::Printf(TEXT("/Game/Textures/Cards/%s.%s"), *Columns[2], *Columns[2]);
    FText CardDescription = FText::FromString(Columns[3]);
    int32 ActionPointCost = FCString::Atoi(*Columns[4]);
    TArray<FEffectInstance> ParsedEffects = ParseEffects(Columns[5]);

    // Create or update asset
    FString AssetPath = FString::Printf(TEXT("/Game/DataAssets/Cards/%s"), *AssetFileName);
    UCard* CardAsset = Cast<UCard>(StaticLoadObject(UCard::StaticClass(), nullptr, *AssetPath));

    if (!CardAsset)
    {
        CardAsset = NewObject<UCard>(GetTransientPackage(), UCard::StaticClass(), FName(*AssetFileName), RF_Public | RF_Standalone);
        if (!CardAsset) return;
    }

    // Assign values
    CardAsset->CardName = CardName;
    CardAsset->CardThumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *TexturePath));
    CardAsset->CardDescription = CardDescription;
    CardAsset->ActionPointCost = ActionPointCost;
    CardAsset->Effects = ParsedEffects;

    SaveAsset(CardAsset, AssetPath, AssetFileName);
}

void UDataImporter::InitEquipment(const FString& ParseString)
{
    TArray<FString> Columns;
    ParseString.ParseIntoArray(Columns, TEXT(","), true);

    if (Columns.Num() < 10)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Equipment Data Format"));
        return;
    }

    FString AssetFileName = Columns[0];
    FString AssetPath = FString::Printf(TEXT("/Game/DataAssets/Items/%s"), *AssetFileName);
    FString TexturePath = FString::Printf(TEXT("/Game/Textures/Items/%s.%s"), *Columns[3], *Columns[3]);
    UEquipment* EquipmentAsset = Cast<UEquipment>(StaticLoadObject(UEquipment::StaticClass(), nullptr, *AssetPath));

    if (!EquipmentAsset)
    {
        EquipmentAsset = NewObject<UEquipment>(GetTransientPackage(), UEquipment::StaticClass(), FName(*AssetFileName), RF_Public | RF_Standalone);
        if (!EquipmentAsset) return;
    }

    EquipmentAsset->ItemName = FText::FromString(Columns[1]);
    EquipmentAsset->ItemThumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *TexturePath));
    EquipmentAsset->ItemDescription = FText::FromString(Columns[2]);
    EquipmentAsset->ItemSize = FItemDimension(FCString::Atoi(*Columns[4]), FCString::Atoi(*Columns[5]));
    EquipmentAsset->Cards = ParseCards(Columns[6]);
    EquipmentAsset->Skills = ParseSkills(Columns[8]);
    EquipmentAsset->Genre = static_cast<EGenre>(StaticEnum<EGenre>()->GetValueByNameString(Columns[9]));
    EquipmentAsset->Type = static_cast<EEquipmentType>(StaticEnum<EEquipmentType>()->GetValueByNameString(Columns[7]));

    SaveAsset(EquipmentAsset, AssetPath, AssetFileName);
}

void UDataImporter::SaveAsset(UObject* Asset, const FString& AssetPath, const FString& AssetFileName)
{
    if (!Asset) return;

    UPackage* Package = CreatePackage(*AssetPath);
    Asset->Rename(*AssetFileName, Package);

    FAssetRegistryModule::AssetCreated(Asset);
    Package->MarkPackageDirty();

    FString PackageFileName = FPackageName::LongPackageNameToFilename(AssetPath, FPackageName::GetAssetPackageExtension());
    UPackage::SavePackage(Package, Asset, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName);
}

// Helper Functions
TArray<FEffectInstance> UDataImporter::ParseEffects(const FString& EffectString)
{
    TArray<FEffectInstance> Effects;
    TArray<FString> EffectPairs;
    EffectString.ParseIntoArray(EffectPairs, TEXT(";"), true);

    for (const FString& EffectPair : EffectPairs)
    {
        TArray<FString> Components;
        EffectPair.ParseIntoArray(Components, TEXT(":"), true);

        if (Components.Num() == 2)
        {
            UClass* EffectClass = LoadEffectClass(Components[0]);

            if (EffectClass)
                Effects.Add({ EffectClass, FCString::Atoi(*Components[1]) });
        }
    }
    return Effects;
}

TArray<FItemCard> UDataImporter::ParseCards(const FString& CardString)
{
    TArray<FItemCard> Cards;
    TArray<FString> CardEntries;
    CardString.ParseIntoArray(CardEntries, TEXT(";"), true);

    for (const FString& Entry : CardEntries)
    {
        TArray<FString> Components;
        Entry.ParseIntoArray(Components, TEXT(":"), true);

        if (Components.Num() == 2)
        {
            FString CardPath = FString::Printf(TEXT("/Game/DataAssets/Cards/%s.%s"), *Components[0], *Components[0]);
            UCard* LoadedCard = Cast<UCard>(StaticLoadObject(UCard::StaticClass(), nullptr, *CardPath));

            if (LoadedCard)
            {
                Cards.Add({ LoadedCard, static_cast<EGenre>(StaticEnum<EGenre>()->GetValueByNameString(Components[1])) });
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to load card: %s"), *CardPath);
            }
        }
    }
    return Cards;
}

FString UDataImporter::OpenCSVFileDialog()
{
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (!DesktopPlatform) return FString();

    TArray<FString> OutFiles;
    const void* ParentWindowHandle = nullptr;

    bool bSuccess = DesktopPlatform->OpenFileDialog(
        ParentWindowHandle,
        TEXT("Select a CSV File"),
        TEXT(""),
        TEXT(""),
        TEXT("CSV Files (*.csv)|*.csv"),
        EFileDialogFlags::None,
        OutFiles
    );

    return bSuccess && OutFiles.Num() > 0 ? OutFiles[0] : FString();
}

TArray<FSkillVariant> UDataImporter::ParseSkills(const FString& EffectString)
{
    TArray<FSkillVariant> Effects;
    TArray<FString> EffectPairs;
    EffectString.ParseIntoArray(EffectPairs, TEXT(";"), true);
    TArray<FSkillVariant> SkillVariants;
    TArray<FString> SkillEntries;
    EffectString.ParseIntoArray(SkillEntries, TEXT(";"), true);

    const int32 NumFieldsPerSkill = 3;
    if (SkillEntries.Num() % NumFieldsPerSkill != 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid input format for SkillVariant list."));
        return SkillVariants;
    }

    for (int32 i = 0; i < SkillEntries.Num(); i += NumFieldsPerSkill)
    {
        FSkillVariant SkillVariant;

        // Extract skill name and find object
        FString SkillPath = FString::Printf(TEXT("/Script/GSD405.Skill'/Game/DataAssets/Skills/%s.%s'"), *SkillEntries[i], *SkillEntries[i]);
        SkillVariant.Skill = Cast<USkill>(StaticLoadObject(USkill::StaticClass(), nullptr, *SkillPath));
        if (!SkillVariant.Skill)
        {
            UE_LOG(LogTemp, Warning, TEXT("Skill '%s' not found."), *SkillPath);
            continue;
        }

        // Extract magnitude
        SkillVariant.Magnitude = FCString::Atoi(*SkillEntries[i + 1]);

        // Extract skill requirements
        TArray<FString> Requirements;
        SkillEntries[i + 2].ParseIntoArray(Requirements, TEXT("|"), true);

        for (const FString& Requirement : Requirements)
        {
            TArray<FString> GenrePair;
            Requirement.ParseIntoArray(GenrePair, TEXT(":"), true);
            if (GenrePair.Num() == 2)
            {
                FCardGenreCount GenreCount;

                // Convert string to ECardGenre using the enum system
                int FoundGenre = StaticEnum<EGenre>()->GetValueByNameString(GenrePair[0]);
                if (FoundGenre)
                {
                    GenreCount.Genre = static_cast<EGenre>(FoundGenre);
                    GenreCount.Count = FCString::Atoi(*GenrePair[1]);
                    SkillVariant.SkillRequirement.Add(GenreCount);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Invalid genre name: %s"), *GenrePair[0]);
                }
            }
        }
        SkillVariants.Add(SkillVariant);
    }
    return SkillVariants;
}

void UDataImporter::InitSkill(const FString& ParseString)
{
    TArray<FString> Columns;
    ParseString.ParseIntoArray(Columns, TEXT(","), true);

    if (Columns.Num() < 5) // Ensure sufficient columns
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Skill Data Format"));
        return;
    }

    // Extract values
    FString AssetFileName = Columns[0];
    FText SkillName = FText::FromString(Columns[1]);
    FString TexturePath = FString::Printf(TEXT("/Game/Textures/Skills/%s.%s"), *Columns[2], *Columns[3]);
    FText SkillDescription = FText::FromString(Columns[2]);
    TSubclassOf<UEffect> Effect = LoadEffectClass(Columns[4]);
    ETargetingType DefaultTargeting = static_cast<ETargetingType>(FCString::Atoi(*Columns[5]));

    // Create or update asset
    FString AssetPath = FString::Printf(TEXT("/Game/DataAssets/Skills/%s"), *AssetFileName);
    USkill* SkillAsset = Cast<USkill>(StaticLoadObject(USkill::StaticClass(), nullptr, *AssetPath));

    if (!SkillAsset)
    {
        SkillAsset = NewObject<USkill>(GetTransientPackage(), USkill::StaticClass(), FName(*AssetFileName), RF_Public | RF_Standalone);
        if (!SkillAsset) return;
    }

    // Assign values
    SkillAsset->SkillName = SkillName;
    SkillAsset->SkillThumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *TexturePath));
    SkillAsset->SkillDescription = SkillDescription;
    SkillAsset->Effect = Effect;
    SkillAsset->DefaultTargeting = DefaultTargeting;

    SaveAsset(SkillAsset, AssetPath, AssetFileName);
}

TSubclassOf<UEffect> UDataImporter::LoadEffectClass(const FString& EffectPath)
{
    FString FullEffectPath = FString::Printf(TEXT("/Game/Blueprints/Effects/%s.%s_C"), *EffectPath, *EffectPath);
    UClass* EffectClass = StaticLoadClass(UEffect::StaticClass(), nullptr, *FullEffectPath);

    if (EffectClass && EffectClass->IsChildOf(UEffect::StaticClass()))
    {
        return EffectClass;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load effect: %s"), *FullEffectPath);
        return nullptr;
    }
}