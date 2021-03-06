#Set project with C++17
project('OpenE2140', 'c', 'cpp', default_options : ['c_std=c11', 'cpp_std=c++17'])

#Vars
opene2140_deps = []
opene2140_is_macos = host_machine.system() == 'darwin'
opene2140_is_windows = host_machine.system() == 'windows'

#Load SDL2
sdl2_dep = dependency('sdl2', version : '>=2.0.7')
opene2140_deps += [sdl2_dep]

#Load OpenGL
opengl_dep = dependency('gl')
opene2140_deps += [opengl_dep]

#Load GLEW
glew_dep = dependency('glew')
opene2140_deps += [glew_dep]

#Load GLM
glm_dep = dependency('glm')
opene2140_deps += [glm_dep]

#Load json
json_dep = dependency('nlohmann_json')
opene2140_deps += [json_dep]

#Load boost libs
boost_dep = dependency('boost',
    modules: ['filesystem'],
    version : '>=1.66',
    required : false,
)
if boost_dep.found()
    #Boost needs dl in some OSes like linux
    dl_dep = meson.get_compiler('c').find_library('dl', required : false)
    opene2140_deps += [boost_dep, dl_dep]
endif

#Create configuration
opene2140_cfg = configuration_data()
opene2140_cfg.set('OPENE2140_BUILD_CONFIG_PLACEHOLDER_H', '"OpenE2140"', description: 'Disables placeholder build config')
opene2140_cfg.set('GAME_NAME', '"OpenE2140"', description: 'Engine name')
opene2140_cfg.set('GAME_VERSION_MAJOR', 0, description: 'Engine version major digit')
opene2140_cfg.set('GAME_VERSION_MINOR', 3, description: 'Engine version minor digit')
opene2140_cfg.set('GAME_UPDATES_PER_SECOND', 30, description: 'Updates of game logic per second')

#Variable config
opene2140_cfg.set('GAME_USE_BOOST', boost_dep.found() ? 'true' : 'false', description: 'Enables the use of Boost library')
opene2140_cfg.set('GAME_IS_MACOS', opene2140_is_macos ? 'true' : 'false', description: 'True if being building on macos')
opene2140_cfg.set('GAME_IS_WINDOWS', opene2140_is_windows ? 'true' : 'false', description: 'True if being building on windows')

#Save the config to header file
configure_file(output: 'build_config.h', configuration: opene2140_cfg)

#Set source files
opene2140_src = [
    'src/engine/core/engine.cpp',
    'src/engine/core/error_possible.cpp',
    'src/engine/core/utils.cpp',
    'src/engine/graphics/renderer.cpp',
    'src/engine/graphics/palette.cpp',
    'src/engine/graphics/image.cpp',
    'src/engine/graphics/window.cpp',
    'src/engine/graphics/animation.cpp',
    'src/engine/math/rectangle.cpp',
    'src/engine/math/vector2.cpp',
    'src/engine/math/number.cpp',
    'src/engine/io/log.cpp',
    'src/engine/io/file.cpp',
    'src/engine/io/timer.cpp',
    'src/engine/io/config.cpp',
    'src/engine/io/event_handler.cpp',
    'src/engine/io/event_listener.cpp',
    'src/engine/io/event_dispatcher.cpp',
    'src/engine/gui/locale.cpp',
    'src/engine/gui/gui_view.cpp',
    'src/engine/gui/gui_root.cpp',
    'src/engine/gui/game/gui_game_root.cpp',
    'src/engine/gui/game/simulation_view.cpp',
    'src/engine/gui/game/selection_overlay.cpp',
    'src/engine/gui/game/camera_view.cpp',
    'src/engine/gui/game/sidebar.cpp',
    'src/engine/assets/asset.cpp',
    'src/engine/assets/asset_manager.cpp',
    'src/engine/assets/asset_processor.cpp',
    'src/engine/assets/asset_image.cpp',
    'src/engine/assets/asset_palette.cpp',
    'src/engine/assets/asset_level.cpp',
    'src/engine/entities/entity_config.cpp',
    'src/engine/entities/entity_manager.cpp',
    'src/engine/entities/entity_factory.cpp',
    'src/engine/simulation/simulation.cpp',
    'src/engine/simulation/player.cpp',
    'src/engine/simulation/faction.cpp',
    'src/engine/simulation/entity_store.cpp',
    'src/engine/simulation/entity.cpp',
    'src/engine/simulation/world/tile.cpp',
    'src/engine/simulation/world/world.cpp',
    'src/engine/simulation/pathfinder/astar.cpp',
    'src/engine/simulation/pathfinder/astar_comparator.cpp',
    'src/engine/simulation/pathfinder/path_handler.cpp',
    'src/engine/simulation/pathfinder/path_request.cpp',
    'src/engine/simulation/components/faction_component.cpp',
    'src/engine/simulation/components/player_component.cpp',
    'src/engine/simulation/components/image_component.cpp',
    'src/engine/simulation/components/energy_component.cpp',
    'src/engine/simulation/components/rotation_component.cpp',
    'src/engine/simulation/components/attachment_component.cpp',
    'src/game/assets/asset_processor_datpal.cpp',
    'src/game/assets/asset_processor_level.cpp',
    'src/game/assets/asset_processor_wd.cpp',
    'src/game/assets/asset_processor_mix.cpp',
    'src/game/assets/asset_processor_fixes.cpp',
    'src/game/assets/asset_level_game.cpp',
    'src/game/components/palette_component.cpp',
    'src/game/components/sprite_rotation_component.cpp',
    'src/game/components/sprite_damage_component.cpp',
    'src/game/components/movement_component.cpp',
    'src/game/entities/object.cpp',
    'src/game/entities/building.cpp',
    'src/game/entities/unit.cpp',
    'src/game/entities/attachment.cpp',
    'src/game/io/event_listener_debug.cpp',
    'src/game/core/game.cpp',
    'src/game/core/main.cpp',
]
library_src = [
    #libfixmath
    'lib/libfixmath/libfixmath/fix16.c',
    'lib/libfixmath/libfixmath/fix16_trig.c',
    'lib/libfixmath/libfixmath/fix16_sqrt.c',
]

#Include headers
opene2140_incs = include_directories(
    #So we can use the config headers generated by build system
    '.',
    #Source headers
    'src',
    #Lib headers
    'lib/spdlog/include',
    'lib/libfixmath',
    'lib/stb',
)

#Include extra files
if opene2140_is_macos
  install_data('Info.plist', install_dir: 'Contents')
endif

#Create executable, set definitions and link it
opene2140_exe = executable(
    'opene2140',
    opene2140_src + library_src,
    include_directories: opene2140_incs,
    dependencies: opene2140_deps,
    install: true,
    override_options : ['c_std=c11', 'cpp_std=c++17']
)
