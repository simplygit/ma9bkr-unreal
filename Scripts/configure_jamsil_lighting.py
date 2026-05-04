import unreal


MAP_PATH = "/Game/Maps/Stadiums/L_Jamsil_Prototype"
LIGHT_PREFIX = "KR_Prototype_Light_"


def destroy_previous_lighting():
    actors = unreal.EditorLevelLibrary.get_all_level_actors()
    for actor in actors:
        label = actor.get_actor_label()
        if label.startswith(LIGHT_PREFIX):
            unreal.EditorLevelLibrary.destroy_actor(actor)


def set_component_movable(component):
    if component:
        component.set_editor_property("mobility", unreal.ComponentMobility.MOVABLE)


def configure_existing_lights():
    actors = unreal.EditorLevelLibrary.get_all_level_actors()
    for actor in actors:
        actor_class_name = actor.get_class().get_name()
        if "Light" not in actor_class_name:
            continue

        root_component = actor.get_editor_property("root_component")
        set_component_movable(root_component)

        light_component = actor.get_component_by_class(unreal.LightComponentBase)
        set_component_movable(light_component)


def spawn_directional_light():
    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.DirectionalLight,
        unreal.Vector(0.0, 0.0, 2500.0),
        unreal.Rotator(-32.0, -38.0, 0.0),
    )
    actor.set_actor_label(f"{LIGHT_PREFIX}Directional")
    light_component = actor.get_component_by_class(unreal.DirectionalLightComponent)
    set_component_movable(light_component)
    light_component.set_editor_property("intensity", 10.0)
    light_component.set_editor_property("cast_shadows", True)
    light_component.set_editor_property("atmosphere_sun_light", True)
    light_component.set_editor_property("atmosphere_sun_light_index", 0)


def spawn_sky_light():
    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.SkyLight,
        unreal.Vector(0.0, 0.0, 1200.0),
        unreal.Rotator(0.0, 0.0, 0.0),
    )
    actor.set_actor_label(f"{LIGHT_PREFIX}Sky")
    light_component = actor.get_component_by_class(unreal.SkyLightComponent)
    set_component_movable(light_component)
    light_component.set_editor_property("intensity", 1.2)
    light_component.set_editor_property("real_time_capture", True)


def spawn_sky_atmosphere():
    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.SkyAtmosphere,
        unreal.Vector(0.0, 0.0, 0.0),
        unreal.Rotator(0.0, 0.0, 0.0),
    )
    actor.set_actor_label(f"{LIGHT_PREFIX}Atmosphere")


def spawn_exponential_height_fog():
    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.ExponentialHeightFog,
        unreal.Vector(0.0, 0.0, 0.0),
        unreal.Rotator(0.0, 0.0, 0.0),
    )
    actor.set_actor_label(f"{LIGHT_PREFIX}Fog")
    fog_component = actor.get_component_by_class(unreal.ExponentialHeightFogComponent)
    set_component_movable(fog_component)
    fog_component.set_editor_property("fog_density", 0.01)
    fog_component.set_editor_property("fog_height_falloff", 0.2)


def spawn_post_process_volume():
    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.PostProcessVolume,
        unreal.Vector(0.0, 0.0, 0.0),
        unreal.Rotator(0.0, 0.0, 0.0),
    )
    actor.set_actor_label(f"{LIGHT_PREFIX}PostProcess")
    actor.set_editor_property("unbound", True)


def configure_world_settings(world):
    world_settings = world.get_world_settings()
    world_settings.set_editor_property("force_no_precomputed_lighting", True)


def main():
    if not unreal.EditorAssetLibrary.does_asset_exist(MAP_PATH):
        raise RuntimeError(f"Map does not exist: {MAP_PATH}")

    world = unreal.EditorLoadingAndSavingUtils.load_map(MAP_PATH)
    if not world:
        raise RuntimeError(f"Failed to load map: {MAP_PATH}")

    configure_world_settings(world)
    configure_existing_lights()
    destroy_previous_lighting()

    spawn_directional_light()
    spawn_sky_light()
    spawn_sky_atmosphere()
    spawn_exponential_height_fog()
    spawn_post_process_volume()

    unreal.EditorLevelLibrary.save_current_level()
    unreal.EditorLoadingAndSavingUtils.save_dirty_packages(True, True)
    unreal.EditorAssetLibrary.sync_browser_to_objects([MAP_PATH])
    unreal.log("Jamsil prototype lighting configured for movable preview workflow.")


if __name__ == "__main__":
    main()
