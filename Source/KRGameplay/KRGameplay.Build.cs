using UnrealBuildTool;

public class KRGameplay : ModuleRules
{
    public KRGameplay(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "KRCore",
            "KRLegacyBridge",
            "KRPresentation"
        });
    }
}
