# Build Verification

## Purpose

- Make `Phase 2` build verification repeatable.
- Keep the editor-target workflow explicit so we do not lose time to locked DLL failures.

## Environment

- Engine root: `D:\EpicLibrary\UE_5.7\Engine`
- Project root: `F:\workspace_f\KR_unreal`
- Project file: `F:\workspace_f\KR_unreal\KRUnreal.uproject`
- Build helper: `F:\workspace_f\KR_unreal\Scripts\Invoke-KRBuild.ps1`

## Recommended Commands

### Game target

```powershell
& 'F:\workspace_f\KR_unreal\Scripts\Invoke-KRBuild.ps1' -Target KRUnreal
```

### Editor target

```powershell
& 'F:\workspace_f\KR_unreal\Scripts\Invoke-KRBuild.ps1' -Target KRUnrealEditor
```

## Important Rule

- `KRUnrealEditor` 빌드 전에는 `UnrealEditor.exe` 를 종료한다.
- 에디터가 열린 상태에서는 `UnrealEditor-KRCore.dll`, `UnrealEditor-KRLegacyBridge.dll`, `UnrealEditor-KRPresentation.dll`, `UnrealEditor-KRGameplay.dll` 링크가 파일 잠금으로 실패할 수 있다.

## Current Verification Status

- `KRUnreal` game target: verified success
- `KRUnrealEditor` editor target: workflow verified, but final success still depends on building with the editor process closed

## Phase 2 Exit Readiness

- `.uproject` exists
- module layout exists
- module responsibilities are documented
- build commands are scripted
- editor-target precondition is documented

남은 수동 확인:

- 에디터를 종료한 상태에서 `KRUnrealEditor` 빌드 1회 성공 확인
