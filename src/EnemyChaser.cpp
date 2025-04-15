#include "../include/EnemyChaser.h"

EnemyChaser::EnemyChaser(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, sf::IntRect textureRect, float speed, float damage, float health)
    : Enemy(position, size, texture, textureRect, speed, damage), m_b_isChasingPlayer(false) {}

EnemyChaser::~EnemyChaser() {}


void EnemyChaser::update(sf::Vector2f playerPosition) {
    float directionX = (playerPosition.x - m_shape.getPosition().x) * 0.1f;
    float directionY = (playerPosition.y - m_shape.getPosition().y) * 0.1;
    float distance = std::sqrt(directionX * directionX + directionY * directionY);
    if (distance < 200.f) { // Chasing distance
        m_b_isChasingPlayer = true;
        m_v_direction.x = directionX / distance; // Normalize direction vector
        m_v_direction.y = directionY / distance; // Normalize direction vector

        m_shape.move(m_v_direction * m_f_speed);
        setPosition(m_shape.getPosition());
    } else {
        m_b_isChasingPlayer = false;
    }
}