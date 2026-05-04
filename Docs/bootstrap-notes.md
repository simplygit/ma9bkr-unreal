# Unreal Bootstrap Notes

## Current Status

- `KRUnreal.uproject` and `KRUnreal.sln` exist.
- `KRCore`, `KRGameplay`, `KRLegacyBridge`, and `KRPresentation` module skeletons are in place.
- `KRUnreal` game target build is verified.
- Baseline bootstrap data now includes:
  - Jamsil stadium baseline
  - LG 2026 starter pitcher
  - batting order 9
  - defensive alignment + DH
  - replay linkage data
  - critical workbook export schemas

## Fixed Structure

- Project root: `F:\workspace_f\KR_unreal`
- Planned modules:
  - `KRCore`
  - `KRGameplay`
  - `KRLegacyBridge`
  - `KRPresentation`

## Verified Paths

- Unreal Engine:
  - `D:\EpicLibrary\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe`
- Build helper:
  - `F:\workspace_f\KR_unreal\Scripts\Invoke-KRBuild.ps1`
- Detailed build notes:
  - [build-verification.md](/F:/workspace_f/KR_unreal/Docs/build-verification.md)

## Current Issue

- `KRUnrealEditor` build is no longer blocked primarily by Shared PCH memory pressure.
- The more direct failure now is editor-open DLL locking during link:
  - `UnrealEditor-KRCore.dll`
  - `UnrealEditor-KRLegacyBridge.dll`
  - `UnrealEditor-KRPresentation.dll`
  - `UnrealEditor-KRGameplay.dll`

## Working Rule

- Build `KRUnrealEditor` only after closing the Unreal Editor process.
- Use the scripted build path instead of ad hoc command edits.

## Immediate Next Steps

1. Close the editor and verify one clean `KRUnrealEditor` build.
2. Decide whether to materialize a `UKRPrototypeBaselineAsset` instance in `Content/`.
3. Move into `Phase 3` gameplay slice work after `Phase 1` sign-off.
