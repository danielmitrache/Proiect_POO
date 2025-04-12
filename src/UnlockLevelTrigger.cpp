#include "../include/UnlockLevelTrigger.h"

UnlockLevelTrigger::UnlockLevelTrigger() : Triggers() {
    m_shape.setFillColor(sf::Color(255, 165, 0, 255));
    m_shape.setSize({64.f, 64.f});
    m_shape.setPosition({0.f, 0.f});
    setWidth(64.f);
    setHeight(64.f);
}

UnlockLevelTrigger::UnlockLevelTrigger(sf::Vector2f position, bool state) : Triggers(position, state) {
    m_shape.setFillColor(sf::Color(255, 165, 0, 255));
    m_shape.setSize({64.f, 64.f});
    m_shape.setPosition(position);
    setWidth(64.f);
    setHeight(64.f);
}

UnlockLevelTrigger::UnlockLevelTrigger(sf::Vector2f position, sf::Vector2f size, bool state) : Triggers(position, state) {
    m_shape.setFillColor(sf::Color(255, 165, 0, 255));
    m_shape.setSize(size);
    m_shape.setPosition(position);
    setWidth(size.x);
    setHeight(size.y);
}

UnlockLevelTrigger::~UnlockLevelTrigger() {}

void UnlockLevelTrigger::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}

void UnlockLevelTrigger::setTexture(const sf::Texture* texture, const sf::IntRect& rect) {
    m_shape.setTexture(texture);
    if (rect != sf::IntRect({-1, -1}, {-1, -1})) {
        m_shape.setTextureRect(rect);
    }
}

void UnlockLevelTrigger::setTextureRect(const sf::IntRect& rect) {
    m_shape.setTextureRect(rect);
}

void UnlockLevelTrigger::setColor(const sf::Color& color) {
    m_shape.setFillColor(color);
}   