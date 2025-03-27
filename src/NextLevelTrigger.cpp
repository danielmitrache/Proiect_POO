#include "../include/NextLevelTrigger.h"

NextLevelTrigger::NextLevelTrigger() : Triggers() {
    m_shape.setRadius(30.f); // Set the radius of the trigger area
    m_shape.setFillColor(sf::Color::Blue); // Set the color of the trigger area
}

NextLevelTrigger::NextLevelTrigger(sf::Vector2f position, std::string nextLevelPath) : Triggers(position), m_s_nextLevelPath(nextLevelPath) {
    m_shape.setRadius(30.f); // Set the radius of the trigger area
    m_shape.setFillColor(sf::Color::Blue); // Set the color of the trigger area
    m_shape.setPosition(position); // Set the position of the trigger area
}

NextLevelTrigger::~NextLevelTrigger() { }

void NextLevelTrigger::setNextLevelPath(const std::string& nextLevelPath) {
    m_s_nextLevelPath = nextLevelPath;
}

const std::string& NextLevelTrigger::getNextLevelPath() const {
    return m_s_nextLevelPath;
}

void NextLevelTrigger::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states); // Draw the trigger area
}