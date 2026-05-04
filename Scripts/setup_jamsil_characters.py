import os

import unreal


UNITY_ROOT = r"F:\workspace_f\KR_trunk"
PROJECT_ROOT = r"F:\workspace_f\KR_unreal"

CHARACTER_DESTINATION = "/Game/Characters/Prototype"
MAP_PATH = "/Game/Maps/Stadiums/L_Jamsil_Prototype"
BALL_MESH_PATH = "/Engine/BasicShapes/Sphere.Sphere"
BALL_MATERIAL_PATH = "/Game/Stadiums/Jamsil/Materials/M_Jamsil_Chalk.M_Jamsil_Chalk"
CHARACTER_MATERIAL_PATHS = {
    "Pitcher": "/Game/Characters/Prototype/Materials/M_Prototype_Pitcher.M_Prototype_Pitcher",
    "Batter": "/Game/Characters/Prototype/Materials/M_Prototype_Batter.M_Prototype_Batter",
    "Catcher": "/Game/Characters/Prototype/Materials/M_Prototype_Catcher.M_Prototype_Catcher",
    "Fielder": "/Game/Characters/Prototype/Materials/M_Prototype_Fielder.M_Prototype_Fielder",
    "Umpire": "/Game/Characters/Prototype/Materials/M_Prototype_Umpire.M_Prototype_Umpire",
}

ROLE_MESH_SOURCES = {
    "Pitcher": os.path.join(UNITY_ROOT, "Assets", "03_Arts", "Character", "FBX", "Magudoli_Base_001.FBX"),
    "Batter": os.path.join(UNITY_ROOT, "Assets", "03_Arts", "Character", "FBX", "Magudoli_Base_001.FBX"),
    "Catcher": os.path.join(UNITY_ROOT, "Assets", "03_Arts", "Character", "FBX", "Magudoli_Base_001.FBX"),
    "Fielder": os.path.join(UNITY_ROOT, "Assets", "03_Arts", "Character", "FBX", "Magudoli_Base_001.FBX"),
    "Umpire": os.path.join(UNITY_ROOT, "Assets", "03_Arts", "Character", "FBX", "Magudoli_Base_001.FBX"),
}

ROLE_ASSET_NAMES = {
    "Pitcher": "PitcherCharacter",
    "Batter": "BatterCharacter",
    "Catcher": "CatcherCharacter",
    "Fielder": "FielderCharacter",
    "Umpire": "UmpireCharacter",
}

CHARACTER_PREFIX = "KR_Prototype_Character_"
LABEL_PREFIX = "KR_Prototype_Label_"
BALL_PREFIX = "KR_Prototype_Ball"

HOME_COLOR = unreal.LinearColor(0.15, 0.45, 1.0, 1.0)
AWAY_COLOR = unreal.LinearColor(1.0, 0.2, 0.2, 1.0)

LINEUP_LAYOUT = [
    {"name": "Pitcher", "role": "Pitcher", "location": unreal.Vector(1844.0, 0.0, 0.0), "yaw": 0.0, "team": "Home"},
    {"name": "Catcher", "role": "Catcher", "location": unreal.Vector(-220.0, 0.0, 0.0), "yaw": 0.0, "team": "Home"},
    {"name": "Umpire", "role": "Umpire", "location": unreal.Vector(-540.0, 0.0, 0.0), "yaw": 0.0, "team": "Home"},
    {"name": "Batter", "role": "Batter", "location": unreal.Vector(-40.0, -95.0, 0.0), "yaw": 0.0, "team": "Away"},
    {"name": "FirstBase", "role": "Fielder", "location": unreal.Vector(2743.0, 2743.0, 0.0), "yaw": 0.0, "team": "Home"},
    {"name": "SecondBase", "role": "Fielder", "location": unreal.Vector(5486.0, 0.0, 0.0), "yaw": 0.0, "team": "Home"},
    {"name": "ThirdBase", "role": "Fielder", "location": unreal.Vector(2743.0, -2743.0, 0.0), "yaw": 0.0, "team": "Home"},
    {"name": "ShortStop", "role": "Fielder", "location": unreal.Vector(4300.0, -1200.0, 0.0), "yaw": 0.0, "team": "Home"},
    {"name": "LeftField", "role": "Fielder", "location": unreal.Vector(9300.0, -7200.0, 0.0), "yaw": 0.0, "team": "Home"},
    {"name": "CenterField", "role": "Fielder", "location": unreal.Vector(11800.0, 0.0, 0.0), "yaw": 0.0, "team": "Home"},
    {"name": "RightField", "role": "Fielder", "location": unreal.Vector(9300.0, 7200.0, 0.0), "yaw": 0.0, "team": "Home"},
]

