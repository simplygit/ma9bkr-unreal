#include "KRLegacyBridgeSubsystem.h"

#include "KRMigrationDeveloperSettings.h"

void UKRLegacyBridgeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    BaselineTables.Reset();
    BaselineTables.Append({
        { TEXT("AI"), TEXT("Tables/09_인게임/마구B_AI테이블.xlsx"), TEXT("AI tuning and decision support baseline"), EKRLegacyTablePriority::Critical, { TEXT("AI") } },
        { TEXT("Replay"), TEXT("Tables/09_인게임/마구B_리플레이.xlsx"), TEXT("Replay and comparison baseline"), EKRLegacyTablePriority::Critical, { TEXT("Replay") } },
        { TEXT("Camera"), TEXT("Tables/09_인게임/마구B_인게임카메라.xlsx"), TEXT("Camera parameter baseline"), EKRLegacyTablePriority::Critical, { TEXT("Camera") } },
        { TEXT("BallInPlay"), TEXT("Tables/09_인게임/마구B_인게임타구.xlsx"), TEXT("Ball-in-play parameter baseline"), EKRLegacyTablePriority::Critical, { TEXT("BallInPlay") } },
        { TEXT("Animation"), TEXT("Tables/09_인게임/마구B_인게임애니메이션세팅.xlsx"), TEXT("Animation tuning reference"), EKRLegacyTablePriority::Recommended, { TEXT("Animation") } },
        { TEXT("Sound"), TEXT("Tables/09_인게임/마구B_인게임사운드.xlsx"), TEXT("In-game sound event baseline"), EKRLegacyTablePriority::Deferred, { TEXT("Sound") } },
        { TEXT("Intervention"), TEXT("Tables/09_인게임/마구24_개입조작.xlsx"), TEXT("Intervention input and control tuning"), EKRLegacyTablePriority::Recommended, { TEXT("Intervention") } }
    });
}

void UKRLegacyBridgeSubsystem::Deinitialize()
{
    BaselineTables.Reset();

    Super::Deinitialize();
}

const TArray<FKRLegacyTableDescriptor>& UKRLegacyBridgeSubsystem::GetBaselineTables() const
{
    return BaselineTables;
}

FString UKRLegacyBridgeSubsystem::GetUnityProjectRoot() const
{
    return GetDefault<UKRMigrationDeveloperSettings>()->UnityProjectRoot;
}

FString UKRLegacyBridgeSubsystem::GetBaselineDocumentPath() const
{
    return GetDefault<UKRMigrationDeveloperSettings>()->BaselineDocumentPath;
}
