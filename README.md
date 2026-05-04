# KR Unreal Workspace

## Purpose

- This directory is the Unreal migration workspace paired with the Unity project at `F:\workspace_f\KR_trunk`.
- Current focus: close `Phase 1` cleanly and stabilize the `Phase 2` project/build workflow.

## Current Structure

- `KRUnreal.uproject`
- `KRUnreal.sln`
- `Config/`
- `Content/`
- `Plugins/`
- `Source/KRCore/`
- `Source/KRGameplay/`
- `Source/KRLegacyBridge/`
- `Source/KRPresentation/`
- `Docs/`
- `Scripts/`

## Implemented Foundations

- `KRCore`
  - `UKRMigrationDeveloperSettings`
- `KRLegacyBridge`
  - `UKRLegacyBridgeSubsystem`
  - `FKRLegacyTableDescriptor`
  - `FKRLegacySheetExportDescriptor`
- `KRGameplay`
  - `UKRGameplayBootstrapSubsystem`
  - `UKRPrototypeBaselineAsset`
  - `FKRPrototypeReplayLinkDescriptor`
  - `AKRPrototypeGameState`
  - `FKRPrototypeMatchState`
  - `AKRPrototypeGameMode`
  - `UKRPrototypeGameInstance`

## Module Responsibilities

- `KRCore`
  - Shared settings, logging, state, time, and low-level utilities
- `KRGameplay`
  - Match bootstrap, gameplay state, and core baseball flow
- `KRLegacyBridge`
  - Legacy Unity-side data, table, and backend compatibility bridge
- `KRPresentation`
  - UMG, camera presentation, and Blueprint-facing scene composition

## Build Workflow

- Engine path:
  - `D:\EpicLibrary\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe`
- Build helper:
  - `F:\workspace_f\KR_unreal\Scripts\Invoke-KRBuild.ps1`
- Build notes:
  - [build-verification.md](/F:/workspace_f/KR_unreal/Docs/build-verification.md)

Examples:

```powershell
& 'F:\workspace_f\KR_unreal\Scripts\Invoke-KRBuild.ps1' -Target KRUnreal
& 'F:\workspace_f\KR_unreal\Scripts\Invoke-KRBuild.ps1' -Target KRUnrealEditor
```

## Current Constraints

- `KRUnreal` game target build is verified.
- `KRUnrealEditor` build must be run with the editor process closed.
- When the editor is open, module DLL linking can fail because `UnrealEditor-*.dll` files are locked.

## Next Work

1. Re-run `KRUnrealEditor` build once the editor is closed and record the result.
2. Decide whether to materialize a real baseline `.uasset` for the current bootstrap data.
3. Start `Phase 3` gameplay slice work after `Phase 1` closeout is signed off.
