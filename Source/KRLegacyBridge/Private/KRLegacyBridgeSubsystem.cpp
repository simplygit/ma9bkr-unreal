#include "KRLegacyBridgeSubsystem.h"

#include "KRMigrationDeveloperSettings.h"

void UKRLegacyBridgeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    BaselineTables.Reset();

    auto MakeSheetExport =
        [](const TCHAR* SheetName, std::initializer_list<const TCHAR*> ExportColumnNames, const TCHAR* Notes) -> FKRLegacySheetExportDescriptor
    {
        FKRLegacySheetExportDescriptor Descriptor;
        Descriptor.SheetName = SheetName;
        Descriptor.Notes = Notes;

        for (const TCHAR* ColumnName : ExportColumnNames)
        {
            Descriptor.ExportColumnNames.Add(ColumnName);
        }

        return Descriptor;
    };

    auto MakeTableDescriptor =
        [](
            const TCHAR* LogicalName,
            const TCHAR* SourceRelativePath,
            const TCHAR* Notes,
            EKRLegacyTablePriority Priority,
            std::initializer_list<const TCHAR*> ExpectedSheetNames,
            std::initializer_list<FKRLegacySheetExportDescriptor> ExportSchemas) -> FKRLegacyTableDescriptor
    {
        FKRLegacyTableDescriptor Descriptor;
        Descriptor.LogicalName = LogicalName;
        Descriptor.SourceRelativePath = SourceRelativePath;
        Descriptor.Notes = Notes;
        Descriptor.Priority = Priority;

        for (const TCHAR* SheetName : ExpectedSheetNames)
        {
            Descriptor.ExpectedSheetNames.Add(SheetName);
        }

        for (const FKRLegacySheetExportDescriptor& ExportSchema : ExportSchemas)
        {
            Descriptor.ExportSchemas.Add(ExportSchema);
        }

        return Descriptor;
    };

    BaselineTables.Append({
        MakeTableDescriptor(
            TEXT("AI"),
            TEXT("Tables/09_인게임/마구B_AI테이블.xlsx"),
            TEXT("AI tuning and decision support baseline."),
            EKRLegacyTablePriority::Critical,
            { TEXT("NewbieAIBalance"), TEXT("AIBalance"), TEXT("AIContentsLv") },
            {
                MakeSheetExport(TEXT("NewbieAIBalance"), { TEXT("user_level"), TEXT("pitch_slot"), TEXT("hit_prob"), TEXT("homerun_prob"), TEXT("home_prob") }, TEXT("Entry-level AI onboarding curve.")),
                MakeSheetExport(TEXT("AIBalance"), { TEXT("channelIndex"), TEXT("batting"), TEXT("fooled"), TEXT("pitching"), TEXT("running"), TEXT("stealBase"), TEXT("fielding"), TEXT("fieldingDelay"), TEXT("fielderSpeed"), TEXT("pitchingGauge"), TEXT("batSigma"), TEXT("correctSwing"), TEXT("nonCorrectSwing") }, TEXT("Primary CPU batting, fielding, and pitching difficulty controls.")),
                MakeSheetExport(TEXT("AIContentsLv"), { TEXT("gameMode"), TEXT("Applylevel") }, TEXT("Maps game modes to AI difficulty application levels."))
            }),
        MakeTableDescriptor(
            TEXT("Replay"),
            TEXT("Tables/09_인게임/마구B_리플레이.xlsx"),
            TEXT("Replay and comparison baseline."),
            EKRLegacyTablePriority::Critical,
            { TEXT("ReplayCameras"), TEXT("ReplayConditions"), TEXT("ReplayShots"), TEXT("ReplayScenes") },
            {
                MakeSheetExport(TEXT("ReplayConditions"), { TEXT("StateID"), TEXT("StateTitle"), TEXT("Scenlist") }, TEXT("Result state to replay scene mapping.")),
                MakeSheetExport(TEXT("ReplayScenes"), { TEXT("SceneID"), TEXT("SceneTitle"), TEXT("ShotID") }, TEXT("Scene grouping and shot sequence.")),
                MakeSheetExport(TEXT("ReplayShots"), { TEXT("ShotID"), TEXT("ShotTitle"), TEXT("CameraID"), TEXT("StartPoint"), TEXT("Offset_start"), TEXT("EndPoint"), TEXT("Offset_end"), TEXT("Etc") }, TEXT("Shot timeline and playfield usage flags.")),
                MakeSheetExport(TEXT("ReplayCameras"), { TEXT("ID"), TEXT("Title"), TEXT("Period"), TEXT("Duration"), TEXT("ActionID"), TEXT("CamName"), TEXT("ViewType"), TEXT("CamPosX"), TEXT("CamPosY"), TEXT("CamPosZ"), TEXT("ViewPosX"), TEXT("ViewPosY"), TEXT("ViewPosZ"), TEXT("ProjDegree"), TEXT("ProjRatio"), TEXT("ProjNear"), TEXT("ProjFar"), TEXT("CamDist") }, TEXT("Camera definitions referenced by replay shots."))
            }),
        MakeTableDescriptor(
            TEXT("Camera"),
            TEXT("Tables/09_인게임/마구B_인게임카메라.xlsx"),
            TEXT("Camera parameter baseline."),
            EKRLegacyTablePriority::Critical,
            { TEXT("CameraData"), TEXT("CameraPreset"), TEXT("CameraConversion") },
            {
                MakeSheetExport(TEXT("CameraData"), { TEXT("Name"), TEXT("Index"), TEXT("EyeX"), TEXT("EyeY"), TEXT("EyeZ"), TEXT("AtX"), TEXT("AtY"), TEXT("AtZ"), TEXT("Fov"), TEXT("Aspect"), TEXT("Near"), TEXT("Far"), TEXT("ApplyTime"), TEXT("RotX"), TEXT("RotY"), TEXT("RotZ") }, TEXT("Sequence camera transform and lens data.")),
                MakeSheetExport(TEXT("CameraPreset"), { TEXT("index"), TEXT("position_x"), TEXT("position_y"), TEXT("position_z"), TEXT("rotation_x"), TEXT("rotation_y"), TEXT("rotation_z"), TEXT("fov_value"), TEXT("near_clip_plane"), TEXT("far_clip_plane"), TEXT("Dutch") }, TEXT("Static preset camera transforms.")),
                MakeSheetExport(TEXT("CameraConversion"), { TEXT("stadium_index"), TEXT("home_town"), TEXT("stadium_desc"), TEXT("batting_distance") }, TEXT("Stadium-specific camera conversion and batting distance thresholds."))
            }),
        MakeTableDescriptor(
            TEXT("BallInPlay"),
            TEXT("Tables/09_인게임/마구B_인게임타구.xlsx"),
            TEXT("Ball-in-play parameter baseline."),
            EKRLegacyTablePriority::Critical,
            { TEXT("HitPreset"), TEXT("AiHitPreset"), TEXT("BaseHitPreset"), TEXT("ErrorBall"), TEXT("BuntPreset") },
            {
                MakeSheetExport(TEXT("HitPreset"), { TEXT("*preset_index"), TEXT("battingAccuracy"), TEXT("hitzonetype"), TEXT("hitballtype"), TEXT("hittype"), TEXT("condition_min"), TEXT("condition_max"), TEXT("V_angle_min"), TEXT("V_angle_max"), TEXT("H_angle_min"), TEXT("H_angle_max"), TEXT("BallSpeed_min"), TEXT("BallSpeed_max"), TEXT("Runner_1B"), TEXT("Runner_2B"), TEXT("Runner_3B") }, TEXT("Primary user hit result preset ranges.")),
                MakeSheetExport(TEXT("AiHitPreset"), { TEXT("*preset_index"), TEXT("battingAccuracy"), TEXT("hitzonetype"), TEXT("hitballtype"), TEXT("hittype"), TEXT("condition_min"), TEXT("condition_max"), TEXT("V_angle_min"), TEXT("V_angle_max"), TEXT("H_angle_min"), TEXT("H_angle_max"), TEXT("BallSpeed_min"), TEXT("BallSpeed_max") }, TEXT("CPU batting result preset ranges.")),
                MakeSheetExport(TEXT("BaseHitPreset"), { TEXT("index"), TEXT("condition_min"), TEXT("condition_max"), TEXT("result_vmin"), TEXT("result_vmax"), TEXT("result_hmin"), TEXT("result_hmax"), TEXT("result_smin"), TEXT("result_smax"), TEXT("defense_shift"), TEXT("base_hit") }, TEXT("Base-hit outcome shaping.")),
                MakeSheetExport(TEXT("ErrorBall"), { TEXT("index"), TEXT("BallType"), TEXT("ErrorType"), TEXT("speedRate"), TEXT("vAngle"), TEXT("vAngleInvert"), TEXT("hAngle") }, TEXT("Fielding error ball variants.")),
                MakeSheetExport(TEXT("BuntPreset"), { TEXT("*preset_index"), TEXT("V_angle_min"), TEXT("V_angle_max"), TEXT("H_angle_min"), TEXT("H_angle_max"), TEXT("BallSpeed_min"), TEXT("BallSpeed_max") }, TEXT("Bunt-specific exit profile ranges."))
            }),
        MakeTableDescriptor(
            TEXT("Animation"),
            TEXT("Tables/09_인게임/마구B_인게임애니메이션세팅.xlsx"),
            TEXT("Animation tuning reference."),
            EKRLegacyTablePriority::Recommended,
            { TEXT("Animation") },
            {}),
        MakeTableDescriptor(
            TEXT("Sound"),
            TEXT("Tables/09_인게임/마구B_인게임사운드.xlsx"),
            TEXT("In-game sound event baseline."),
            EKRLegacyTablePriority::Deferred,
            { TEXT("Sound") },
            {}),
        MakeTableDescriptor(
            TEXT("Intervention"),
            TEXT("Tables/09_인게임/마구24_개입조작.xlsx"),
            TEXT("Intervention input and control tuning."),
            EKRLegacyTablePriority::Recommended,
            { TEXT("Intervention") },
            {})
    });
}

void UKRLegacyBridgeSubsystem::Deinitialize()
{
    BaselineTables.Reset();

    Super::Deinitialize();
}

const TArray<FKRLegacyTableDescriptor>& UKRLegacyBridgeSubsystem::GetBaselineTables() const
{
    return BaselineTables;
}

FString UKRLegacyBridgeSubsystem::GetUnityProjectRoot() const
{
    return GetDefault<UKRMigrationDeveloperSettings>()->UnityProjectRoot;
}

FString UKRLegacyBridgeSubsystem::GetBaselineDocumentPath() const
{
    return GetDefault<UKRMigrationDeveloperSettings>()->BaselineDocumentPath;
}
