//
// Created by Ion Agorria on 27/04/19
//
#ifndef OPENE2140_GAME_H
#define OPENE2140_GAME_H

#include "engine/core/engine.h"

class Player;
class Tile;

/**
 * Contain's game specific code
 */
class Game: public Engine {
protected:
    /**
     * Correction to apply when converting rotation
     */
    static number_t SpriteRotationCorrection;

    void run() override;

    void setupEventHandler() override;

    void setupAssetManager() override;

    void setupEntityManager() override;

    void setupSimulation(std::unique_ptr<SimulationParameters> parameters) override;

    void setupGUI() override;

    /**
     * Setup player extra colors as palette colors
     */
    void setupPlayerColors();

    /**
     * Sets a tile as reactor crate
     * TODO move this to some world or powerplant specific class
     */
    void setReactorCrate(Tile& tile);

public:
    /**
     * Does angle to sprite index conversion
     *
     * @param angle the input angle to convert
     * @param halfSide each side angle half
     * @param index the result of conversion
     * @return true if index is counter clockwise
     */
    static bool angleToSpriteIndex(number_t angle, number_t halfSide, uint16_t& index);

    /**
     * Does angle to sprite index approximate angle conversion
     *
     * @param angle the input angle to convert
     * @param side each side angle
     * @return the result of conversion
     */
    static number_t angleToSpriteAngle(number_t angle, number_t side);
};

#endif //OPENE2140_GAME_H
