#pragma once

#include "Engine/DeveloperSettings.h"

#include "KRMigrationDeveloperSettings.generated.h"

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="KR Migration Settings"))
class KRCORE_API UKRMigrationDeveloperSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UKRMigrationDeveloperSettings();

    virtual FName GetCategoryName() const override;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Workspace")
    FString UnityProjectRoot;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Workspace")
    FString UnrealWorkspaceRoot;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Workspace")
    FString MigrationDocsRoot;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Baseline")
    FString BaselineDocumentPath;
};
