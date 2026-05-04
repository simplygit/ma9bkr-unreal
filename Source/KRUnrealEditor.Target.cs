using UnrealBuildTool;
using System.Collections.Generic;

public class KRUnrealEditorTarget : TargetRules
{
    public KRUnrealEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V6;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        ExtraModuleNames.AddRange(new string[]
        {
            "KRGameplay"
        });
    }
}
