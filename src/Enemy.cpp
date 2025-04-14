#include "../include/Enemy.h"

Enemy::Enemy(const sf::Vector2f& position, float speed, float damage)
    : Actor(position.x, position.y), Killer(damage) {
    m_f_speed = speed;
    m_v_direction = sf::Vector2f(1.f, 0.f); // Default direction to the right
    m_shape.setFillColor(sf::Color(139, 0, 0)); // Set the color of the enemy walker
    m_shape.setPosition(position); // Set the position of the enemy walker
    m_shape.setSize(sf::Vector2f(50.f, 50.f)); // Set width of the enemy walker
    setWidth(50.f); // Set width of the enemy walker
    setHeight(50.f); // Set height of the enemy walker
}

Enemy::Enemy(const sf::Vector2f& position, const sf::Vector2f& size, float speed, float damage)
    : Actor(position.x, position.y), Killer(damage) {
    m_f_speed = speed;
    m_v_direction = sf::Vector2f(1.f, 0.f); // Default direction to the right
    m_shape.setFillColor(sf::Color(139, 0, 0)); // Set the color of the enemy walker
    m_shape.setPosition(position); // Set the position of the enemy walker
    m_shape.setSize(size); // Set size of the enemy walker
    setWidth(size.x); // Set width of the enemy walker
    setHeight(size.y); // Set height of the enemy walker
}

Enemy::Enemy(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, float speed, float damage)
    : Actor(position.x, position.y), Killer(damage) {
    m_f_speed = speed;
    m_v_direction = sf::Vector2f(1.f, 0.f); // Default direction to the right
    m_shape.setFillColor(sf::Color::White); // Set the color of the enemy walker
    m_shape.setPosition(position); // Set the position of the enemy walker
    m_shape.setSize(size); // Set size of the enemy walker
    setWidth(size.x); // Set width of the enemy walker
    setHeight(size.y); // Set height of the enemy walker
    

    if ( texture ) {
        m_texture = texture;
        m_shape.setTexture(m_texture); // Set the texture of the enemy walker
    }
}

Enemy::Enemy(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, const sf::IntRect& rect, float speed, float damage)
    : Actor(position.x, position.y), Killer(damage) {
    m_f_speed = speed;
    m_v_direction = sf::Vector2f(1.f, 0.f); // Default direction to the right
    m_shape.setFillColor(sf::Color::White); // Set the color of the enemy walker
    m_shape.setPosition(position); // Set the position of the enemy walker
    m_shape.setSize(size); // Set size of the enemy walker
    setWidth(size.x); // Set width of the enemy walker
    setHeight(size.y); // Set height of the enemy walker

    if (texture) {
        m_texture = texture;
        m_shape.setTexture(m_texture); // Set the texture of the enemy walker
        m_shape.setTextureRect(rect); // Set the texture rectangle of the enemy walker shape
    }
}

Enemy::~Enemy() {}


void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states); // Draw the enemy walker shape
}

void Enemy::setTexture(sf::Texture* texture, const sf::IntRect& rect) {
    m_texture = texture; // Set the texture of the enemy walker
    m_shape.setTexture(m_texture); // Set the texture of the enemy walker shape
    if (rect != sf::IntRect({-1, -1}, {-1, -1})) {
        m_shape.setTextureRect(rect); // Set the texture rectangle of the enemy walker shape
    }
}

void Enemy::setTextureRect(const sf::IntRect& rect) {
    m_shape.setTextureRect(rect); // Set the texture rectangle of the enemy walker shape
}
void Enemy::setColor(const sf::Color& color) {
    m_shape.setFillColor(color); // Set the color of the enemy walker shape
}

void Enemy::updateTakeDamageTimer(float deltaTime) {
    if (m_f_takeDamageTimer > 0.f) {
        m_f_takeDamageTimer -= deltaTime; // Decrease the take damage timer
        if (m_f_takeDamageTimer <= 0.f) {
            m_shape.setFillColor(sf::Color::White); // Reset the color of the enemy walker shape
        }
    }
}

void Enemy::setTakeDamageTimer(float duration) {
    m_f_takeDamageTimer = duration; // Set the take damage timer to 0.5 seconds
    m_shape.setFillColor(ColorHelpers::blendColors(sf::Color::White, sf::Color::Red, 0.3f)); // Set the color of the enemy walker shape to red
}

void Enemy::setSpeed(float speed) {
    m_f_speed = speed; // Set the speed of the enemy walker
}

float Enemy::getSpeed() const {
    return m_f_speed; // Return the speed of the enemy walker
}

void Enemy::setDirection( sf::Vector2f& direction) {
    m_v_direction = direction; // Set the direction of the enemy walker
}

sf::Vector2f Enemy::getDirection() const {
    return m_v_direction; // Return the direction of the enemy walker
}

void Enemy::setSize( sf::Vector2f& size) {
    m_shape.setSize(size); // Set the size of the enemy walker shape
    setWidth(size.x); // Set width of the enemy walker
    setHeight(size.y); // Set height of the enemy walker
}

sf::Vector2f Enemy::getSize() const {
    return m_shape.getSize(); // Return the size of the enemy walker shape
}