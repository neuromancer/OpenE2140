//
// Created by Ion Agorria on 2018/06/03
//
#ifndef OPENE2140_ENTITY_H
#define OPENE2140_ENTITY_H

#include "engine/simulation/components/component.h"
#include "engine/core/macros.h"
#include "engine/core/to_string.h"
#include "engine/math/rectangle.h"
#include "engine/graphics/image.h"

class Tile;
class Simulation;
class Renderer;
class EntityConfig;
class Entity;

using entity_ptr = std::shared_ptr<Entity>;
using entity_changes_count_t = uint16_t;

/**
 * Base entity in game, this is the common interface between world and entities
 */
class Entity: public IToString {
protected:
    /**
     * Unique ID for entity
     */
    entity_id_t id = 0;

    /**
     * This entity config such as type and stats
     */
    const EntityConfig* config = nullptr;

    /**
     * Simulation which this entity belongs
     */
    Simulation* simulation = nullptr;

    /**
     * Renderer to use when drawing this entity
     */
    Renderer* renderer = nullptr;

    /**
     * Entity center position
     */
    Vector2 position;

    /**
     * Entity direction which is facing
     */
    entity_direction_t direction = 0;

    /**
     * Entity bounding rectangle if any
     */
    Rectangle bounds;

    /**
     * Tile or tiles which this entity is currently occupying
     */
    std::vector<Tile*> tiles;

    /**
     * Max health of entity or 0 for none
     */
    entity_health_t maxHealth = 0;

    /**
     * Current health of entity
     */
    entity_health_t currentHealth = 0;

    /**
     * Flag for active state
     */
    bool active = false;

    /**
     * Flag for disable state
     */
    bool disable = false;

    /**
     * Flag for selectable
     */
    bool selectable = false;

    /**
     * Parent of this entity which is attached to if any
     */
    Entity* parent = nullptr;

    /**
     * Last changes count since last update
     * This way we can know when to update
     */
    entity_changes_count_t lastChangesCount = 0;

    /**
     * Add components method forwarding so extended entities can override them
     */
    COMPONENT_METHODS(COMPONENT_METHOD_FORWARD_VIRTUAL)
public:
    /**
     * Every time a change occurs in entity this count is incremented
     */
    entity_changes_count_t changesCount = 0;

    /**
     * Required flags for tiles to be possible to move in
     */
    tile_flags_t tileFlagsRequired = 0;

    /**
     * Entity flags that are set in tiles when this entity is present,
     * this is also used to discard tiles containing entities which this entity can't transverse
     */
    tile_flags_t entityFlagsMask = 0;

    /**
     * Entity constructor
     */
    Entity();

    /**
     * Entity destructor
     */
    ~Entity() override;

    /**
     * Macros
     */
    NON_COPYABLE(Entity)
    TYPE_NAME_OVERRIDE(Entity)

    /**
     * Does the entity setup after object creation
     */
    virtual void setup(EntityConfig* newConfig);

    /**
     * @return entity id
     */
    entity_id_t getID() const;

    /**
     * @return entity pointer
     */
    std::shared_ptr<Entity> getEntityPtr() const;

    /**
     * @return entity position
     */
    const Vector2& getPosition() const;

    /**
     * Set entity position
     *
     * @param newPosition position to set
     */
    void setPosition(const Vector2& newPosition);

    /**
     * @return entity direction
     */
    entity_direction_t getDirection() const;

    /**
     * Set entity direction
     *
     * @param newDirection direction to set
     */
    void setDirection(entity_direction_t newDirection);

    /**
     * @return entity bounds
     */
    const Rectangle& getBounds() const;

    /**
     * Set entity bounds
     *
     * @param newBounds bounds to set
     */
    void setBounds(const Vector2& newBounds);

    /**
     * Set entity max health
     *
     * @param maxHealth to set or 0 for none
     */
    void setMaxHealth(entity_health_t maxHealth);

    /** @return entity max health */
    entity_health_t getMaxHealth();

    /**
     * Set entity current health
     *
     * @param currentHealth to set
     */
    void setCurrentHealth(entity_health_t currentHealth);

    /** @return entity current health */
    entity_health_t getCurrentHealth();

    /**
     * Adds health to entity
     *
     * @param health to apply
     */
    void addHealth(entity_health_t health);

    /**
     * Removes health from entity
     *
     * @param health to remove
     */
    void removeHealth(entity_health_t health);

    /** @return if entity has health */
    bool hasHealth();

    /** @return if entity has health and is damaged */
    bool isDamaged();

    /** @return if entity has health and is destroyed */
    bool isDestroyed();

    /**
     * @return entity config if any
     */
    const EntityConfig* getConfig() const;

    /**
     * Sets this entity parent
     */
    void setParent(Entity* entity);

    /**
     * @return entity parent if any
     */
    Entity* getParent() const;

    /**
     * @return entity simulation if any
     */
    Simulation* getSimulation() const;

    /**
     * Called when entity is added to simulation
     *
     * @param entityID allocated for this entity
     * @param simulation which entity was added to
     */
    void addedToSimulation(entity_id_t entityID, Simulation* simulation);

    /**
     * Called when entity is removed from simulation
     */
    void removedFromSimulation();

    /**
     * Called when entity is added or removed from simulation
     */
    virtual void simulationChanged();

    /**
     * Updates the entity state
     */
    virtual void update();

    /**
     * Called when entity is changed according to it's hangesCount
     */
    virtual void entityChanged();

    /**
     * Called when this entity is requested to draw
     */
    virtual void draw();

    /**
     * @return true if entity is considered active (has ID and is inside simulation)
     */
    bool isActive() const;

    /**
     * @return true if entity is considered disabled
     */
    bool isDisable() const;

    /**
     * Sets this entity disable state
     *
     * @param newDisable state to set
     */
    void setDisable(bool newDisable);

    /**
     * @return true if entity is considered selectable
     */
    bool isSelectable() const;

    /**
     * Sets this entity selectable
     *
     * @param newSelectable state to set
     */
    void setSelectable(bool newSelectable);

    /**
     * In case of none this method will return null
     * In case of several tiles it will return the first tile in collection, which should be the center
     * @return tile which this entity is occupying
     */
    Tile* getTile();

    /**
     * @return tile or tiles which this entity is occupying
     */
    const std::vector<Tile*>& getTiles() const;

    /**
     * @return tile or tiles which this entity is occupying
     */
    std::vector<Tile*>& getTiles();

    /**
     * Clears all tiles this entity might have
     */
    void clearTiles();

    /*
     * IToString
     */

    std::string toStringContent() const override;
};

/**
 * Macro for entity class definition without components
 *
 * T_ENTITY specifies the class type name
 */
#define CLASS_ENTITY(T_BASE, T_ENTITY) \
class T_ENTITY: public T_BASE { \
public: \
    /** Update type name */ \
    TYPE_NAME_OVERRIDE(T_ENTITY)

/**
 * Macro for common entity class definition with provided components
 *
 * T_ENTITY specifies the class type name
 * The rest of args are the component classes to be attached into this class
 */
#define CLASS_ENTITY_COMPONENTS(T_BASE, T_ENTITY, ...) \
class T_ENTITY: public ComponentBinder<T_BASE, T_ENTITY ,##__VA_ARGS__> { \
public: \
    /** Update type name */ \
    TYPE_NAME_OVERRIDE(T_ENTITY)

#endif //OPENE2140_ENTITY_H
