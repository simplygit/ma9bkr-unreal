import os

import unreal


PROJECT_ROOT = r"F:\workspace_f\KR_unreal"
UNITY_ROOT = r"F:\workspace_f\KR_trunk"
FBX_SOURCE_DIR = os.path.join(UNITY_ROOT, "Assets", "03_Arts", "FBX", "Bg", "Stadium_Jamsil")

MESH_DESTINATION = "/Game/Stadiums/Jamsil/Meshes"
MAP_DESTINATION = "/Game/Maps/Stadiums/L_Jamsil_Prototype"

CORE_FBX_FILES = [
    "Stadium_Jamsil_Infield.FBX",
    "Stadium_Jamsil_Outfield.FBX",
    "Stadium_Jamsil_00.fbx",
    "Stadium_Jamsil_01.fbx",
    "Stadium_Jamsil_0.FBX",
    "Stadium_Jamsil_net.fbx",
    "Stadium_Jamsil_Sky.fbx",
    "Stadium_Jamsil_ETC.fbx",
    "SamSungBridge.fbx",
    "Countlight.fbx",
]

PLACEMENT_ORDER = [
    ("Stadium_Jamsil_Sky", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Base", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Baseline", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Ground", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Grass", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_00", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_01", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Infield_A1", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Infield_A2", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Infield_A3", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Infield_B1", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Infield_B2", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Infield_B3", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Infield_C", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Infield_D", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Outfield_A", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Outfield_B", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_Outfield_C", unreal.Vector(0.0, 0.0, 0.0)),
    ("Stadium_Jamsil_net", unreal.Vector(0.0, 0.0, 0.0)),
    ("APT_1", unreal.Vector(0.0, 0.0, 0.0)),
    ("APT_2", unreal.Vector(0.0, 0.0, 0.0)),
    ("APT_3", unreal.Vector(0.0, 0.0, 0.0)),
    ("Building_1", unreal.Vector(0.0, 0.0, 0.0)),
    ("Building_2", unreal.Vector(0.0, 0.0, 0.0)),
    ("Bulding_1", unreal.Vector(0.0, 0.0, 0.0)),
    ("ChungshinGirlsSchool", unreal.Vector(0.0, 0.0, 0.0)),
    ("Bridge_1", unreal.Vector(0.0, 0.0, 0.0)),
    ("Bridge_2", unreal.Vector(0.0, 0.0, 0.0)),
    ("SamSungBridge01", unreal.Vector(0.0, 0.0, 0.0)),
    ("Countlight", unreal.Vector(0.0, 0.0, 0.0)),
]


def ensure_directory(path):
    if not unreal.EditorAssetLibrary.does_directory_exist(path):
        unreal.EditorAssetLibrary.make_directory(path)


def build_import_task(source_path, destination_path):
    task = unreal.AssetImportTask()
    task.set_editor_property("filename", source_path)
    task.set_editor_property("destination_path", destination_path)
    task.set_editor_property("automated", True)
    task.set_editor_property("replace_existing", True)
    task.set_editor_property("replace_existing_settings", True)
    task.set_editor_property("save", True)

    options = unreal.FbxImportUI()
    options.set_editor_property("import_mesh", True)
    options.set_editor_property("import_as_skeletal", False)
    options.set_editor_property("import_textures", False)
    options.set_editor_property("import_materials", False)
    options.set_editor_property("import_animations", False)
    options.set_editor_property("mesh_type_to_import", unreal.FBXImportType.FBXIT_STATIC_MESH)

    static_mesh_data = options.get_editor_property("static_mesh_import_data")
    static_mesh_data.set_editor_property("combine_meshes", False)
    static_mesh_data.set_editor_property("auto_generate_collision", False)
    static_mesh_data.set_editor_property("generate_lightmap_u_vs", True)
    static_mesh_data.set_editor_property("remove_degenerates", True)
    static_mesh_data.set_editor_property("convert_scene", True)
    static_mesh_data.set_editor_property("convert_scene_unit", True)

    task.set_editor_property("options", options)
    return task


def import_core_meshes():
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    imported_assets = []

    tasks = []
    for file_name in CORE_FBX_FILES:
        source_path = os.path.join(FBX_SOURCE_DIR, file_name)
        if not os.path.exists(source_path):
            raise RuntimeError(f"Missing source FBX: {source_path}")
        tasks.append(build_import_task(source_path, MESH_DESTINATION))

    asset_tools.import_asset_tasks(tasks)

    for task in tasks:
        imported_assets.extend(task.get_editor_property("imported_object_paths"))

    unreal.log(f"Imported {len(imported_assets)} assets into {MESH_DESTINATION}")
    return imported_assets


def spawn_static_mesh(asset_path, actor_label, location):
    static_mesh = unreal.EditorAssetLibrary.load_asset(asset_path)
    if not static_mesh:
        raise RuntimeError(f"Failed to load static mesh: {asset_path}")

    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.StaticMeshActor,
        location,
        unreal.Rotator(0.0, 0.0, 0.0),
    )
    actor.set_actor_label(actor_label)

    mesh_component = actor.get_editor_property("static_mesh_component")
    mesh_component.set_editor_property("static_mesh", static_mesh)
    mesh_component.set_editor_property("mobility", unreal.ComponentMobility.STATIC)
    actor.set_actor_scale3d(unreal.Vector(1.0, 1.0, 1.0))

    return actor


