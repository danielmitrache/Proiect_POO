#include "../include/EnemyChaser.h"

EnemyChaser::EnemyChaser(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, sf::IntRect textureRect, float speed, float damage, float health)
    : Enemy(position, size, texture, textureRect, speed, damage), m_b_isChasingPlayer(false) {}

EnemyChaser::~EnemyChaser() {}


void EnemyChaser::update(sf::Vector2f playerPosition) {
    
}