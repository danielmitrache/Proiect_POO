#include "../include/kill_Aura.h"

KillAura::KillAura(sf::Vector2f position, float radius, sf::Color color)
    : Actor(position.x, position.y), m_f_killAuraRadius(radius), m_color(color), m_b_isActive(false), m_f_animationDuration(-.5f) {
    setWidth(m_f_killAuraRadius * 2.f);
    setHeight(m_f_killAuraRadius * 2.f);
    m_killAuraShape.setRadius(m_f_killAuraRadius);
    m_killAuraShape.setFillColor(m_color);
}

KillAura::KillAura(sf::Vector2f position, float radius, sf::Color color, sf::Texture* texture, sf::IntRect textureRect)
    : Actor(position.x, position.y), m_f_killAuraRadius(radius), m_color(color), m_b_isActive(false), m_f_animationDuration(0.5f) {
    setWidth(m_f_killAuraRadius * 2.f);
    setHeight(m_f_killAuraRadius * 2.f);
    m_killAuraShape.setRadius(m_f_killAuraRadius);
    m_killAuraShape.setFillColor(m_color);
    m_killAuraShape.setTexture(texture);
    m_killAuraTexture = texture;
    if (m_killAuraTextureRect != sf::IntRect({-1, -1}, {-1, -1})) {
        m_killAuraTextureRect = textureRect;
        m_killAuraShape.setTextureRect(m_killAuraTextureRect);
    }
}

KillAura::~KillAura() {}

void KillAura::setRadius(float radius) {
    m_f_killAuraRadius = radius;
    m_killAuraShape.setRadius(m_f_killAuraRadius);
    setWidth(m_f_killAuraRadius * 2.f);
    setHeight(m_f_killAuraRadius * 2.f);
}

float KillAura::getRadius() const {
    return m_f_killAuraRadius;
}

void KillAura::setColor(sf::Color color) {
    m_color = color;
    m_killAuraShape.setFillColor(m_color);
}

sf::Color KillAura::getColor() const {
    return m_color;
}

void KillAura::setIsActive(bool active) {
    m_b_isActive = active;
}

bool KillAura::getIsActive() const {
    return m_b_isActive;
}

void KillAura::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_killAuraShape, states);
}

void KillAura::setPosition(sf::Vector2f position) {
    m_killAuraShape.setPosition(position);
    Actor::setPosition(position);
}

sf::Vector2f KillAura::getPosition() const {
    return m_killAuraShape.getPosition();
}

void KillAura::update(float deltaTime, sf::Vector2f playerPosition) {
    if (!m_b_isActive) return;

    // Update the animation timer
    m_f_animationTimer += deltaTime;

    // Calculate the scale factor using a sine wave
    float progress = m_f_animationTimer / m_f_animationDuration;
    float scaleFactor = std::sin(progress * M_PI); // Smoothly grow and shrink

    // Update the radius based on the scale factor
    float newRadius = m_f_killAuraRadius * scaleFactor;
    m_killAuraShape.setRadius(newRadius);
    setWidth(newRadius * 2.f);
    setHeight(newRadius * 2.f);

    // Update the color based on the animation progress
    float alpha = 255 * (1 - progress); // Fade out the color
    m_color.a = static_cast<uint8_t>(alpha);
    m_killAuraShape.setFillColor(m_color);

    // Deactivate the kill aura when the animation is complete
    if (m_f_animationTimer >= m_f_animationDuration) {
        m_f_animationTimer = 0.f; // Reset the animation timer
        m_b_isActive = false;
    }
}
