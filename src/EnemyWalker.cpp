#include "../include/EnemyWalker.h"

EnemyWalker::EnemyWalker(const sf::Vector2f& position, float speed, float damage, float bounceForce)
    : Enemy(position, speed, damage), m_f_bounceForce(bounceForce) {}

EnemyWalker::EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, float speed, float damage, float bounceForce)
    : Enemy(position, size, speed, damage), m_f_bounceForce(bounceForce) {}

EnemyWalker::EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, float speed, float damage, float bounceForce)
    : Enemy(position, size, texture, speed, damage), m_f_bounceForce(bounceForce) {}

EnemyWalker::EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, const sf::IntRect& textureRect, float speed, float damage, float bounceForce)
    : Enemy(position, size, texture, textureRect, speed, damage), m_f_bounceForce(bounceForce) {}

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

void EnemyWalker::setBounceForce(float bounceForce) {
    m_f_bounceForce = bounceForce; // Set the bounce force of the enemy walker
}

float EnemyWalker::getBounceForce() const {
    return m_f_bounceForce; // Get the bounce force of the enemy walker
}