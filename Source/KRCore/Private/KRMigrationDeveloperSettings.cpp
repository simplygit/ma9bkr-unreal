#include "KRMigrationDeveloperSettings.h"

UKRMigrationDeveloperSettings::UKRMigrationDeveloperSettings()
{
    UnityProjectRoot = TEXT("F:/workspace_f/KR_trunk");
    UnrealWorkspaceRoot = TEXT("F:/workspace_f/KR_unreal");
    MigrationDocsRoot = TEXT("F:/workspace_f/KR_trunk/docs/tasks/2026-04-29-unity-to-unreal-migration");
    BaselineDocumentPath = TEXT("F:/workspace_f/KR_trunk/docs/tasks/2026-04-29-unity-to-unreal-migration/artifacts/phase-1-baseline.md");
}

FName UKRMigrationDeveloperSettings::GetCategoryName() const
{
    return TEXT("Project");
}
