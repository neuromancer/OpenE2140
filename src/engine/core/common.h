//
// Created by Ion Agorria on 26/03/18
//

#ifndef OPENE2140_COMMON_H
#define OPENE2140_COMMON_H

//Include GL in proper order
#include <GL/glew.h>
#include <SDL_opengl.h>

//Includes
#include "macros.h"
#include "build_config.h"
#include "build_config_placeholder.h"

//Constants
/** Game version string */
#define GAME_VERSION QUOTE_STR(GAME_VERSION_MAJOR) "." QUOTE_STR(GAME_VERSION_MINOR)
/** Full title of this game */
#define GAME_TITLE GAME_NAME " " GAME_VERSION
/** Delta per game update in ms */
#define GAME_DELTA (1000 / GAME_UPDATES_PER_SECOND)
/** Game main log tag for global use when required */
#define MAIN_LOG "Main"
/** File to dump when crashing */
#define GAME_DUMP_FILE "dump.bin"
/** File to store log output */
#define GAME_LOG_FILE "log.txt"
/** Default window resolution */
#define WINDOW_DEFAULT_RESOLUTION 1024, 768
/** Directory name containing assets */
#define GAME_ASSETS_DIR "assets"
/** Directory name containing data */
#define GAME_DATA_DIR "data"
/** Minimum texture size (texture packer fails under this) */
#define MINIMUM_TEXTURE_SIZE 512
/** Maximum texture size */
#define MAXIMUM_TEXTURE_SIZE 8192
/** Extra size to add when packing texture to avoid bleeding */
#define EXTRA_TEXTURE_SIZE 2
/** Texture unit for RGBA image texture */
#define TEXTURE_UNIT_IMAGE_RGBA GL_TEXTURE0
/** Texture unit for palette image texture */
#define TEXTURE_UNIT_IMAGE_PALETTE GL_TEXTURE1
/** Texture unit for colors palette texture */
#define TEXTURE_UNIT_PALETTE_COLORS GL_TEXTURE2
/** Texture unit for extra palette texture */
#define TEXTURE_UNIT_PALETTE_EXTRA GL_TEXTURE3
/** Constant for infinity cost */
#define PATHFINDER_INFINITY (static_cast<path_cost_t>(-1))
/** Flags for program */
#define FLAG_DEBUG               static_cast<unsigned>(               0b1)
#define FLAG_DEBUG_ALL           static_cast<unsigned>(              0b10)
#define FLAG_DEBUG_OPENGL        static_cast<unsigned>(             0b100)
#define FLAG_INSTALLATION_PARENT static_cast<unsigned>(         0b1000000)
#define FLAG_HEADLESS            static_cast<unsigned>(        0b10000000)
/** Flags for tile states */
#define TILE_FLAG_PASSABLE       static_cast<unsigned>(               0b1)
#define TILE_FLAG_WATER          static_cast<unsigned>(              0b10)
#define TILE_FLAG_SHORE          static_cast<unsigned>(             0b100)
#define TILE_FLAG_IMMUTABLE      static_cast<unsigned>(            0b1000) //Flag for immutable (is not affected by explosions or other stuff
#define TILE_FLAG_SAND           static_cast<unsigned>(           0b10000)
#define TILE_FLAG_ENTITY_TERRAIN static_cast<unsigned>(          0b100000) //Flag if contains an entity in ground/water
#define TILE_FLAG_ENTITY_AIR     static_cast<unsigned>(         0b1000000) //Flag if contains entity in air

#endif //OPENE2140_COMMON_H
