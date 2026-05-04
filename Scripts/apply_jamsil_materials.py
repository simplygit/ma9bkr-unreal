import os

import unreal


UNITY_ROOT = r"F:\workspace_f\KR_trunk"

TEXTURE_SOURCE_DIR = os.path.join(UNITY_ROOT, "Assets", "03_Arts", "Tex")

STADIUM_TEXTURE_DEST = "/Game/Stadiums/Jamsil/Textures"
STADIUM_MATERIAL_DEST = "/Game/Stadiums/Jamsil/Materials"
CHARACTER_MATERIAL_DEST = "/Game/Characters/Prototype/Materials"
STADIUM_MESH_DIR = "/Game/Stadiums/Jamsil/Meshes"

TEXTURE_IMPORTS = {
    "T_Jamsil_Grass": os.path.join(TEXTURE_SOURCE_DIR, "Grass_RGB_Mask_Jamsil.TGA"),
    "T_Jamsil_Ground": os.path.join(TEXTURE_SOURCE_DIR, "Ground_RGB_Mask_Jamsil_2026.tga"),
    "T_Jamsil_LensFlare": os.path.join(TEXTURE_SOURCE_DIR, "Stadium_Jamsil_LensFlare.PNG"),
}

STADIUM_MATERIAL_PATHS = {
    "Grass": f"{STADIUM_MATERIAL_DEST}/M_Jamsil_Grass.M_Jamsil_Grass",
    "Ground": f"{STADIUM_MATERIAL_DEST}/M_Jamsil_Ground.M_Jamsil_Ground",
    "Chalk": f"{STADIUM_MATERIAL_DEST}/M_Jamsil_Chalk.M_Jamsil_Chalk",
    "Concrete": f"{STADIUM_MATERIAL_DEST}/M_Jamsil_Concrete.M_Jamsil_Concrete",
    "Seat": f"{STADIUM_MATERIAL_DEST}/M_Jamsil_Seat.M_Jamsil_Seat",
    "Net": f"{STADIUM_MATERIAL_DEST}/M_Jamsil_Net.M_Jamsil_Net",
    "Sky": f"{STADIUM_MATERIAL_DEST}/M_Jamsil_Sky.M_Jamsil_Sky",
    "Lens": f"{STADIUM_MATERIAL_DEST}/M_Jamsil_Lens.M_Jamsil_Lens",
    "Light": f"{STADIUM_MATERIAL_DEST}/M_Jamsil_Light.M_Jamsil_Light",
    "Structure": f"{STADIUM_MATERIAL_DEST}/M_Jamsil_Structure.M_Jamsil_Structure",
}

CHARACTER_MATERIAL_PATHS = {
    "Pitcher": f"{CHARACTER_MATERIAL_DEST}/M_Prototype_Pitcher.M_Prototype_Pitcher",
    "Batter": f"{CHARACTER_MATERIAL_DEST}/M_Prototype_Batter.M_Prototype_Batter",
    "Catcher": f"{CHARACTER_MATERIAL_DEST}/M_Prototype_Catcher.M_Prototype_Catcher",
    "Fielder": f"{CHARACTER_MATERIAL_DEST}/M_Prototype_Fielder.M_Prototype_Fielder",
    "Umpire": f"{CHARACTER_MATERIAL_DEST}/M_Prototype_Umpire.M_Prototype_Umpire",
}


def ensure_directory(path):
    if not unreal.EditorAssetLibrary.does_directory_exist(path):
        unreal.EditorAssetLibrary.make_directory(path)


def import_textures():
    ensure_directory("/Game/Stadiums")
    ensure_directory("/Game/Stadiums/Jamsil")
    ensure_directory(STADIUM_TEXTURE_DEST)

    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    tasks = []

    for texture_name, source_path in TEXTURE_IMPORTS.items():
        if not os.path.exists(source_path):
            raise RuntimeError(f"Missing source texture: {source_path}")

        task = unreal.AssetImportTask()
        task.set_editor_property("filename", source_path)
        task.set_editor_property("destination_path", STADIUM_TEXTURE_DEST)
        task.set_editor_property("destination_name", texture_name)
        task.set_editor_property("automated", True)
        task.set_editor_property("replace_existing", True)
        task.set_editor_property("replace_existing_settings", True)
        task.set_editor_property("save", True)
        tasks.append(task)

    asset_tools.import_asset_tasks(tasks)


def create_material_asset(asset_name, package_path):
    asset_path = f"{package_path}/{asset_name}.{asset_name}"
    existing = unreal.EditorAssetLibrary.load_asset(asset_path)
    if existing:
        return existing

    factory = unreal.MaterialFactoryNew()
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    material = asset_tools.create_asset(asset_name, package_path, unreal.Material, factory)
    if not material:
        raise RuntimeError(f"Failed to create material: {asset_path}")
    return material


