#pragma once

#include "Engine/DataAsset.h"

#include "KRLegacyTableDescriptor.h"
#include "KRPrototypeBaselineAsset.generated.h"

UENUM(BlueprintType)
enum class EKRPrototypeHandedness : uint8
{
    Right,
    Left,
    Switch
};

UENUM(BlueprintType)
enum class EKRPrototypeRosterRole : uint8
{
    Pitcher,
    Batter,
    Fielder,
    Utility
};

USTRUCT(BlueprintType)
struct KRGAMEPLAY_API FKRPrototypeStadiumDescriptor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString LogicalName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString UnityScenePath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString TargetUnrealMapPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    TArray<FString> DeferredVariants;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString Notes;
};

USTRUCT(BlueprintType)
struct KRGAMEPLAY_API FKRPrototypePlayerSlotDescriptor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString SlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    EKRPrototypeRosterRole Role = EKRPrototypeRosterRole::Utility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    EKRPrototypeHandedness Handedness = EKRPrototypeHandedness::Right;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString LegacySourceHint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString Notes;
};

USTRUCT(BlueprintType)
struct KRGAMEPLAY_API FKRPrototypeReplaySampleDescriptor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString SampleName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString SourceRelativePath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString IntendedUse;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString Notes;
};

USTRUCT(BlueprintType)
struct KRGAMEPLAY_API FKRPrototypeBootstrapSummary
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FKRPrototypeStadiumDescriptor Stadium;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    TArray<FKRPrototypePlayerSlotDescriptor> PlayerSlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    TArray<FKRPrototypeReplaySampleDescriptor> ReplaySamples;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    TArray<FKRLegacyTableDescriptor> BaselineTables;
};

UCLASS(BlueprintType)
class KRGAMEPLAY_API UKRPrototypeBaselineAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Baseline")
    FKRPrototypeStadiumDescriptor Stadium;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Baseline")
    TArray<FKRPrototypePlayerSlotDescriptor> PlayerSlots;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Baseline")
    TArray<FKRPrototypeReplaySampleDescriptor> ReplaySamples;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Baseline")
    TArray<FKRLegacyTableDescriptor> BaselineTables;
};
