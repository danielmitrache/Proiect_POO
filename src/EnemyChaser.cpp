#include "../include/EnemyChaser.h"

EnemyChaser::EnemyChaser(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, sf::IntRect textureRect, float speed, float damage, float health)
    : Enemy(position, size, texture, textureRect, speed, damage), m_b_isChasingPlayer(false) {}

EnemyChaser::~EnemyChaser() {}


void EnemyChaser::update(sf::Vector2f playerPosition) {
    float directionX = (playerPosition.x - m_shape.getPosition().x);
    float directionY = (playerPosition.y - m_shape.getPosition().y);
    float distance = std::sqrt(directionX * directionX + directionY * directionY);
    if (distance < 500.f) { // Chasing distance
        m_b_isChasingPlayer = true;
        //directionX = 0.1f * directionX; // Adjust speed factor as needed
        //directionY = 0.1f * directionY; // Adjust speed factor as needed
        m_v_direction.x = directionX / distance; // Normalize direction vector
        m_v_direction.y = directionY / distance; // Normalize direction vector

        m_shape.move(m_v_direction * m_f_speed);
        setPosition(m_shape.getPosition());
    } else {
        m_b_isChasingPlayer = false;
    }
}