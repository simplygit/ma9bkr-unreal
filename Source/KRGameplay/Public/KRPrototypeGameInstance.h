#pragma once

#include "Engine/GameInstance.h"
#include "KRPrototypeGameInstance.generated.h"

UCLASS()
class KRGAMEPLAY_API UKRPrototypeGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;
    virtual void Shutdown() override;
};
