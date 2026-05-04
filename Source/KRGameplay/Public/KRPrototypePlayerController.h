#pragma once

#include "GameFramework/PlayerController.h"

#include "KRPrototypePlayerController.generated.h"

class AKRPrototypeGameState;

UCLASS()
class KRGAMEPLAY_API AKRPrototypePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    void TriggerNextSequenceStep();
    void TriggerBall();
    void TriggerStrike();
    void TriggerOut();

    AKRPrototypeGameState* GetPrototypeGameState() const;
};
