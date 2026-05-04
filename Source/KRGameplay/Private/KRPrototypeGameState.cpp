#include "KRPrototypeGameState.h"

#include "Engine/GameInstance.h"

#include "KRGameplayBootstrapSubsystem.h"

namespace
{
    struct FKRPrototypeSequenceEntry
    {
        EKRPrototypeAtBatOutcome Outcome = EKRPrototypeAtBatOutcome::None;
        const TCHAR* ReplaySampleName = TEXT("");
    };

    static const FKRPrototypeSequenceEntry GPrototypeSequence[] = {
        { EKRPrototypeAtBatOutcome::StrikeOut, TEXT("StrikeOutReplay") },
        { EKRPrototypeAtBatOutcome::Single, TEXT("SingleReplay") },
        { EKRPrototypeAtBatOutcome::FieldOut, TEXT("FieldingOutReplay") },
        { EKRPrototypeAtBatOutcome::Walk, TEXT("WalkPrototype") },
        { EKRPrototypeAtBatOutcome::Double, TEXT("DoublePrototype") },
        { EKRPrototypeAtBatOutcome::HomeRun, TEXT("HomeRunPrototype") },
        { EKRPrototypeAtBatOutcome::DoublePlay, TEXT("DoublePlayPrototype") }
    };

    static bool IsHomeOffense(const FKRPrototypeMatchState& MatchState)
    {
        return !MatchState.bTopOfInning;
    }
}

AKRPrototypeGameState::AKRPrototypeGameState()
{
    MatchState.Phase = EKRMatchPhase::Boot;
}

void AKRPrototypeGameState::StartPrototypeMatch()
{
    MatchState = FKRPrototypeMatchState();
    MatchState.Phase = EKRMatchPhase::FirstPitch;
    MatchState.CurrentPitcherSlotName = TEXT("StarterPitcher");
    MatchState.CurrentOffenseSide = TEXT("Away");
    MatchState.CurrentDefenseSide = TEXT("Home");
    MatchState.LastOutcomeSummary = TEXT("Prototype match started from the Jamsil baseline.");
    RefreshCurrentMatchup();
}

void AKRPrototypeGameState::RecordOut()
{
    MatchState.Outs++;
    MatchState.LastAtBatOutcome = EKRPrototypeAtBatOutcome::FieldOut;
    MatchState.LastReplaySampleName = TEXT("ManualOut");
    MatchState.LastOutcomeSummary = TEXT("Recorded an out.");
    AdvanceHalfInningIfNeeded();
}

void AKRPrototypeGameState::RecordBall()
{
    MatchState.Balls = FMath::Clamp(MatchState.Balls + 1, 0, 4);
    MatchState.Phase = EKRMatchPhase::FirstPitch;

    if (MatchState.Balls >= 4)
    {
        ResolvePrototypeAtBat(EKRPrototypeAtBatOutcome::Walk, TEXT("WalkPrototype"));
        return;
    }

    MatchState.LastOutcomeSummary = TEXT("Recorded a ball.");
}

void AKRPrototypeGameState::RecordStrike()
{
    MatchState.Strikes = FMath::Clamp(MatchState.Strikes + 1, 0, 3);
    MatchState.Phase = EKRMatchPhase::FirstPitch;

    if (MatchState.Strikes >= 3)
    {
        ResolvePrototypeAtBat(EKRPrototypeAtBatOutcome::StrikeOut, TEXT("StrikeOutReplay"));
        return;
    }

    MatchState.LastOutcomeSummary = TEXT("Recorded a strike.");
}

void AKRPrototypeGameState::AddRun(bool bHomeTeamScored)
{
    if (bHomeTeamScored)
    {
        MatchState.Score.HomeRuns++;
    }
    else
    {
        MatchState.Score.AwayRuns++;
    }
}

