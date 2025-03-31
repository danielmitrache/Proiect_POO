#include "../include/DeadlyPlatform.h"

DeadlyPlatform::DeadlyPlatform(const sf::Vector2f& position, const sf::Vector2f& size, float damage, bool isVisible)
    : Platform(position, size), Killer(damage) 
    {
        setColor(sf::Color::Red);
        if (isVisible == false) {
            turnInvisible();
        }
    }

DeadlyPlatform::~DeadlyPlatform() {}

bool DeadlyPlatform::isDeadly() const {
    return true;
}

void DeadlyPlatform::turnInvisible() {
    setColor(sf::Color::Transparent);
}

void DeadlyPlatform::turnVisible() {
    setColor(sf::Color::Red);
}