//
// Created by Ion Agorria on 13/06/19
//
#include "engine/simulation/world/world.h"
#include "object.h"

void Object::simulationChanged() {
    if (isActive()) {
        //Set bounds
        setBounds(Vector2(simulation->tileSize));

        //Load image according to tileset
        World* world = simulation->getWorld();
        setImageFromSprite("default_" + std::to_string(world->tilesetIndex));
    }

    Entity::simulationChanged();
}

void Object::draw() {
    ImageComponent::draw(renderer);
}

void Tree::draw() {
    ImageComponent::draw(renderer);
}

void Ore::draw() {
    ImageComponent::draw(renderer);
}

void Wall::draw() {
    ImageComponentSlotted<0>::draw(renderer);
    ImageComponentSlotted<1>::draw(renderer);
    ImageComponentSlotted<2>::draw(renderer);
    ImageComponentSlotted<3>::draw(renderer);
}