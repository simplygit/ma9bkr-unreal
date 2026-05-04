#pragma once

#include "Modules/ModuleManager.h"

class FKRCoreModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