def build_color_material(asset_name, package_path, color, roughness=0.8, metallic=0.0, emissive_strength=0.0, unlit=False, two_sided=False):
    material = create_material_asset(asset_name, package_path)
    material.set_editor_property("two_sided", two_sided)
    if unlit:
        material.set_editor_property("shading_model", unreal.MaterialShadingModel.MSM_UNLIT)

    unreal.MaterialEditingLibrary.delete_all_material_expressions(material)

    color_expr = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionConstant3Vector, -500, 0)
    color_expr.set_editor_property("constant", color)

    if unlit:
        unreal.MaterialEditingLibrary.connect_material_property(color_expr, "", unreal.MaterialProperty.MP_EMISSIVE_COLOR)
    else:
        unreal.MaterialEditingLibrary.connect_material_property(color_expr, "", unreal.MaterialProperty.MP_BASE_COLOR)

    roughness_expr = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionConstant, -500, 180)
    roughness_expr.set_editor_property("r", roughness)
    unreal.MaterialEditingLibrary.connect_material_property(roughness_expr, "", unreal.MaterialProperty.MP_ROUGHNESS)

    metallic_expr = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionConstant, -500, 260)
    metallic_expr.set_editor_property("r", metallic)
    unreal.MaterialEditingLibrary.connect_material_property(metallic_expr, "", unreal.MaterialProperty.MP_METALLIC)

    if emissive_strength > 0.0 and not unlit:
        emissive_color = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionMultiply, -220, -160)
        emissive_base = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionConstant3Vector, -500, -200)
        emissive_base.set_editor_property("constant", color)
        emissive_power = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionConstant, -500, -120)
        emissive_power.set_editor_property("r", emissive_strength)
        unreal.MaterialEditingLibrary.connect_material_expressions(emissive_base, "", emissive_color, "A")
        unreal.MaterialEditingLibrary.connect_material_expressions(emissive_power, "", emissive_color, "B")
        unreal.MaterialEditingLibrary.connect_material_property(emissive_color, "", unreal.MaterialProperty.MP_EMISSIVE_COLOR)

    unreal.MaterialEditingLibrary.layout_material_expressions(material)
    unreal.EditorAssetLibrary.save_loaded_asset(material)
    return material


def build_texture_material(asset_name, texture_asset_path, color_tint=None, roughness=0.85, unlit=False):
    material = create_material_asset(asset_name, STADIUM_MATERIAL_DEST)
    texture = unreal.EditorAssetLibrary.load_asset(texture_asset_path)
    if not texture:
        raise RuntimeError(f"Failed to load texture: {texture_asset_path}")

    if unlit:
        material.set_editor_property("shading_model", unreal.MaterialShadingModel.MSM_UNLIT)

    unreal.MaterialEditingLibrary.delete_all_material_expressions(material)

    texture_expr = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionTextureSample, -620, 0)
    texture_expr.set_editor_property("texture", texture)

    final_expr = texture_expr
    if color_tint:
        tint_expr = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionConstant3Vector, -620, 180)
        tint_expr.set_editor_property("constant", color_tint)
        mult_expr = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionMultiply, -320, 0)
        unreal.MaterialEditingLibrary.connect_material_expressions(texture_expr, "RGB", mult_expr, "A")
        unreal.MaterialEditingLibrary.connect_material_expressions(tint_expr, "", mult_expr, "B")
        final_expr = mult_expr

    if unlit:
        unreal.MaterialEditingLibrary.connect_material_property(final_expr, "RGB", unreal.MaterialProperty.MP_EMISSIVE_COLOR)
    else:
        unreal.MaterialEditingLibrary.connect_material_property(final_expr, "RGB", unreal.MaterialProperty.MP_BASE_COLOR)

    roughness_expr = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionConstant, -620, 260)
    roughness_expr.set_editor_property("r", roughness)
    unreal.MaterialEditingLibrary.connect_material_property(roughness_expr, "", unreal.MaterialProperty.MP_ROUGHNESS)

    unreal.MaterialEditingLibrary.layout_material_expressions(material)
    unreal.EditorAssetLibrary.save_loaded_asset(material)
    return material


