//
// Created by Ion Agorria on 12/07/19
//
#ifndef OPENE2140_PLAYER_H
#define OPENE2140_PLAYER_H

#include "engine/core/common.h"

class Faction;

/**
 * Contains Player related data
 */
class Player {
public:
    /**
     * ID for the player
     */
    const player_id_t id = 0;

    /**
     * Mask of this player based on id
     */
    const player_mask_t mask = 0;

protected:
    /**
     * Player faction
     */
    Faction* faction = nullptr;

    /**
     * Player enemies mask, those which are enemies are marked as 1 in their bit position (determined at mask)
     */
    player_mask_t enemies = 0;

public:
    /**
     * Name for this player
     */
    std::string name = "";

    /**
     * Player money amount
     */
    money_t money = 0;

    /**
     * Constructor
     */
    Player(player_id_t id, Faction* faction = nullptr, player_mask_t enemies = 0);

    /**
     * Destructor
     */
    virtual ~Player();

    /**
     * Disable copy
     */
    NON_COPYABLE(Player)

    /**
     * Type name
     */
    TYPE_NAME(Player)

    /**
     * Faction of this player if any
     *
     * @return faction
     */
    Faction* getFaction();

    /**
     * Returns if this player considers the other as enemy
     *
     * @param other player which to check with this player
     * @return true if enemy
     */
     bool isEnemy(const Player* other) const;

    /**
     * Adds player as this player enemy
     */
    void addEnemy(const Player* other);

    /**
     * Removes player as this player enemy
     */
    void removeEnemy(const Player* other);
};

#endif //OPENE2140_PLAYER_H