#include "KRPrototypeGameMode.h"

#include "KRPrototypeGameState.h"

AKRPrototypeGameMode::AKRPrototypeGameMode()
{
    GameStateClass = AKRPrototypeGameState::StaticClass();
}
