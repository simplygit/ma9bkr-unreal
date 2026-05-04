#pragma once

#include "Subsystems/GameInstanceSubsystem.h"

#include "KRPrototypeBaselineAsset.h"
#include "KRGameplayBootstrapSubsystem.generated.h"

class UKRLegacyBridgeSubsystem;

UCLASS()
class KRGAMEPLAY_API UKRGameplayBootstrapSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintPure, Category="Bootstrap")
    bool HasLegacyBridge() const;

    UFUNCTION(BlueprintPure, Category="Bootstrap")
    FString DescribeBootstrapStatus() const;

    UFUNCTION(BlueprintPure, Category="Bootstrap")
    const FKRPrototypeBootstrapSummary& GetBootstrapSummary() const;

private:
    bool bLegacyBridgeAvailable = false;
    FKRPrototypeBootstrapSummary BootstrapSummary;
};
