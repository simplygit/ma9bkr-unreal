#include "KRPrototypeGameState.h"

AKRPrototypeGameState::AKRPrototypeGameState()
{
    MatchState.Phase = EKRMatchPhase::Boot;
}

void AKRPrototypeGameState::StartPrototypeMatch()
{
    MatchState = FKRPrototypeMatchState();
    MatchState.Phase = EKRMatchPhase::Warmup;
}

void AKRPrototypeGameState::RecordOut()
{
    MatchState.Outs++;
    AdvanceHalfInningIfNeeded();
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

const FKRPrototypeMatchState& AKRPrototypeGameState::GetMatchState() const
{
    return MatchState;
}

void AKRPrototypeGameState::AdvanceHalfInningIfNeeded()
{
    if (MatchState.Outs < 3)
    {
        return;
    }

    MatchState.Outs = 0;
    MatchState.Balls = 0;
    MatchState.Strikes = 0;
    MatchState.Bases = FKRBaseOccupancy();
    MatchState.Phase = EKRMatchPhase::HalfInningEnd;

    if (MatchState.bTopOfInning)
    {
        MatchState.bTopOfInning = false;
    }
    else
    {
        MatchState.bTopOfInning = true;
        MatchState.Inning++;
    }
}
