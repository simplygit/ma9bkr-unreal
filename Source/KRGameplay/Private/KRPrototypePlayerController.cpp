#include "KRPrototypePlayerController.h"

#include "InputCoreTypes.h"

#include "GameFramework/HUD.h"

#include "KRPrototypeGameState.h"

void AKRPrototypePlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = false;

    if (AHUD* PrototypeHUD = GetHUD())
    {
        PrototypeHUD->bShowHUD = true;
    }
}

void AKRPrototypePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent == nullptr)
    {
        return;
    }

    InputComponent->BindKey(EKeys::N, IE_Pressed, this, &AKRPrototypePlayerController::TriggerNextSequenceStep);
    InputComponent->BindKey(EKeys::B, IE_Pressed, this, &AKRPrototypePlayerController::TriggerBall);
    InputComponent->BindKey(EKeys::S, IE_Pressed, this, &AKRPrototypePlayerController::TriggerStrike);
    InputComponent->BindKey(EKeys::O, IE_Pressed, this, &AKRPrototypePlayerController::TriggerOut);
}

void AKRPrototypePlayerController::TriggerNextSequenceStep()
{
    if (AKRPrototypeGameState* PrototypeGameState = GetPrototypeGameState())
    {
        PrototypeGameState->PlayNextPrototypeSequenceStep();
    }
}

void AKRPrototypePlayerController::TriggerBall()
{
    if (AKRPrototypeGameState* PrototypeGameState = GetPrototypeGameState())
    {
        PrototypeGameState->RecordBall();
    }
}

void AKRPrototypePlayerController::TriggerStrike()
{
    if (AKRPrototypeGameState* PrototypeGameState = GetPrototypeGameState())
    {
        PrototypeGameState->RecordStrike();
    }
}

void AKRPrototypePlayerController::TriggerOut()
{
    if (AKRPrototypeGameState* PrototypeGameState = GetPrototypeGameState())
    {
        PrototypeGameState->RecordOut();
    }
}

AKRPrototypeGameState* AKRPrototypePlayerController::GetPrototypeGameState() const
{
    return GetWorld() ? GetWorld()->GetGameState<AKRPrototypeGameState>() : nullptr;
}
