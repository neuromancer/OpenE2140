//
// Created by Ion Agorria on 13/06/19
//
#include "engine/simulation/entities/entity_config.h"
#include "engine/simulation/world/world.h"
#include "attachment.h"

void Attachment::simulationChanged() {
}

void Attachment::draw() {
    ImageComponent::draw(renderer);
}

void Spinner::simulationChanged() {
    if (isActive()) {
        //Set bounds
        World* world = simulation->getWorld();
        bounds.setCenter(position, Vector2(world->tileSize));

        //Setup the animation
        setAnimationFromSprite("default");
        animation->reverse = !clockwise;
    }

    Attachment::simulationChanged();
}

void Spinner::update() {
    Entity::update();
    if (!animation) {
        return;
    }

    //Check if animation finished, flip the image and reverse the animation
    if (animation->isFinished()) {
        animation->reverse = !animation->reverse;
    }
    imageFlipX = clockwise == animation->reverse;

    //Some sprites need compensation of X by 1 pixel
    if (config->code == "flywheel_mine") {
        size_t index = animation->getCurrentIndex();
        if (index < 2) {
            imageOffset.x = imageFlipX ? -1 : 1;
        } else {
            imageOffset.x = 0;
        }
    }
}