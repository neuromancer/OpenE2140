//
// Created by Ion Agorria on 15/8/19
//

#include "engine/simulation/entities/entity_config.h"
#include "engine/simulation/components/player_component.h"
#include "engine/simulation/components/image_component.h"
#include "palette_component.h"

void PaletteComponent::construction() {
}

unsigned short test;
void PaletteComponent::update() {
    test+=10;
    setLight(0x8000 < test);
}

void PaletteComponent::setup() {
    const EntityConfig* config = base->getConfig();

    //Load flags based on default values per kind, if config value exists then use it
    hasPlayer = config->kind == ENTITY_KIND_UNIT || config->kind == ENTITY_KIND_BUILDING;
    hasPlayer = config->getData<bool>("palette_player", hasPlayer);
    hasLight = config->kind == ENTITY_KIND_BUILDING;
    hasLight = config->getData<bool>("palette_light", hasLight);
    hasShadow = false;
    if (config->kind == ENTITY_KIND_OBJECT) {
        hasShadow = config->type == "tree" || config->type == "wall" || config->type == "pipe";
    } else if (config->kind == ENTITY_KIND_UNIT || config->kind == ENTITY_KIND_BUILDING) {
        hasShadow = true;
    }
    hasShadow = config->getData<bool>("palette_shadow", hasShadow);

    //Set palette size using the entity config data
    switch (config->kind) {
        case ENTITY_KIND_OBJECT:
            if (hasShadow) {
                lowestEntry = PALETTE_OBJECT_SHADOW;
            }
            break;
        case ENTITY_KIND_UNIT:
            lowestEntry = PALETTE_UNIT_MOVEMENT0;
            break;
        case ENTITY_KIND_BUILDING:
            //Some buildings don't use certain indexes
            if (hasPlayer) {
                lowestEntry = PALETTE_BUILDING_PLAYER0;
            } else if (hasLight) {
                lowestEntry = PALETTE_BUILDING_LIGHT0;
            } else {
                lowestEntry = PALETTE_BUILDING_SHADOW_EXTRA;
            }
            break;
    }

    //Check if nothing to do
    if (0 == lowestEntry) {
        return;
    }

    //Create palette and set it to image component
    ImageComponent* imageComponent = GET_COMPONENT(base, ImageComponent);
    palette = std::make_shared<Palette>((PALETTE_MAX_INDEX+1) - lowestEntry, true);
    imageComponent->extraPalette = palette;
}

void PaletteComponent::simulationChanged() {
    if (!base->isActive()) {
        return;
    }
    if (!palette) {
        return;
    }
    const EntityConfig* config = base->getConfig();

    //Copy the original colors since some entities might not have lights or other stuff
    ImageComponent* imageComponent = GET_COMPONENT(base, ImageComponent);
    Palette* imagePalette = imageComponent->getImagePalette();
    if (imagePalette) {
        palette->setColors(imagePalette, lowestEntry, 0, palette->length() - 1);
    }

    //Load player color
    /* TODO set color to palette
    PlayerComponent* playerComponent = GET_COMPONENT(base, PlayerComponent);
    if (playerComponent) {
        Player* player = playerComponent->getPlayer();
        if (player) {
        }
    }
    */

    //Setup the rest
    setupShadows(config);
    palette->setColor(0xFF - lowestEntry, Color::CLEAR);
    palette->updateTexture();
}

void PaletteComponent::setupShadows(const EntityConfig* config) {
    size_t shadowMain = 0;
    size_t shadowExtra = 0;
    switch (config->kind) {
        case ENTITY_KIND_OBJECT:
            shadowMain = PALETTE_OBJECT_SHADOW;
            break;
        case ENTITY_KIND_UNIT:
            shadowMain = PALETTE_UNIT_SHADOW;
            break;
        case ENTITY_KIND_BUILDING:
            shadowMain = PALETTE_BUILDING_SHADOW;
            shadowExtra = PALETTE_BUILDING_SHADOW_EXTRA;
            break;

    }

    if (shadowMain) {
        palette->setColor(shadowMain - lowestEntry, Color::SHADOW_MAIN);
    }
    if (shadowExtra) {
        palette->setColor(shadowExtra - lowestEntry, Color::SHADOW_EXTRA);
    }
}

void PaletteComponent::setLight(bool state) {
    if (!palette || !hasLight) {
        return;
    }
    const EntityConfig* config = base->getConfig();
    switch (config->kind) {
        case ENTITY_KIND_UNIT:
            //TODO get color for this
            palette->setColor(
                    PALETTE_UNIT_LIGHT0 - lowestEntry,
                    state ? Color::BLUE : Color::BLACK
            );
            break;
        case ENTITY_KIND_BUILDING:
            //Some buildings don't use certain indexes
            if (config->code == "water_base") {
                return;
            }
            palette->setColor(
                    PALETTE_BUILDING_LIGHT0 - lowestEntry,
                    state ? Color::BUILDING_LIGHT0_ON : Color::BUILDING_LIGHT_OFF
            );
            palette->setColor(
                    PALETTE_BUILDING_LIGHT1 - lowestEntry,
                    state ? Color::BUILDING_LIGHT1_ON : Color::BUILDING_LIGHT_OFF
            );
            palette->setColor(
                    PALETTE_BUILDING_LIGHT2 - lowestEntry,
                    state ? Color::BUILDING_LIGHT2_ON : Color::BUILDING_LIGHT_OFF
            );
            palette->setColor(
                    PALETTE_BUILDING_LIGHT3 - lowestEntry,
                    state ? Color::BUILDING_LIGHT3_ON : Color::BUILDING_LIGHT_OFF
            );
            break;
        default:
            //Nothing to do
            return;
    }
    palette->updateTexture();
}

Palette* PaletteComponent::getPalette() const {
    return palette.get();
}
