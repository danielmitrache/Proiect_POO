#include "../include/KillAura.h"

KillAura::KillAura(sf::Vector2f position, float radius, sf::Color color)
    : Actor(position.x, position.y), m_f_killAuraRadius(radius), m_color(color), m_b_isActive(false) {
    setWidth(m_f_killAuraRadius * 2.f);
    setHeight(m_f_killAuraRadius * 2.f);
    m_killAuraShape.setRadius(m_f_killAuraRadius);
    m_killAuraShape.setFillColor(m_color);
    m_killAuraShape.setOrigin({m_f_killAuraRadius, m_f_killAuraRadius});
}

KillAura::KillAura(sf::Vector2f position, float radius, sf::Color color, sf::Texture* texture, sf::IntRect textureRect)
    : Actor(position.x, position.y), m_f_killAuraRadius(radius), m_color(color), m_b_isActive(false) {
    setWidth(m_f_killAuraRadius * 2.f);
    setHeight(m_f_killAuraRadius * 2.f);
    m_killAuraShape.setRadius(m_f_killAuraRadius);
    m_killAuraShape.setFillColor(m_color);
    m_killAuraShape.setOrigin({m_f_killAuraRadius, m_f_killAuraRadius});
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
    m_killAuraShape.setOrigin({m_f_killAuraRadius, m_f_killAuraRadius});
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