void AKRPrototypeGameState::ResolvePrototypeAtBat(EKRPrototypeAtBatOutcome Outcome, const FString& ReplaySampleName)
{
    MatchState.LastAtBatOutcome = Outcome;
    MatchState.LastReplaySampleName = ReplaySampleName;
    MatchState.PlateAppearanceCount++;

    switch (Outcome)
    {
    case EKRPrototypeAtBatOutcome::StrikeOut:
        MatchState.Phase = EKRMatchPhase::DeadBall;
        MatchState.LastOutcomeSummary = TEXT("Prototype strikeout resolved.");
        ResetCount();
        MatchState.Outs++;
        AdvanceHalfInningIfNeeded();

        if (MatchState.Phase != EKRMatchPhase::HalfInningEnd)
        {
            AdvanceBatter();
            MatchState.Phase = EKRMatchPhase::FirstPitch;
        }
        break;

    case EKRPrototypeAtBatOutcome::Single:
        MatchState.LastOutcomeSummary = TEXT("Prototype single resolved.");
        ApplySingleOutcome();
        break;

    case EKRPrototypeAtBatOutcome::Double:
        MatchState.LastOutcomeSummary = TEXT("Prototype double resolved.");
        ApplyDoubleOutcome();
        break;

    case EKRPrototypeAtBatOutcome::HomeRun:
        MatchState.LastOutcomeSummary = TEXT("Prototype home run resolved.");
        ApplyHomeRunOutcome();
        break;

    case EKRPrototypeAtBatOutcome::Walk:
        MatchState.LastOutcomeSummary = TEXT("Prototype walk resolved.");
        ApplyWalkOutcome();
        break;

    case EKRPrototypeAtBatOutcome::FieldOut:
        MatchState.Phase = EKRMatchPhase::DeadBall;
        MatchState.LastOutcomeSummary = TEXT("Prototype field out resolved.");
        ResetCount();
        MatchState.Outs++;
        AdvanceHalfInningIfNeeded();

        if (MatchState.Phase != EKRMatchPhase::HalfInningEnd)
        {
            AdvanceBatter();
            MatchState.Phase = EKRMatchPhase::FirstPitch;
        }
        break;

    case EKRPrototypeAtBatOutcome::DoublePlay:
        MatchState.LastOutcomeSummary = TEXT("Prototype double play resolved.");
        ApplyDoublePlayOutcome();
        break;

    default:
        MatchState.LastOutcomeSummary = TEXT("No prototype at-bat outcome was applied.");
        break;
    }
}

void AKRPrototypeGameState::PlayNextPrototypeSequenceStep()
{
    constexpr int32 SequenceLength = static_cast<int32>(sizeof(GPrototypeSequence) / sizeof(FKRPrototypeSequenceEntry));
    const int32 SequenceIndex = MatchState.PlateAppearanceCount % SequenceLength;
    const FKRPrototypeSequenceEntry& SequenceEntry = GPrototypeSequence[SequenceIndex];
    ResolvePrototypeAtBat(SequenceEntry.Outcome, SequenceEntry.ReplaySampleName);
}

const FKRPrototypeMatchState& AKRPrototypeGameState::GetMatchState() const
{
    return MatchState;
}

void AKRPrototypeGameState::ResetCount()
{
    MatchState.Balls = 0;
    MatchState.Strikes = 0;
}

void AKRPrototypeGameState::AdvanceBatter()
{
    int32& BattingOrderIndex = MatchState.bTopOfInning
        ? MatchState.TopBattingOrderIndex
        : MatchState.BottomBattingOrderIndex;

    BattingOrderIndex++;

    if (BattingOrderIndex > 9)
    {
        BattingOrderIndex = 1;
    }

    RefreshCurrentMatchup();
}

void AKRPrototypeGameState::AdvanceHalfInningIfNeeded()
{
    if (MatchState.Outs < 3)
    {
        return;
    }

    MatchState.Outs = 0;
    ResetCount();
    MatchState.Bases = FKRBaseOccupancy();
    MatchState.Phase = EKRMatchPhase::HalfInningEnd;

    if (MatchState.bTopOfInning)
    {
        MatchState.bTopOfInning = false;
        MatchState.CurrentOffenseSide = TEXT("Home");
        MatchState.CurrentDefenseSide = TEXT("Away");
    }
    else
    {
        MatchState.bTopOfInning = true;
        MatchState.Inning++;
        MatchState.CurrentOffenseSide = TEXT("Away");
        MatchState.CurrentDefenseSide = TEXT("Home");
    }

    MatchState.LastOutcomeSummary = TEXT("Half inning complete. Resetting counts and bases.");
    RefreshCurrentMatchup();
}

void AKRPrototypeGameState::ApplySingleOutcome()
{
    MatchState.Phase = EKRMatchPhase::DeadBall;

    const bool bRunnerOnThird = MatchState.Bases.bThirdBaseOccupied;
    const bool bRunnerOnSecond = MatchState.Bases.bSecondBaseOccupied;
    const bool bRunnerOnFirst = MatchState.Bases.bFirstBaseOccupied;

    if (bRunnerOnThird)
    {
        AddRun(IsHomeOffense(MatchState));
    }

    MatchState.Bases.bThirdBaseOccupied = bRunnerOnSecond;
    MatchState.Bases.bSecondBaseOccupied = bRunnerOnFirst;
    MatchState.Bases.bFirstBaseOccupied = true;

    ResetCount();
    AdvanceBatter();
    MatchState.Phase = EKRMatchPhase::FirstPitch;
}

