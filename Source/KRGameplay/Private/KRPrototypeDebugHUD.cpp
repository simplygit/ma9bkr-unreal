#include "KRPrototypeDebugHUD.h"

#include "Engine/Engine.h"

#include "KRPrototypeGameState.h"

namespace
{
    FString DescribePhase(EKRMatchPhase Phase)
    {
        switch (Phase)
        {
        case EKRMatchPhase::Boot:
            return TEXT("Boot");
        case EKRMatchPhase::Warmup:
            return TEXT("Warmup");
        case EKRMatchPhase::FirstPitch:
            return TEXT("FirstPitch");
        case EKRMatchPhase::BallInPlay:
            return TEXT("BallInPlay");
        case EKRMatchPhase::DeadBall:
            return TEXT("DeadBall");
        case EKRMatchPhase::HalfInningEnd:
            return TEXT("HalfInningEnd");
        case EKRMatchPhase::Final:
            return TEXT("Final");
        default:
            return TEXT("Unknown");
        }
    }

    FString DescribeOutcome(EKRPrototypeAtBatOutcome Outcome)
    {
        switch (Outcome)
        {
        case EKRPrototypeAtBatOutcome::None:
            return TEXT("None");
        case EKRPrototypeAtBatOutcome::StrikeOut:
            return TEXT("StrikeOut");
        case EKRPrototypeAtBatOutcome::Single:
            return TEXT("Single");
        case EKRPrototypeAtBatOutcome::Double:
            return TEXT("Double");
        case EKRPrototypeAtBatOutcome::HomeRun:
            return TEXT("HomeRun");
        case EKRPrototypeAtBatOutcome::Walk:
            return TEXT("Walk");
        case EKRPrototypeAtBatOutcome::FieldOut:
            return TEXT("FieldOut");
        case EKRPrototypeAtBatOutcome::DoublePlay:
            return TEXT("DoublePlay");
        default:
            return TEXT("Unknown");
        }
    }

    FString DescribeBases(const FKRBaseOccupancy& Bases)
    {
        return FString::Printf(
            TEXT("1B:%s 2B:%s 3B:%s"),
            Bases.bFirstBaseOccupied ? TEXT("On") : TEXT("Off"),
            Bases.bSecondBaseOccupied ? TEXT("On") : TEXT("Off"),
            Bases.bThirdBaseOccupied ? TEXT("On") : TEXT("Off"));
    }
}

void AKRPrototypeDebugHUD::DrawHUD()
{
    Super::DrawHUD();

    const AKRPrototypeGameState* PrototypeGameState = GetWorld() ? GetWorld()->GetGameState<AKRPrototypeGameState>() : nullptr;
    if (PrototypeGameState == nullptr)
    {
        DrawText(TEXT("KR Prototype Debug HUD: GameState unavailable"), FLinearColor::Red, 40.0f, 40.0f, GEngine->GetSmallFont(), 1.0f, false);
        return;
    }

    const FKRPrototypeMatchState& MatchState = PrototypeGameState->GetMatchState();

    TArray<FString> Lines;
    Lines.Add(TEXT("KR Prototype Match Debug"));
    Lines.Add(FString::Printf(TEXT("Phase: %s"), *DescribePhase(MatchState.Phase)));
    Lines.Add(FString::Printf(
        TEXT("Inning: %d %s  Score Away %d : Home %d"),
        MatchState.Inning,
        MatchState.bTopOfInning ? TEXT("Top") : TEXT("Bottom"),
        MatchState.Score.AwayRuns,
        MatchState.Score.HomeRuns));
    Lines.Add(FString::Printf(TEXT("Count: %d Ball / %d Strike / %d Out"), MatchState.Balls, MatchState.Strikes, MatchState.Outs));
    Lines.Add(FString::Printf(TEXT("Offense: %s  Defense: %s"), *MatchState.CurrentOffenseSide, *MatchState.CurrentDefenseSide));
    Lines.Add(FString::Printf(TEXT("Batter Slot: %s  Pitcher Slot: %s"), *MatchState.CurrentBatterSlotName, *MatchState.CurrentPitcherSlotName));
    Lines.Add(FString::Printf(TEXT("Bases: %s"), *DescribeBases(MatchState.Bases)));
    Lines.Add(FString::Printf(TEXT("Plate Appearances: %d"), MatchState.PlateAppearanceCount));
    Lines.Add(FString::Printf(TEXT("Last Outcome: %s"), *DescribeOutcome(MatchState.LastAtBatOutcome)));
    Lines.Add(FString::Printf(TEXT("Last Replay: %s"), *MatchState.LastReplaySampleName));
    Lines.Add(FString::Printf(TEXT("Summary: %s"), *MatchState.LastOutcomeSummary));
    Lines.Add(TEXT("Controls: N=Next Sequence  B=Ball  S=Strike  O=Out"));

    const float OriginX = 28.0f;
    const float OriginY = 28.0f;
    const float PanelWidth = 760.0f;
    const float PanelHeight = 230.0f;
    DrawRect(FLinearColor(0.0f, 0.0f, 0.0f, 0.65f), OriginX - 12.0f, OriginY - 12.0f, PanelWidth, PanelHeight);

    float Y = OriginY;
    for (const FString& Line : Lines)
    {
        DrawText(Line, FLinearColor::Yellow, OriginX, Y, GEngine->GetMediumFont(), 1.0f, false);
        Y += 20.0f;
    }
}