def spawn_environment():
    sun = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.DirectionalLight,
        unreal.Vector(-4000.0, 0.0, 2500.0),
        unreal.Rotator(-32.0, -38.0, 0.0),
    )
    sun.set_actor_label("Jamsil_SunLight")

    sky_light = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.SkyLight,
        unreal.Vector(0.0, 0.0, 300.0),
        unreal.Rotator(0.0, 0.0, 0.0),
    )
    sky_light.set_actor_label("Jamsil_SkyLight")

    atmosphere = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.SkyAtmosphere,
        unreal.Vector(0.0, 0.0, 0.0),
        unreal.Rotator(0.0, 0.0, 0.0),
    )
    atmosphere.set_actor_label("Jamsil_SkyAtmosphere")

    fog = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.ExponentialHeightFog,
        unreal.Vector(0.0, 0.0, 0.0),
        unreal.Rotator(0.0, 0.0, 0.0),
    )
    fog.set_actor_label("Jamsil_Fog")

    # Skip cine camera creation in headless commandlet mode. It has caused
    # an engine-side divide-by-zero crash under null RHI on this machine.


def create_or_replace_level():
    if unreal.EditorAssetLibrary.does_asset_exist(MAP_DESTINATION):
        unreal.EditorAssetLibrary.delete_asset(MAP_DESTINATION)

    level_subsystem = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    if not level_subsystem.new_level(MAP_DESTINATION):
        raise RuntimeError(f"Failed to create level: {MAP_DESTINATION}")


def populate_level():
    spawn_environment()

    for mesh_name, location in PLACEMENT_ORDER:
        asset_path = f"{MESH_DESTINATION}/{mesh_name}.{mesh_name}"
        spawn_static_mesh(asset_path, mesh_name, location)

    unreal.EditorLevelLibrary.save_current_level()


def main():
    ensure_directory("/Game/Stadiums")
    ensure_directory("/Game/Stadiums/Jamsil")
    ensure_directory(MESH_DESTINATION)
    ensure_directory("/Game/Maps")
    ensure_directory("/Game/Maps/Stadiums")

    imported_assets = import_core_meshes()
    create_or_replace_level()
    populate_level()

    unreal.EditorLoadingAndSavingUtils.save_dirty_packages(True, True)
    unreal.EditorAssetLibrary.sync_browser_to_objects(imported_assets + [MAP_DESTINATION])
    unreal.log(f"Jamsil stadium import complete: {MAP_DESTINATION}")


if __name__ == "__main__":
    main()
