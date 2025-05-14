#include "../include/Bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f size, float speed, sf::Vector2f direction, float damage)
    : Actor(position, size), m_f_speed(speed), m_v_direction(direction), Killer(damage) {
    m_shape.setFillColor(sf::Color::Red); // Set the bullet color to red
    m_shape.setRadius(size.x); // Set the size of the bullet
    m_shape.setPosition(position); // Set the initial position of the bullet
}

Bullet::Bullet(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, const sf::IntRect& textureRect, float speed, sf::Vector2f direction, float damage)
    : Actor(position, size), m_f_speed(speed), m_v_direction(direction), Killer(damage) {
    m_texture = texture; // Set the texture of the bullet
    m_shape.setTexture(m_texture); // Set the texture of the bullet shape
    m_shape.setTextureRect(textureRect); // Set the texture rectangle of the bullet shape
    m_shape.setRadius(size.x); // Set the size of the bullet
    m_shape.setPosition(position); // Set the initial position of the bullet
}

Bullet::~Bullet() {}

void Bullet::move() {
    m_f_lifeTime += 1.f / 60.f; // Increment the lifetime of the bullet
    m_shape.move(m_v_direction * m_f_speed); // Move the bullet shape by the offset
    m_shape.setPosition(m_shape.getPosition() + m_v_direction * m_f_speed); // Update the position of the bullet
    setPosition(m_shape.getPosition()); // Set the position of the bullet actor
}

void Bullet::setDirection(sf::Vector2f direction) {
    m_v_direction = direction; // Set the direction of the bullet
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states); // Draw the bullet shape
}

float Bullet::getLifeTime() const {
    return m_f_lifeTime; // Return the lifetime of the bullet
}

std::ostream& operator<<(std::ostream& os, const Bullet& bullet) {
    os << "Bullet ["
       << "Position: " << bullet.getPosition().x << ", " << bullet.getPosition().y << ", "
       << "Speed: " << bullet.m_f_speed << ", "
       << "Direction: " << bullet.m_v_direction.x << ", " << bullet.m_v_direction.y << ", "
       << "Damage: " << bullet.getDamage() << ", "
       << "LifeTime: " << bullet.m_f_lifeTime
       << "]";
    return os;
}