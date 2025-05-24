#include "../include/deadly_platform.h"

DeadlyPlatform::DeadlyPlatform(const sf::Vector2f& position, const sf::Vector2f& size, float damage, bool isVisible)
    : Platform(position, size), Killer(damage) 
    {
        setColor(sf::Color::Red);
        if (isVisible == false) {
            turnInvisible();
        }
    }

DeadlyPlatform::DeadlyPlatform(const sf::Vector2f& position, const sf::Vector2f& size, float damage, sf::Texture* texture, const sf::IntRect& textureRect, bool isVisible)
    : Platform(position, size, texture, textureRect), Killer(damage) 
    {
        setColor(sf::Color::Red);
        if (isVisible == false) {
            turnInvisible();
        }
    }

DeadlyPlatform::~DeadlyPlatform() {}

void DeadlyPlatform::turnInvisible() {
    setColor(sf::Color::Transparent);
}

void DeadlyPlatform::turnVisible() {
    setColor(sf::Color::Red);
}