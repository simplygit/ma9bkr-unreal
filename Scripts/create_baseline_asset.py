import unreal


ASSET_NAME = "DA_KRPrototypeBaseline"
PACKAGE_PATH = "/Game/Baseline"
ASSET_PATH = f"{PACKAGE_PATH}/{ASSET_NAME}"
ASSET_CLASS_PATH = "/Script/KRGameplay.KRPrototypeBaselineAsset"


def make_player_slot(
    slot_name,
    source_sheet,
    card_index,
    season_year,
    team_name,
    player_name,
    primary_position,
    batting_order,
    defensive_position,
    starting_lineup,
    defensive_starter,
    designated_hitter,
    overall,
    power,
    contact,
    run_speed,
    defense_speed,
    defense_range,
    throw_power,
    throw_skill,
    agility,
    stamina,
    control,
    ball_speed,
    pitch_arsenal_summary,
    notes,
):
    slot = unreal.KRPrototypePlayerSlotDescriptor()
    slot.set_editor_property("slot_name", slot_name)
    slot.set_editor_property("source_sheet", source_sheet)
    slot.set_editor_property("card_index", card_index)
    slot.set_editor_property("season_year", season_year)
    slot.set_editor_property("team_name", team_name)
    slot.set_editor_property("player_name", player_name)
    slot.set_editor_property("primary_position", primary_position)
    slot.set_editor_property("batting_order", batting_order)
    slot.set_editor_property("defensive_position", defensive_position)
    slot.set_editor_property("overall", overall)
    slot.set_editor_property("power", power)
    slot.set_editor_property("contact", contact)
    slot.set_editor_property("run_speed", run_speed)
    slot.set_editor_property("defense_speed", defense_speed)
    slot.set_editor_property("defense_range", defense_range)
    slot.set_editor_property("throw_power", throw_power)
    slot.set_editor_property("throw_skill", throw_skill)
    slot.set_editor_property("agility", agility)
    slot.set_editor_property("stamina", stamina)
    slot.set_editor_property("control", control)
    slot.set_editor_property("ball_speed", ball_speed)
    slot.set_editor_property("pitch_arsenal_summary", pitch_arsenal_summary)
    slot.set_editor_property("notes", notes)
    return slot


def make_replay_sample(sample_name, source_relative_path, source_sheet, key_column, key_value, linked_scene_title, notes):
    sample = unreal.KRPrototypeReplaySampleDescriptor()
    sample.set_editor_property("sample_name", sample_name)
    sample.set_editor_property("source_relative_path", source_relative_path)
    sample.set_editor_property("source_sheet", source_sheet)
    sample.set_editor_property("key_column", key_column)
    sample.set_editor_property("key_value", key_value)
    sample.set_editor_property("linked_scene_title", linked_scene_title)
    sample.set_editor_property("notes", notes)
    return sample


def make_replay_link(sample_name, condition_state_id, condition_state_title, scene_id, scene_title, shot_sequence, camera_sequence, notes):
    link = unreal.KRPrototypeReplayLinkDescriptor()
    link.set_editor_property("sample_name", sample_name)
    link.set_editor_property("condition_state_id", condition_state_id)
    link.set_editor_property("condition_state_title", condition_state_title)
    link.set_editor_property("scene_id", scene_id)
    link.set_editor_property("scene_title", scene_title)
    link.set_editor_property("shot_sequence", shot_sequence)
    link.set_editor_property("camera_sequence", camera_sequence)
    link.set_editor_property("notes", notes)
    return link