BALL_LAYOUT = {
    "name": "Ball",
    "location": unreal.Vector(1680.0, 120.0, 135.0),
    "scale": unreal.Vector(0.2, 0.2, 0.2),
}


def ensure_directory(path):
    if not unreal.EditorAssetLibrary.does_directory_exist(path):
        unreal.EditorAssetLibrary.make_directory(path)


def import_character_mesh(role_name):
    source_path = ROLE_MESH_SOURCES[role_name]
    asset_name = ROLE_ASSET_NAMES[role_name]
    asset_path = f"{CHARACTER_DESTINATION}/{asset_name}.{asset_name}"

    if unreal.EditorAssetLibrary.does_asset_exist(asset_path):
        return asset_path

    if not os.path.exists(source_path):
        raise RuntimeError(f"Missing source character FBX: {source_path}")

    ensure_directory("/Game/Characters")
    ensure_directory(CHARACTER_DESTINATION)

    task = unreal.AssetImportTask()
    task.set_editor_property("filename", source_path)
    task.set_editor_property("destination_path", CHARACTER_DESTINATION)
    task.set_editor_property("destination_name", asset_name)
    task.set_editor_property("automated", True)
    task.set_editor_property("replace_existing", True)
    task.set_editor_property("replace_existing_settings", True)
    task.set_editor_property("save", True)

    options = unreal.FbxImportUI()
    options.set_editor_property("import_mesh", True)
    options.set_editor_property("import_as_skeletal", True)
    options.set_editor_property("import_materials", False)
    options.set_editor_property("import_textures", False)
    options.set_editor_property("import_animations", False)
    options.set_editor_property("mesh_type_to_import", unreal.FBXImportType.FBXIT_SKELETAL_MESH)

    skeletal_data = options.get_editor_property("skeletal_mesh_import_data")
    skeletal_data.set_editor_property("convert_scene", True)
    skeletal_data.set_editor_property("convert_scene_unit", True)
    skeletal_data.set_editor_property("import_morph_targets", False)
    skeletal_data.set_editor_property("preserve_smoothing_groups", True)

    task.set_editor_property("options", options)
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])

    for imported_path in task.get_editor_property("imported_object_paths"):
        asset = unreal.EditorAssetLibrary.load_asset(imported_path)
        if asset and asset.get_class().get_name() == "SkeletalMesh":
            unreal.log(f"Using imported skeletal mesh for {role_name}: {imported_path}")
            return imported_path

    if unreal.EditorAssetLibrary.does_asset_exist(asset_path):
        return asset_path

    raise RuntimeError(f"Failed to resolve imported prototype character skeletal mesh for role: {role_name}")


def destroy_previous_actors():
    actors = unreal.EditorLevelLibrary.get_all_level_actors()
    for actor in actors:
        label = actor.get_actor_label()
        if label.startswith(CHARACTER_PREFIX) or label.startswith(LABEL_PREFIX) or label.startswith(BALL_PREFIX):
            unreal.EditorLevelLibrary.destroy_actor(actor)


def spawn_label(actor_name, location, team):
    text_actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.TextRenderActor,
        location + unreal.Vector(0.0, 0.0, 240.0),
        unreal.Rotator(0.0, 0.0, 0.0),
    )
    text_actor.set_actor_label(f"{LABEL_PREFIX}{actor_name}")
    text_component = text_actor.get_component_by_class(unreal.TextRenderComponent)
    text_component.set_editor_property("text", actor_name)
    text_component.set_editor_property("horizontal_alignment", unreal.HorizTextAligment.EHTA_CENTER)
    text_component.set_editor_property("world_size", 64.0)
    text_component.set_editor_property("x_scale", 1.5)
    text_component.set_editor_property("y_scale", 1.5)
    if team == "Away":
        text_component.set_editor_property("text_render_color", unreal.Color(255, 64, 64, 255))
    else:
        text_component.set_editor_property("text_render_color", unreal.Color(64, 160, 255, 255))


