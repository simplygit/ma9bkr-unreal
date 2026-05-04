#pragma once

#include "Subsystems/GameInstanceSubsystem.h"

#include "KRLegacyTableDescriptor.h"
#include "KRLegacyBridgeSubsystem.generated.h"

UCLASS()
class KRLEGACYBRIDGE_API UKRLegacyBridgeSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintPure, Category="Legacy Bridge")
    const TArray<FKRLegacyTableDescriptor>& GetBaselineTables() const;

    UFUNCTION(BlueprintPure, Category="Legacy Bridge")
    FString GetUnityProjectRoot() const;

    UFUNCTION(BlueprintPure, Category="Legacy Bridge")
    FString GetBaselineDocumentPath() const;

private:
    TArray<FKRLegacyTableDescriptor> BaselineTables;
};
