#include "../include/EnemyWalker.h"

EnemyWalker::EnemyWalker(const sf::Vector2f& position, float speed, float damage)
    : Actor(position.x, position.y), Killer(damage) {
    m_f_speed = speed;
    m_v_direction = sf::Vector2f(1.f, 0.f); // Default direction to the right
    m_shape.setFillColor(sf::Color(139, 0, 0)); // Set the color of the enemy walker
    m_shape.setPosition(position); // Set the position of the enemy walker
    m_shape.setSize(sf::Vector2f(50.f, 50.f)); // Set width of the enemy walker
    setWidth(50.f); // Set width of the enemy walker
    setHeight(50.f); // Set height of the enemy walker
}

EnemyWalker::~EnemyWalker() {}

void EnemyWalker::update(float deltaTime) {}

void EnemyWalker::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states); // Draw the enemy walker shape
}