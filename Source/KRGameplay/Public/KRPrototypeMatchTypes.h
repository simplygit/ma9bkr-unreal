#pragma once

#include "KRPrototypeMatchTypes.generated.h"

UENUM(BlueprintType)
enum class EKRMatchPhase : uint8
{
    Boot,
    Warmup,
    FirstPitch,
    BallInPlay,
    DeadBall,
    HalfInningEnd,
    Final
};

USTRUCT(BlueprintType)
struct KRGAMEPLAY_API FKRScoreLine
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    int32 AwayRuns = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    int32 HomeRuns = 0;
};

USTRUCT(BlueprintType)
struct KRGAMEPLAY_API FKRBaseOccupancy
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    bool bFirstBaseOccupied = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    bool bSecondBaseOccupied = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    bool bThirdBaseOccupied = false;
};

USTRUCT(BlueprintType)
struct KRGAMEPLAY_API FKRPrototypeMatchState
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    EKRMatchPhase Phase = EKRMatchPhase::Boot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    int32 Inning = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    bool bTopOfInning = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    int32 Outs = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    int32 Balls = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    int32 Strikes = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    FKRScoreLine Score;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match")
    FKRBaseOccupancy Bases;
};
