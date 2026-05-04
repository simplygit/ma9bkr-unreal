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
    FString SourceSheet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 CardIndex = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 SeasonYear = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString TeamName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString PlayerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString PrimaryPosition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 BattingOrder = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString DefensivePosition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    bool bStartingLineup = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    bool bDefensiveStarter = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    bool bDesignatedHitter = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 Overall = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 Power = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 Contact = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 RunSpeed = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 DefenseSpeed = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 DefenseRange = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 ThrowPower = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 ThrowSkill = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 Agility = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 Stamina = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 Control = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 BallSpeed = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString PitchArsenalSummary;

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
    FString SourceSheet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString KeyColumn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString KeyValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString LinkedSceneTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString Notes;
};

USTRUCT(BlueprintType)
struct KRGAMEPLAY_API FKRPrototypeReplayLinkDescriptor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString SampleName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 ConditionStateId = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString ConditionStateTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    int32 SceneId = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    FString SceneTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    TArray<int32> ShotSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Baseline")
    TArray<int32> CameraSequence;

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
    TArray<FKRPrototypeReplayLinkDescriptor> ReplayLinks;

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
    TArray<FKRPrototypeReplayLinkDescriptor> ReplayLinks;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Baseline")
    TArray<FKRLegacyTableDescriptor> BaselineTables;
};
