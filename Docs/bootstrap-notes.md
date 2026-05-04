# Unreal Bootstrap Notes

## 현재 상태

- `KRUnreal.uproject` 와 `KRUnreal.sln` 이 생성되었다.
- `KRCore`, `KRGameplay`, `KRLegacyBridge`, `KRPresentation` 모듈의 최소 C++ 엔트리가 생성되었다.
- `KRUnreal` 게임 타깃 빌드가 성공했다.
- 기준 계획 문서는 `F:\workspace_f\KR_trunk\docs\tasks\2026-04-29-unity-to-unreal-migration\implementation-plan.md` 를 따른다.

## 예정 구조

- Project root: `F:\workspace_f\KR_unreal`
- Planned modules:
  - `KRCore`
  - `KRGameplay`
  - `KRLegacyBridge`
  - `KRPresentation`

## 확인된 사항

- Unreal Engine 경로:
  - `D:\EpicLibrary\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe`
- 프로젝트명:
  - `KRUnreal`
- 대상 플랫폼 우선순위:
  - 모바일 기준

## 현재 이슈

- `KRUnrealEditor` 빌드 검증이 로컬 메모리 압박으로 중단되었다.
- UBT 로그에는 `UbaSessionServer`가 Shared PCH 컴파일을 반복적으로 종료한 기록이 있다.

## 생성 후 바로 해야 할 일

1. 빌드 메모리 문제를 피할 수 있는 로컬 빌드 설정 정리
2. 최소 startup map과 test map 분리
3. 경기 코어용 테스트 월드 구성
4. 기준선 문서와 연결되는 data bridge 초안 추가
