#include "KRGameplayBootstrapSubsystem.h"

#include "KRLegacyBridgeSubsystem.h"

void UKRGameplayBootstrapSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    const UKRLegacyBridgeSubsystem* LegacyBridge = GetGameInstance()->GetSubsystem<UKRLegacyBridgeSubsystem>();
    bLegacyBridgeAvailable = LegacyBridge != nullptr;

    BootstrapSummary = FKRPrototypeBootstrapSummary();
    BootstrapSummary.Stadium.LogicalName = TEXT("JamsilPrimary");
    BootstrapSummary.Stadium.UnityScenePath = TEXT("Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil.unity");
    BootstrapSummary.Stadium.TargetUnrealMapPath = TEXT("/Game/Maps/Stadiums/L_Jamsil_Prototype");
    BootstrapSummary.Stadium.DeferredVariants = {
        TEXT("Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil_Night.unity"),
        TEXT("Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil_Toon.unity"),
        TEXT("Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil_Night_Toon.unity")
    };
    BootstrapSummary.Stadium.Notes = TEXT("Primary stadium baseline selected from Phase 1 document.");

    auto MakePitcherSlot =
        [](
            const TCHAR* SlotName,
            EKRPrototypeHandedness Handedness,
            int32 CardIndex,
            const TCHAR* PlayerName,
            const TCHAR* PrimaryPosition,
            const TCHAR* DefensivePosition,
            int32 Overall,
            int32 Stamina,
            int32 Control,
            int32 BallSpeed,
            const TCHAR* PitchArsenalSummary,
            const TCHAR* Notes) -> FKRPrototypePlayerSlotDescriptor
    {
        FKRPrototypePlayerSlotDescriptor Slot;
        Slot.SlotName = SlotName;
        Slot.Role = EKRPrototypeRosterRole::Pitcher;
        Slot.Handedness = Handedness;
        Slot.SourceSheet = TEXT("PlayerPitcher");
        Slot.CardIndex = CardIndex;
        Slot.SeasonYear = 2026;
        Slot.TeamName = TEXT("LG");
        Slot.PlayerName = PlayerName;
        Slot.PrimaryPosition = PrimaryPosition;
        Slot.BattingOrder = 0;
        Slot.DefensivePosition = DefensivePosition;
        Slot.bStartingLineup = true;
        Slot.bDefensiveStarter = true;
        Slot.bDesignatedHitter = false;
        Slot.Overall = Overall;
        Slot.Stamina = Stamina;
        Slot.Control = Control;
        Slot.BallSpeed = BallSpeed;
        Slot.PitchArsenalSummary = PitchArsenalSummary;
        Slot.Notes = Notes;
        return Slot;
    };

    auto MakeBatterSlot =
        [](
            const TCHAR* SlotName,
            EKRPrototypeHandedness Handedness,
            int32 CardIndex,
            const TCHAR* PlayerName,
            const TCHAR* PrimaryPosition,
            int32 BattingOrder,
            const TCHAR* DefensivePosition,
            bool bDesignatedHitter,
            int32 Overall,
            int32 Power,
            int32 Contact,
            int32 RunSpeed,
            int32 DefenseSpeed,
            int32 DefenseRange,
            int32 ThrowPower,
            int32 ThrowSkill,
            int32 Agility,
            const TCHAR* Notes) -> FKRPrototypePlayerSlotDescriptor
    {
        FKRPrototypePlayerSlotDescriptor Slot;
        Slot.SlotName = SlotName;
        Slot.Role = bDesignatedHitter ? EKRPrototypeRosterRole::Utility : EKRPrototypeRosterRole::Batter;
        Slot.Handedness = Handedness;
        Slot.SourceSheet = TEXT("PlayerBatter");
        Slot.CardIndex = CardIndex;
        Slot.SeasonYear = 2026;
        Slot.TeamName = TEXT("LG");
        Slot.PlayerName = PlayerName;
        Slot.PrimaryPosition = PrimaryPosition;
        Slot.BattingOrder = BattingOrder;
        Slot.DefensivePosition = DefensivePosition;
        Slot.bStartingLineup = true;
        Slot.bDefensiveStarter = !bDesignatedHitter;
        Slot.bDesignatedHitter = bDesignatedHitter;
        Slot.Overall = Overall;
        Slot.Power = Power;
        Slot.Contact = Contact;
        Slot.RunSpeed = RunSpeed;
        Slot.DefenseSpeed = DefenseSpeed;
        Slot.DefenseRange = DefenseRange;
        Slot.ThrowPower = ThrowPower;
        Slot.ThrowSkill = ThrowSkill;
        Slot.Agility = Agility;
        Slot.Notes = Notes;
        return Slot;
    };

    auto MakeReplayLink =
        [](
            const TCHAR* SampleName,
            int32 ConditionStateId,
            const TCHAR* ConditionStateTitle,
            int32 SceneId,
            const TCHAR* SceneTitle,
            std::initializer_list<int32> ShotSequence,
            std::initializer_list<int32> CameraSequence,
            const TCHAR* Notes) -> FKRPrototypeReplayLinkDescriptor
    {
        FKRPrototypeReplayLinkDescriptor Link;
        Link.SampleName = SampleName;
        Link.ConditionStateId = ConditionStateId;
        Link.ConditionStateTitle = ConditionStateTitle;
        Link.SceneId = SceneId;
        Link.SceneTitle = SceneTitle;
        Link.Notes = Notes;

        for (const int32 ShotId : ShotSequence)
        {
            Link.ShotSequence.Add(ShotId);
        }

        for (const int32 CameraId : CameraSequence)
        {
            Link.CameraSequence.Add(CameraId);
        }

        return Link;
    };

    BootstrapSummary.PlayerSlots = {
        MakePitcherSlot(
            TEXT("StarterPitcher"),
            EKRPrototypeHandedness::Right,
            107488,
            TEXT("임찬규"),
            TEXT("SP"),
            TEXT("P"),
            82,
            88,
            84,
            77,
            TEXT("4FB(81) / SlowCurve(81) / VSlider(84)"),
            TEXT("Primary Jamsil baseline starter from LG 2026. DH ruleset keeps him out of the batting order.")),
        MakeBatterSlot(
            TEXT("Lineup01"),
            EKRPrototypeHandedness::Left,
            209538,
            TEXT("홍창기"),
            TEXT("RF"),
            1,
            TEXT("RF"),
            false,
            84,
            81,
            80,
            88,
            88,
            89,
            92,
            91,
            87,
            TEXT("Lead-off baseline for first-pitch timing and right-field route validation.")),
        MakeBatterSlot(
            TEXT("Lineup02"),
            EKRPrototypeHandedness::Left,
            209530,
            TEXT("박해민"),
            TEXT("CF"),
            2,
            TEXT("CF"),
            false,
            88,
            83,
            87,
            90,
            91,
            93,
            95,
            95,
            90,
            TEXT("Center-field coverage baseline with high route, catch, and relay values.")),
        MakeBatterSlot(
            TEXT("Lineup03"),
            EKRPrototypeHandedness::Right,
            209533,
            TEXT("오스틴"),
            TEXT("1B"),
            3,
            TEXT("1B"),
            false,
            94,
            95,
            92,
            87,
            87,
            90,
            88,
            87,
            86,
            TEXT("Middle-order contact and slugging anchor for runner-on-base validation.")),
        MakeBatterSlot(
            TEXT("Lineup04"),
            EKRPrototypeHandedness::Left,
            209526,
            TEXT("문보경"),
            TEXT("1B"),
            4,
            TEXT("DH"),
            true,
            87,
            88,
            88,
            82,
            80,
            74,
            75,
            77,
            67,
            TEXT("Primary designated hitter baseline. Keeps the fielding alignment stable while preserving a power bat.")),
        MakeBatterSlot(
            TEXT("Lineup05"),
            EKRPrototypeHandedness::Left,
            209534,
            TEXT("오지환"),
            TEXT("SS"),
            5,
            TEXT("SS"),
            false,
            89,
            86,
            89,
            88,
            88,
            89,
            88,
            88,
            87,
            TEXT("Shortstop baseline for infield funnel, pivot, and relay behavior.")),
        MakeBatterSlot(
            TEXT("Lineup06"),
            EKRPrototypeHandedness::Right,
            209529,
            TEXT("박동원"),
            TEXT("C"),
            6,
            TEXT("C"),
            false,
            87,
            86,
            85,
            80,
            81,
            89,
            84,
            84,
            82,
            TEXT("Primary catcher baseline for receiving, tag, and infield throw termination checks.")),
        MakeBatterSlot(
            TEXT("Lineup07"),
            EKRPrototypeHandedness::Left,
            209527,
            TEXT("문성주"),
            TEXT("LF"),
            7,
            TEXT("LF"),
            false,
            89,
            83,
            92,
            86,
            87,
            89,
            94,
            93,
            86,
            TEXT("Left-field baseline with stronger throw values for wall and relay path checks.")),
        MakeBatterSlot(
            TEXT("Lineup08"),
            EKRPrototypeHandedness::Left,
            209532,
            TEXT("신민재"),
            TEXT("2B"),
            8,
            TEXT("2B"),
            false,
            83,
            80,
            81,
            83,
            85,
            92,
            89,
            89,
            85,
            TEXT("Second-base baseline for double-play turns and middle-infield chase coverage.")),
        MakeBatterSlot(
            TEXT("Lineup09"),
            EKRPrototypeHandedness::Left,
            209537,
            TEXT("천성호"),
            TEXT("3B"),
            9,
            TEXT("3B"),
            false,
            90,
            86,
            93,
            86,
            85,
            85,
            85,
            82,
            84,
            TEXT("Third-base baseline for hot-corner reaction and left-side infield completion.")),
    };

    BootstrapSummary.ReplaySamples = {
        {
            TEXT("StrikeOutReplay"),
            TEXT("Tables/09_인게임/마구B_리플레이.xlsx"),
            TEXT("ReplayConditions"),
            TEXT("StateID"),
            TEXT("6"),
            TEXT("삼진"),
            TEXT("Use SCENE_RESULT_SO as the first pitch-to-result validation baseline.")
        },
        {
            TEXT("SingleReplay"),
            TEXT("Tables/09_인게임/마구B_리플레이.xlsx"),
            TEXT("ReplayConditions"),
            TEXT("StateID"),
            TEXT("13"),
            TEXT("1루타"),
            TEXT("Use SCENE_RESULT_1B as the first ball-in-play advancement baseline.")
        },
        {
            TEXT("FieldingOutReplay"),
            TEXT("Tables/09_인게임/마구B_리플레이.xlsx"),
            TEXT("ReplayConditions"),
            TEXT("StateID"),
            TEXT("5"),
            TEXT("아웃"),
            TEXT("Use SCENE_RESULT_OUT as the first fielding-resolution baseline.")
        }
    };

    BootstrapSummary.ReplayLinks = {
        MakeReplayLink(
            TEXT("StrikeOutReplay"),
            6,
            TEXT("SCENE_RESULT_SO"),
            2,
            TEXT("삼진"),
            { 4, 61, 63 },
            { 1, 13, 16 },
            TEXT("Strikeout scene resolves through one mound view, one side camera, and one pitch-finishing shot.")),
        MakeReplayLink(
            TEXT("SingleReplay"),
            13,
            TEXT("SCENE_RESULT_1B"),
            5,
            TEXT("1루타"),
            { 60, 48, 49, 50, 47 },
            { 2, 3, 4, 5, 0 },
            TEXT("Single-hit baseline fans through one broadcast camera and four field follow-up shots.")),
        MakeReplayLink(
            TEXT("FieldingOutReplay"),
            5,
            TEXT("SCENE_RESULT_OUT"),
            7,
            TEXT("아웃"),
            { 56, 57, 60, 58, 51 },
            { 10, 11, 2, 12, 0 },
            TEXT("Generic out baseline mixes field cameras and a shared broadcast follow camera before resolution."))
    };

    if (LegacyBridge != nullptr)
    {
        BootstrapSummary.BaselineTables = LegacyBridge->GetBaselineTables();
    }
}

void UKRGameplayBootstrapSubsystem::Deinitialize()
{
    bLegacyBridgeAvailable = false;
    BootstrapSummary = FKRPrototypeBootstrapSummary();

    Super::Deinitialize();
}

bool UKRGameplayBootstrapSubsystem::HasLegacyBridge() const
{
    return bLegacyBridgeAvailable;
}

FString UKRGameplayBootstrapSubsystem::DescribeBootstrapStatus() const
{
    return bLegacyBridgeAvailable
        ? TEXT("Legacy bridge ready for baseline table and document access.")
        : TEXT("Legacy bridge subsystem is not available.");
}

const FKRPrototypeBootstrapSummary& UKRGameplayBootstrapSubsystem::GetBootstrapSummary() const
{
    return BootstrapSummary;
}
