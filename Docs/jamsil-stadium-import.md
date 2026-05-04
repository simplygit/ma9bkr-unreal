# 잠실 구장 임포트

## 개요

- Unity 원본 씬: `F:\workspace_f\KR_trunk\Assets\01_Scenes\Stadium\KBO\Stadium_Jamsil.unity`
- Unity 원본 FBX 폴더: `F:\workspace_f\KR_trunk\Assets\03_Arts\FBX\Bg\Stadium_Jamsil`
- Unreal 메시 대상 경로: `/Game/Stadiums/Jamsil/Meshes`
- Unreal 테스트 맵: `/Game/Maps/Stadiums/L_Jamsil_Prototype`

## 임포트 대상 메시

- `Stadium_Jamsil_Infield.FBX`
- `Stadium_Jamsil_Outfield.FBX`
- `Stadium_Jamsil_00.fbx`
- `Stadium_Jamsil_01.fbx`
- `Stadium_Jamsil_0.FBX`
- `Stadium_Jamsil_net.fbx`
- `Stadium_Jamsil_Sky.fbx`
- `Stadium_Jamsil_ETC.fbx`
- `SamSungBridge.fbx`
- `Countlight.fbx`

## 실행 방법

- PowerShell 진입점: `F:\workspace_f\KR_unreal\Scripts\Import-JamsilStadium.ps1`
- Python 임포트 스크립트: `F:\workspace_f\KR_unreal\Scripts\import_jamsil_stadium.py`
- 프로젝트 파일: `F:\workspace_f\KR_unreal\KRUnreal.uproject`

실행:

```powershell
& 'F:\workspace_f\KR_unreal\Scripts\Import-JamsilStadium.ps1'
```

## 메모

- 현재 임포터는 머티리얼 복원보다 에디터 가시화와 배치 확인을 우선합니다.
- 정적 메시는 프로토타입 맵의 월드 원점 기준으로 배치해서 Unity FBX 피벗이 그대로 맞는지 먼저 확인할 수 있게 했습니다.
- 처음 시도했던 `UnrealEditor-Cmd.exe` + `-nullrhi` 경로는 이 환경에서 액터 배치가 불안정했습니다. 현재 정상 경로는 `UnrealEditor.exe` + `-ExecutePythonScript` 조합입니다.
- 자동화 실행 중 로컬 플러그인 로딩 오류를 피하기 위해 프로젝트 설정에서 `VisualStudioTools`는 명시적으로 비활성화했습니다.