def main():
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    asset_library = unreal.EditorAssetLibrary
    baseline_asset_class = unreal.load_class(None, ASSET_CLASS_PATH)

    if not baseline_asset_class:
        raise RuntimeError(f"Failed to load asset class: {ASSET_CLASS_PATH}")

    if not asset_library.does_directory_exist(PACKAGE_PATH):
        asset_library.make_directory(PACKAGE_PATH)

    existing_asset = asset_library.load_asset(ASSET_PATH)
    if existing_asset:
        asset = existing_asset
    else:
        factory = unreal.DataAssetFactory()
        try:
            factory.set_editor_property("data_asset_class", baseline_asset_class)
        except Exception:
            try:
                factory.set_editor_property("DataAssetClass", baseline_asset_class)
            except Exception:
                pass

        asset = asset_tools.create_asset(
            asset_name=ASSET_NAME,
            package_path=PACKAGE_PATH,
            asset_class=baseline_asset_class,
            factory=factory,
        )

    if not asset:
        raise RuntimeError("Failed to create baseline asset.")

    stadium = unreal.KRPrototypeStadiumDescriptor()
    stadium.set_editor_property("logical_name", "JamsilPrimary")
    stadium.set_editor_property("unity_scene_path", "Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil.unity")
    stadium.set_editor_property("target_unreal_map_path", "/Game/Maps/Stadiums/L_Jamsil_Prototype")
    stadium.set_editor_property(
        "deferred_variants",
        [
            "Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil_Night.unity",
            "Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil_Toon.unity",
            "Assets/01_Scenes/Stadium/KBO/Stadium_Jamsil_Night_Toon.unity",
        ],
    )
    stadium.set_editor_property("notes", "Primary stadium baseline selected from Phase 1 document.")
    asset.set_editor_property("stadium", stadium)

    asset.set_editor_property(
        "player_slots",
        [
            make_player_slot("StarterPitcher", "PlayerPitcher", 107488, 2026, "LG", "임찬규", "SP", 0, "P", True, True, False, 82, 0, 0, 0, 0, 0, 0, 0, 0, 88, 84, 77, "4FB(81) / SlowCurve(81) / VSlider(84)", "Primary Jamsil baseline starter from LG 2026."),
            make_player_slot("Lineup01", "PlayerBatter", 209538, 2026, "LG", "홍창기", "RF", 1, "RF", True, True, False, 84, 81, 80, 88, 88, 89, 92, 91, 87, 0, 0, 0, "", "Lead-off baseline."),
            make_player_slot("Lineup02", "PlayerBatter", 209530, 2026, "LG", "박해민", "CF", 2, "CF", True, True, False, 88, 83, 87, 90, 91, 93, 95, 95, 90, 0, 0, 0, "", "Center-field coverage baseline."),
            make_player_slot("Lineup03", "PlayerBatter", 209533, 2026, "LG", "오스틴", "1B", 3, "1B", True, True, False, 94, 95, 92, 87, 87, 90, 88, 87, 86, 0, 0, 0, "", "Middle-order slugging anchor."),
            make_player_slot("Lineup04", "PlayerBatter", 209526, 2026, "LG", "문보경", "1B", 4, "DH", True, False, True, 87, 88, 88, 82, 80, 74, 75, 77, 67, 0, 0, 0, "", "Primary designated hitter baseline."),
            make_player_slot("Lineup05", "PlayerBatter", 209534, 2026, "LG", "오지환", "SS", 5, "SS", True, True, False, 89, 86, 89, 88, 88, 89, 88, 88, 87, 0, 0, 0, "", "Shortstop baseline."),
            make_player_slot("Lineup06", "PlayerBatter", 209529, 2026, "LG", "박동원", "C", 6, "C", True, True, False, 87, 86, 85, 80, 81, 89, 84, 84, 82, 0, 0, 0, "", "Primary catcher baseline."),
            make_player_slot("Lineup07", "PlayerBatter", 209527, 2026, "LG", "문성주", "LF", 7, "LF", True, True, False, 89, 83, 92, 86, 87, 89, 94, 93, 86, 0, 0, 0, "", "Left-field baseline."),
            make_player_slot("Lineup08", "PlayerBatter", 209532, 2026, "LG", "신민재", "2B", 8, "2B", True, True, False, 83, 80, 81, 83, 85, 92, 89, 89, 85, 0, 0, 0, "", "Second-base baseline."),
            make_player_slot("Lineup09", "PlayerBatter", 209537, 2026, "LG", "천성호", "3B", 9, "3B", True, True, False, 90, 86, 93, 86, 85, 85, 85, 82, 84, 0, 0, 0, "", "Third-base baseline."),
        ],
    )

    asset.set_editor_property(
        "replay_samples",
        [
            make_replay_sample("StrikeOutReplay", "Tables/09_인게임/마구B_리플레이.xlsx", "ReplayConditions", "StateID", "6", "삼진", "Use SCENE_RESULT_SO as the first pitch-to-result validation baseline."),
            make_replay_sample("SingleReplay", "Tables/09_인게임/마구B_리플레이.xlsx", "ReplayConditions", "StateID", "13", "1루타", "Use SCENE_RESULT_1B as the first ball-in-play advancement baseline."),
            make_replay_sample("FieldingOutReplay", "Tables/09_인게임/마구B_리플레이.xlsx", "ReplayConditions", "StateID", "5", "아웃", "Use SCENE_RESULT_OUT as the first fielding-resolution baseline."),
        ],
    )

    asset.set_editor_property(
        "replay_links",
        [
            make_replay_link("StrikeOutReplay", 6, "SCENE_RESULT_SO", 2, "삼진", [4, 61, 63], [1, 13, 16], "Strikeout scene link."),
            make_replay_link("SingleReplay", 13, "SCENE_RESULT_1B", 5, "1루타", [60, 48, 49, 50, 47], [2, 3, 4, 5, 0], "Single-hit scene link."),
            make_replay_link("FieldingOutReplay", 5, "SCENE_RESULT_OUT", 7, "아웃", [56, 57, 60, 58, 51], [10, 11, 2, 12, 0], "Field-out scene link."),
        ],
    )

    asset_library.save_loaded_asset(asset)
    unreal.EditorAssetLibrary.sync_browser_to_objects([ASSET_PATH])
    unreal.log(f"Baseline asset ready: {ASSET_PATH}")


if __name__ == "__main__":
    main()
