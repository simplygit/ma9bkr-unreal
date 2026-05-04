#include "KRGameplayBootstrapSubsystem.h"

#include "KRLegacyBridgeSubsystem.h"

void UKRGameplayBootstrapSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    const UKRLegacyBridgeSubsystem* LegacyBridge = GetGameInstance()->GetSubsystem<UKRLegacyBridgeSubsystem>();
    bLegacyBridgeAvailable = LegacyBridge != nullptr;

    BootstrapSummary = FKRPrototypeBootstrapSummary();
    BootstrapSummary.Stadium.LogicalName = TEXT("JamsilPrimary");
    BootstrapSummary.Stadium.UnityScenePath = TEXT("Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil.unity");
    BootstrapSummary.Stadium.TargetUnrealMapPath = TEXT("/Game/Maps/Stadiums/L_Jamsil_Prototype");
    BootstrapSummary.Stadium.DeferredVariants = {
        TEXT("Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil_Night.unity"),
        TEXT("Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil_Toon.unity"),
        TEXT("Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil_Night_Toon.unity")
    };
    BootstrapSummary.Stadium.Notes = TEXT("Primary stadium baseline selected from Phase 1 document.");

    BootstrapSummary.PlayerSlots = {
        { TEXT("PrimaryPitcher"), EKRPrototypeRosterRole::Pitcher, EKRPrototypeHandedness::Right, TEXT("Legacy starter pitcher baseline"), TEXT("Use as first migrated throwing profile.") },
        { TEXT("PrimaryBatter"), EKRPrototypeRosterRole::Batter, EKRPrototypeHandedness::Right, TEXT("Legacy lead-off batter baseline"), TEXT("Use as first migrated batting/contact profile.") },
        { TEXT("PrimaryFielder"), EKRPrototypeRosterRole::Fielder, EKRPrototypeHandedness::Right, TEXT("Legacy center-field style baseline"), TEXT("Use as first migrated chase/catch profile.") }
    };

    BootstrapSummary.ReplaySamples = {
        { TEXT("FirstPitchContact"), TEXT("Tables/09_인게임/마구B_리플레이.xlsx"), TEXT("First-contact replay baseline"), TEXT("Representative replay source to validate pitch/contact flow.") },
        { TEXT("BallInPlayFielding"), TEXT("Tables/09_인게임/마구B_리플레이.xlsx"), TEXT("Fielding follow-up baseline"), TEXT("Representative replay source to validate chase and catch timing.") }
    };

    if (LegacyBridge != nullptr)
    {
        BootstrapSummary.BaselineTables = LegacyBridge->GetBaselineTables();
    }
}

void UKRGameplayBootstrapSubsystem::Deinitialize()
{
    bLegacyBridgeAvailable = false;
    BootstrapSummary = FKRPrototypeBootstrapSummary();

    Super::Deinitialize();
}

bool UKRGameplayBootstrapSubsystem::HasLegacyBridge() const
{
    return bLegacyBridgeAvailable;
}

FString UKRGameplayBootstrapSubsystem::DescribeBootstrapStatus() const
{
    return bLegacyBridgeAvailable
        ? TEXT("Legacy bridge ready for baseline table and document access.")
        : TEXT("Legacy bridge subsystem is not available.");
}

const FKRPrototypeBootstrapSummary& UKRGameplayBootstrapSubsystem::GetBootstrapSummary() const
{
    return BootstrapSummary;
}