def create_materials():
    ensure_directory(STADIUM_MATERIAL_DEST)
    ensure_directory("/Game/Characters")
    ensure_directory("/Game/Characters/Prototype")
    ensure_directory(CHARACTER_MATERIAL_DEST)

    build_texture_material("M_Jamsil_Grass", f"{STADIUM_TEXTURE_DEST}/T_Jamsil_Grass.T_Jamsil_Grass", roughness=0.95)
    build_texture_material("M_Jamsil_Ground", f"{STADIUM_TEXTURE_DEST}/T_Jamsil_Ground.T_Jamsil_Ground", roughness=0.92)
    build_texture_material("M_Jamsil_Lens", f"{STADIUM_TEXTURE_DEST}/T_Jamsil_LensFlare.T_Jamsil_LensFlare", color_tint=unreal.LinearColor(1.0, 0.92, 0.75, 1.0), roughness=0.0, unlit=True)

    build_color_material("M_Jamsil_Chalk", STADIUM_MATERIAL_DEST, unreal.LinearColor(0.95, 0.95, 0.92, 1.0), roughness=0.7)
    build_color_material("M_Jamsil_Concrete", STADIUM_MATERIAL_DEST, unreal.LinearColor(0.58, 0.60, 0.64, 1.0), roughness=0.9)
    build_color_material("M_Jamsil_Seat", STADIUM_MATERIAL_DEST, unreal.LinearColor(0.16, 0.28, 0.76, 1.0), roughness=0.75)
    build_color_material("M_Jamsil_Net", STADIUM_MATERIAL_DEST, unreal.LinearColor(0.08, 0.08, 0.08, 1.0), roughness=1.0, two_sided=True)
    build_color_material("M_Jamsil_Sky", STADIUM_MATERIAL_DEST, unreal.LinearColor(0.44, 0.67, 0.95, 1.0), roughness=1.0, unlit=True)
    build_color_material("M_Jamsil_Light", STADIUM_MATERIAL_DEST, unreal.LinearColor(1.0, 0.96, 0.82, 1.0), roughness=0.1, emissive_strength=3.5)
    build_color_material("M_Jamsil_Structure", STADIUM_MATERIAL_DEST, unreal.LinearColor(0.35, 0.37, 0.40, 1.0), roughness=0.88)

    build_color_material("M_Prototype_Pitcher", CHARACTER_MATERIAL_DEST, unreal.LinearColor(0.96, 0.97, 1.0, 1.0), roughness=0.65)
    build_color_material("M_Prototype_Batter", CHARACTER_MATERIAL_DEST, unreal.LinearColor(0.82, 0.22, 0.22, 1.0), roughness=0.62)
    build_color_material("M_Prototype_Catcher", CHARACTER_MATERIAL_DEST, unreal.LinearColor(0.10, 0.12, 0.22, 1.0), roughness=0.55)
    build_color_material("M_Prototype_Fielder", CHARACTER_MATERIAL_DEST, unreal.LinearColor(0.66, 0.78, 1.0, 1.0), roughness=0.65)
    build_color_material("M_Prototype_Umpire", CHARACTER_MATERIAL_DEST, unreal.LinearColor(0.18, 0.18, 0.18, 1.0), roughness=0.6)


def choose_stadium_material(mesh_name):
    if "Lensflare" in mesh_name:
        return STADIUM_MATERIAL_PATHS["Lens"]
    if "Sky" in mesh_name:
        return STADIUM_MATERIAL_PATHS["Sky"]
    if "Countlight" in mesh_name:
        return STADIUM_MATERIAL_PATHS["Light"]
    if "net" in mesh_name:
        return STADIUM_MATERIAL_PATHS["Net"]
    if "Grass" in mesh_name:
        return STADIUM_MATERIAL_PATHS["Grass"]
    if "Ground" in mesh_name:
        return STADIUM_MATERIAL_PATHS["Ground"]
    if "Baseline" in mesh_name or mesh_name.endswith("_Base"):
        return STADIUM_MATERIAL_PATHS["Chalk"]
    if "_Seat" in mesh_name:
        return STADIUM_MATERIAL_PATHS["Seat"]
    if "APT_" in mesh_name or "Bridge" in mesh_name or "Building" in mesh_name or "Bulding" in mesh_name or "Bus_" in mesh_name or "Car_" in mesh_name or "Truck_" in mesh_name:
        return STADIUM_MATERIAL_PATHS["Structure"]
    return STADIUM_MATERIAL_PATHS["Concrete"]


def apply_material_to_static_mesh(mesh_asset_path, material_asset_path):
    mesh = unreal.EditorAssetLibrary.load_asset(mesh_asset_path)
    material = unreal.EditorAssetLibrary.load_asset(material_asset_path)
    if not mesh or not material:
        raise RuntimeError(f"Failed to load mesh/material pair: {mesh_asset_path} -> {material_asset_path}")

    static_materials = list(mesh.get_editor_property("static_materials"))
    if not static_materials:
        return

    for static_material in static_materials:
        static_material.set_editor_property("material_interface", material)

    mesh.set_editor_property("static_materials", static_materials)
    mesh.modify()
    unreal.EditorAssetLibrary.save_loaded_asset(mesh)


def apply_stadium_materials():
    asset_paths = unreal.EditorAssetLibrary.list_assets(STADIUM_MESH_DIR, recursive=False, include_folder=False)
    for asset_path in asset_paths:
        mesh_name = asset_path.split("/")[-1].split(".")[0]
        material_path = choose_stadium_material(mesh_name)
        apply_material_to_static_mesh(asset_path, material_path)


def main():
    import_textures()
    create_materials()
    apply_stadium_materials()
    unreal.EditorLoadingAndSavingUtils.save_dirty_packages(True, True)
    unreal.EditorAssetLibrary.sync_browser_to_objects(
        list(STADIUM_MATERIAL_PATHS.values()) + list(CHARACTER_MATERIAL_PATHS.values())
    )
    unreal.log("Jamsil stadium and prototype character materials created successfully.")


if __name__ == "__main__":
    main()
