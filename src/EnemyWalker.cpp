#include "../include/EnemyWalker.h"

EnemyWalker::EnemyWalker(const sf::Vector2f& position, float speed, float damage)
    : Enemy(position, speed, damage) {}

EnemyWalker::EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, float speed, float damage)
    : Enemy(position, size, speed, damage) {}

EnemyWalker::EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, float speed, float damage)
    : Enemy(position, size, texture, speed, damage) {}

EnemyWalker::EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, const sf::IntRect& textureRect, float speed, float damage)
    : Enemy(position, size, texture, textureRect, speed, damage) {}

EnemyWalker::~EnemyWalker() {}

void EnemyWalker::walk() {
    sf::Vector2f position = m_shape.getPosition(); // Get the current position of the enemy walker
    position += m_v_direction * m_f_speed;
    m_shape.setPosition(position); // Update the position of the enemy walker
    setPosition(position); // Update the position of the enemy walker in the Actor class
}

void EnemyWalker::reverseDirection() {
    m_v_direction.x = -m_v_direction.x; // Reverse the direction of the enemy walker
}