#include "KRPrototypeGameInstance.h"

#include "KRGameplayBootstrapSubsystem.h"

void UKRPrototypeGameInstance::Init()
{
    Super::Init();

    GetSubsystem<UKRGameplayBootstrapSubsystem>();
}

void UKRPrototypeGameInstance::Shutdown()
{
    Super::Shutdown();
}
