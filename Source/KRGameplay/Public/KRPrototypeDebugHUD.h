#pragma once

#include "GameFramework/HUD.h"

#include "KRPrototypeDebugHUD.generated.h"

UCLASS()
class KRGAMEPLAY_API AKRPrototypeDebugHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;
};
