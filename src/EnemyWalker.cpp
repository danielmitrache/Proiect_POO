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

void EnemyWalker::update() {
    sf::Vector2f position = m_shape.getPosition(); // Get the current position of the enemy walker
    position += m_v_direction * m_f_speed;
    m_shape.setPosition(position); // Update the position of the enemy walker
    setPosition(position); // Update the position of the enemy walker in the Actor class
}

void EnemyWalker::reverseDirection() {
    m_v_direction.x = -m_v_direction.x; // Reverse the direction of the enemy walker
}

void EnemyWalker::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states); // Draw the enemy walker shape
}