def spawn_character(mesh, entry):
    rotation = unreal.Rotator(
        entry.get("pitch", 0.0),
        entry.get("yaw", 0.0),
        entry.get("roll", 0.0),
    )
    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.SkeletalMeshActor,
        entry["location"],
        rotation,
    )
    actor_name = entry["name"]
    actor.set_actor_label(f"{CHARACTER_PREFIX}{actor_name}")
    actor.set_actor_scale3d(unreal.Vector(1.0, 1.0, 1.0))
    actor.set_actor_location(entry["location"], False, False)
    actor.set_actor_rotation(rotation, False)

    mesh_component = actor.get_editor_property("skeletal_mesh_component")
    mesh_component.set_editor_property("skeletal_mesh_asset", mesh)
    mesh_component.set_editor_property("component_tags", [entry["team"], actor_name, entry["role"]])

    role_material = unreal.EditorAssetLibrary.load_asset(CHARACTER_MATERIAL_PATHS[entry["role"]])
    if role_material:
        material_count = mesh_component.get_num_materials()
        for material_index in range(material_count):
            mesh_component.set_material(material_index, role_material)

    spawn_label(actor_name, entry["location"], entry["team"])


def spawn_ball():
    ball_mesh = unreal.EditorAssetLibrary.load_asset(BALL_MESH_PATH)
    if not ball_mesh:
        raise RuntimeError(f"Failed to load prototype ball mesh: {BALL_MESH_PATH}")

    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.StaticMeshActor,
        BALL_LAYOUT["location"],
        unreal.Rotator(0.0, 0.0, 0.0),
    )
    actor.set_actor_label(BALL_PREFIX)
    actor.set_actor_scale3d(BALL_LAYOUT["scale"])
    actor.set_actor_location(BALL_LAYOUT["location"], False, False)
    actor.set_actor_rotation(unreal.Rotator(0.0, 0.0, 0.0), False)

    mesh_component = actor.get_component_by_class(unreal.StaticMeshComponent)
    mesh_component.set_editor_property("static_mesh", ball_mesh)
    mesh_component.set_editor_property("component_tags", ["Baseball", "Prototype"])

    ball_material = unreal.EditorAssetLibrary.load_asset(BALL_MATERIAL_PATH)
    if ball_material:
        material_count = mesh_component.get_num_materials()
        for material_index in range(material_count):
            mesh_component.set_material(material_index, ball_material)

    spawn_label(BALL_LAYOUT["name"], BALL_LAYOUT["location"], "Home")


def main():
    role_meshes = {}
    for role_name in ROLE_MESH_SOURCES.keys():
        mesh_path = import_character_mesh(role_name)
        mesh = unreal.EditorAssetLibrary.load_asset(mesh_path)
        if not mesh:
            raise RuntimeError(f"Failed to load skeletal mesh: {mesh_path}")
        role_meshes[role_name] = {
            "path": mesh_path,
            "asset": mesh,
        }

    if not unreal.EditorAssetLibrary.does_asset_exist(MAP_PATH):
        raise RuntimeError(f"Map does not exist yet: {MAP_PATH}")

    world = unreal.EditorLoadingAndSavingUtils.load_map(MAP_PATH)
    if not world:
        raise RuntimeError(f"Failed to load map: {MAP_PATH}")

    destroy_previous_actors()

    for entry in LINEUP_LAYOUT:
        spawn_character(role_meshes[entry["role"]]["asset"], entry)

    spawn_ball()

    unreal.EditorLevelLibrary.save_current_level()
    unreal.EditorLoadingAndSavingUtils.save_dirty_packages(True, True)
    unreal.EditorAssetLibrary.sync_browser_to_objects(
        [MAP_PATH] + [role_meshes[role_name]["path"] for role_name in role_meshes.keys()]
    )
    unreal.log("Jamsil prototype characters placed successfully.")


if __name__ == "__main__":
    main()
