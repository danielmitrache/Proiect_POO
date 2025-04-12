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

EnemyWalker::EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, float speed, float damage)
    : Actor(position.x, position.y), Killer(damage) {
    m_f_speed = speed;
    m_v_direction = sf::Vector2f(1.f, 0.f); // Default direction to the right
    m_shape.setFillColor(sf::Color(139, 0, 0)); // Set the color of the enemy walker
    m_shape.setPosition(position); // Set the position of the enemy walker
    m_shape.setSize(size); // Set size of the enemy walker
    setWidth(size.x); // Set width of the enemy walker
    setHeight(size.y); // Set height of the enemy walker
}

EnemyWalker::EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, float speed, float damage)
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

EnemyWalker::EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, const sf::IntRect& rect, float speed, float damage)
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

sf::Vector2f EnemyWalker::getDirection() const {
    return m_v_direction; // Return the direction of the enemy walker
}

void EnemyWalker::setTexture(sf::Texture* texture, const sf::IntRect& rect) {
    m_texture = texture; // Set the texture of the enemy walker
    m_shape.setTexture(m_texture); // Set the texture of the enemy walker shape
    if (rect != sf::IntRect({-1, -1}, {-1, -1})) {
        m_shape.setTextureRect(rect); // Set the texture rectangle of the enemy walker shape
    }
}

void EnemyWalker::setTextureRect(const sf::IntRect& rect) {
    m_shape.setTextureRect(rect); // Set the texture rectangle of the enemy walker shape
}
void EnemyWalker::setColor(const sf::Color& color) {
    m_shape.setFillColor(color); // Set the color of the enemy walker shape
}

void EnemyWalker::updateTakeDamageTimer(float deltaTime) {
    if (m_f_takeDamageTimer > 0.f) {
        m_f_takeDamageTimer -= deltaTime; // Decrease the take damage timer
        if (m_f_takeDamageTimer <= 0.f) {
            m_shape.setFillColor(sf::Color::White); // Reset the color of the enemy walker shape
        }
    }
}

void EnemyWalker::setTakeDamageTimer(float duration) {
    m_f_takeDamageTimer = duration; // Set the take damage timer to 0.5 seconds
    m_shape.setFillColor(ColorHelpers::blendColors(sf::Color::White, sf::Color::Red, 0.3f)); // Set the color of the enemy walker shape to red
}