#include "KRPrototypeGameMode.h"

#include "KRPrototypeDebugHUD.h"
#include "KRPrototypeGameState.h"
#include "KRPrototypePlayerController.h"
#include "Engine/Engine.h"

AKRPrototypeGameMode::AKRPrototypeGameMode()
{
    GameStateClass = AKRPrototypeGameState::StaticClass();
    HUDClass = AKRPrototypeDebugHUD::StaticClass();
    PlayerControllerClass = AKRPrototypePlayerController::StaticClass();
}

void AKRPrototypeGameMode::StartPlay()
{
    Super::StartPlay();

    if (GEngine != nullptr)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            8.0f,
            FColor::Green,
            TEXT("KR Prototype Debug Active - N: Next  B: Ball  S: Strike  O: Out"));
    }

    if (AKRPrototypeGameState* PrototypeGameState = GetGameState<AKRPrototypeGameState>())
    {
        PrototypeGameState->StartPrototypeMatch();
    }
}