void AKRPrototypeGameState::ApplyDoubleOutcome()
{
    MatchState.Phase = EKRMatchPhase::DeadBall;

    int32 RunsScored = 0;

    if (MatchState.Bases.bThirdBaseOccupied)
    {
        RunsScored++;
    }

    if (MatchState.Bases.bSecondBaseOccupied)
    {
        RunsScored++;
    }

    if (MatchState.Bases.bFirstBaseOccupied)
    {
        MatchState.Bases.bThirdBaseOccupied = true;
    }
    else
    {
        MatchState.Bases.bThirdBaseOccupied = false;
    }

    MatchState.Bases.bSecondBaseOccupied = true;
    MatchState.Bases.bFirstBaseOccupied = false;

    for (int32 Index = 0; Index < RunsScored; ++Index)
    {
        AddRun(IsHomeOffense(MatchState));
    }

    ResetCount();
    AdvanceBatter();
    MatchState.Phase = EKRMatchPhase::FirstPitch;
}

void AKRPrototypeGameState::ApplyHomeRunOutcome()
{
    MatchState.Phase = EKRMatchPhase::DeadBall;

    int32 RunsScored = 1;
    RunsScored += MatchState.Bases.bFirstBaseOccupied ? 1 : 0;
    RunsScored += MatchState.Bases.bSecondBaseOccupied ? 1 : 0;
    RunsScored += MatchState.Bases.bThirdBaseOccupied ? 1 : 0;

    MatchState.Bases = FKRBaseOccupancy();

    for (int32 Index = 0; Index < RunsScored; ++Index)
    {
        AddRun(IsHomeOffense(MatchState));
    }

    ResetCount();
    AdvanceBatter();
    MatchState.Phase = EKRMatchPhase::FirstPitch;
}

void AKRPrototypeGameState::ApplyWalkOutcome()
{
    MatchState.Phase = EKRMatchPhase::DeadBall;

    const bool bRunnerOnFirst = MatchState.Bases.bFirstBaseOccupied;
    const bool bRunnerOnSecond = MatchState.Bases.bSecondBaseOccupied;
    const bool bRunnerOnThird = MatchState.Bases.bThirdBaseOccupied;

    if (bRunnerOnFirst && bRunnerOnSecond && bRunnerOnThird)
    {
        AddRun(IsHomeOffense(MatchState));
    }

    MatchState.Bases.bThirdBaseOccupied = bRunnerOnThird || (bRunnerOnFirst && bRunnerOnSecond);
    MatchState.Bases.bSecondBaseOccupied = bRunnerOnSecond || bRunnerOnFirst;
    MatchState.Bases.bFirstBaseOccupied = true;

    ResetCount();
    AdvanceBatter();
    MatchState.Phase = EKRMatchPhase::FirstPitch;
}

void AKRPrototypeGameState::ApplyDoublePlayOutcome()
{
    MatchState.Phase = EKRMatchPhase::DeadBall;
    ResetCount();

    if (MatchState.Bases.bFirstBaseOccupied)
    {
        MatchState.Bases.bFirstBaseOccupied = false;
        MatchState.Outs += 2;
    }
    else
    {
        MatchState.Outs += 1;
    }

    AdvanceHalfInningIfNeeded();

    if (MatchState.Phase != EKRMatchPhase::HalfInningEnd)
    {
        AdvanceBatter();
        MatchState.Phase = EKRMatchPhase::FirstPitch;
    }
}

void AKRPrototypeGameState::RefreshCurrentMatchup()
{
    const int32 BattingOrderIndex = MatchState.bTopOfInning
        ? MatchState.TopBattingOrderIndex
        : MatchState.BottomBattingOrderIndex;

    MatchState.CurrentBatterSlotName = FString::Printf(TEXT("Lineup%02d"), BattingOrderIndex);

    if (MatchState.CurrentPitcherSlotName.IsEmpty())
    {
        MatchState.CurrentPitcherSlotName = TEXT("StarterPitcher");
    }

    if (MatchState.CurrentOffenseSide.IsEmpty() || MatchState.CurrentDefenseSide.IsEmpty())
    {
        MatchState.CurrentOffenseSide = MatchState.bTopOfInning ? TEXT("Away") : TEXT("Home");
        MatchState.CurrentDefenseSide = MatchState.bTopOfInning ? TEXT("Home") : TEXT("Away");
    }

    if (UGameInstance* GameInstance = GetGameInstance())
    {
        if (const UKRGameplayBootstrapSubsystem* BootstrapSubsystem = GameInstance->GetSubsystem<UKRGameplayBootstrapSubsystem>())
        {
            const FKRPrototypeBootstrapSummary& BootstrapSummary = BootstrapSubsystem->GetBootstrapSummary();

            for (const FKRPrototypePlayerSlotDescriptor& Slot : BootstrapSummary.PlayerSlots)
            {
                if (Slot.SlotName == MatchState.CurrentBatterSlotName)
                {
                    MatchState.LastOutcomeSummary = FString::Printf(
                        TEXT("Current matchup ready: %s %s batting against %s %s."),
                        *MatchState.CurrentOffenseSide,
                        *Slot.PlayerName,
                        *MatchState.CurrentDefenseSide,
                        *MatchState.CurrentPitcherSlotName);
                    break;
                }
            }
        }
    }
}
