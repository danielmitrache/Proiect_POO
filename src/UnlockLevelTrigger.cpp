#include "../include/UnlockLevelTrigger.h"

UnlockLevelTrigger::UnlockLevelTrigger() : Triggers() {
    m_shape.setFillColor(sf::Color(255, 0, 255, 255));
    m_shape.setPosition({0.f, 0.f});
}

UnlockLevelTrigger::UnlockLevelTrigger(sf::Vector2f position, bool state) : Triggers(position, state) {
    m_shape.setFillColor(sf::Color(255, 0, 255, 255));
    m_shape.setPosition(position);
}

UnlockLevelTrigger::~UnlockLevelTrigger() {}

void UnlockLevelTrigger::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}