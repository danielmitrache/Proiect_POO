#include "../include/EnemyShooter.h"

EnemyShooter::EnemyShooter(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, const sf::IntRect& textureRect, float speed, float damage, float fireRate, float health) 
: Enemy(position, size, texture, textureRect, speed, damage) {
    m_f_fireRate = fireRate;
    m_f_fireRateCounter = 0.0f;
    m_f_health = health;
}

EnemyShooter::~EnemyShooter() {}

void EnemyShooter::turnToPlayer(sf::Vector2f& playerPosition, sf::Texture& leftTexture, sf::Texture& rightTexture) {
    sf::Vector2f direction = playerPosition - m_shape.getPosition();
    if (direction.x < 0) {
        setTexture(&leftTexture, sf::IntRect({0, 0}, {44, 44})); // Set texture to right
    } else {
        setTexture(&rightTexture, sf::IntRect({0, 0}, {44, 44})); // Set texture to left
    }
}