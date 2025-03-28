#include "../include/NextLevelTrigger.h"

NextLevelTrigger::NextLevelTrigger() : Triggers() {
    m_i_nextLevelID = 0; // Initialize the next level ID to 0
    m_shape.setRadius(10.f); // Set the radius of the trigger area
    m_shape.setFillColor(sf::Color::Blue); // Set the color of the trigger area
    m_shape.setPosition({0.f, 0.f}); // Set the position of the trigger area
    setWidth(20.f); // Set the width of the trigger area
    setHeight(20.f); // Set the height of the trigger area
}

NextLevelTrigger::NextLevelTrigger(sf::Vector2f position, int nextLevel) : Triggers(position), m_i_nextLevelID(nextLevel) {
    m_shape.setRadius(10.f); // Set the radius of the trigger area
    m_shape.setFillColor(sf::Color::Blue); // Set the color of the trigger area
    m_shape.setPosition(position); // Set the position of the trigger area
    setWidth(20.f); // Set the width of the trigger area
    setHeight(20.f); // Set the height of the trigger area
}

NextLevelTrigger::~NextLevelTrigger() { }

void NextLevelTrigger::setNextLevelID(const int nextLevelID) {
    m_i_nextLevelID = nextLevelID;
}

const int NextLevelTrigger::getNextLevelID() const {
    return m_i_nextLevelID;
}

void NextLevelTrigger::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states); // Draw the trigger area
}

void NextLevelTrigger::move(const sf::Vector2f position) {
    m_shape.setPosition(position); // Move the trigger area to the new position
    setPosition(position); // Update the position of the trigger
}

std::string NextLevelTrigger::getNextLevelPath(std::string BASE_PATH) const {
    return BASE_PATH + "level" + std::to_string(m_i_nextLevelID) + ".txt"; // Build the next level path
}