# KR Unreal Workspace

## 목적

- 이 디렉토리는 Unity 프로젝트 `F:\workspace_f\KR_trunk`에서 순차 이관할 Unreal 작업 공간이다.
- 현재 단계는 `Phase 1 기준선 확정`과 `Phase 2 골격 준비`다.
- 아직 Unreal Editor가 로컬에서 확인되지 않아 `.uproject`는 생성되지 않았다.

## 현재 생성된 골격

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

## 현재 구현된 런타임 뼈대

- `KRCore`
  - `UKRMigrationDeveloperSettings`
- `KRLegacyBridge`
  - `UKRLegacyBridgeSubsystem`
  - `FKRLegacyTableDescriptor`
- `KRGameplay`
  - `UKRGameplayBootstrapSubsystem`
  - `UKRPrototypeBaselineAsset`
  - `AKRPrototypeGameState`
  - `FKRPrototypeMatchState`
  - `AKRPrototypeGameMode`
  - `UKRPrototypeGameInstance`

## 모듈 의도

- `KRCore`
  - 공통 설정, 로깅, 시간, 상태, 디버그 유틸
- `KRGameplay`
  - 경기 코어 로직
- `KRLegacyBridge`
  - 기존 Unity 백엔드/테이블/패킷 호환 계층
- `KRPresentation`
  - UMG, 카메라 연출, Blueprint 레벨 구성

## 현재 제약

- 확인된 Unreal Editor 경로:
  - `D:\EpicLibrary\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe`
- `KRUnreal` 게임 타깃 빌드는 성공했다.
- 프로젝트 파일과 솔루션은 생성되었지만, `KRUnrealEditor` 타깃 빌드는 로컬 메모리 압박으로 아직 완료 검증을 못 했다.
- UnrealBuildTool 로그에는 `UbaSessionServer`가 Shared PCH 컴파일을 메모리 부족으로 반복 중단한 기록이 남아 있다.

## 다음 단계

1. `KRUnrealEditor` 타깃 빌드 메모리 이슈 완화
2. 기준 선수 세트와 리플레이 샘플 확정
3. 최소 테스트 맵과 경기 진입용 bootstrap asset 생성
4. 경기 코어 상태 객체 초안 구현
