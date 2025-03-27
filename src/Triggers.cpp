#include "../include/Triggers.h"

Triggers::Triggers() : Actor() {
    m_b_isActive = false;
}
Triggers::Triggers(sf::Vector2f position) : Actor(position.x , position.y) {
    m_b_isActive = false;
}
Triggers::Triggers(sf::Vector2f position, bool state) : Actor(position.x , position.y) {
    m_b_isActive = state;
}
Triggers::~Triggers() {}

void Triggers::setIsActive(bool isActive) {
    m_b_isActive = isActive;
}

bool Triggers::isActive() const {
    return m_b_isActive;
}

void Triggers::switchState() {
    m_b_isActive = !m_b_isActive;
}