#include "../include/DeadlyPlatform.h"

DeadlyPlatform::DeadlyPlatform(const sf::Vector2f& position, const sf::Vector2f& size, float damage)
    : Platform(position, size), Killer(damage) 
    {
        setColor(sf::Color::Red);
    }

DeadlyPlatform::~DeadlyPlatform() {}

bool DeadlyPlatform::isDeadly() const {
    return true;
}