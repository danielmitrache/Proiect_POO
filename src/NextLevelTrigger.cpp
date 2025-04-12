#include "../include/NextLevelTrigger.h"

NextLevelTrigger::NextLevelTrigger() : Triggers() {
    m_i_nextLevelID = 0; // Initialize the next level ID to 0
    m_shape.setSize({64.f, 64.f}); 
    m_shape.setFillColor(sf::Color::Blue); // Set the color of the trigger area
    m_shape.setPosition({0.f, 0.f}); // Set the position of the trigger area
    setWidth(64.f); // Set the width of the trigger area
    setHeight(64.f); // Set the height of the trigger area
}

NextLevelTrigger::NextLevelTrigger(sf::Vector2f position, int nextLevel) : Triggers(position), m_i_nextLevelID(nextLevel) {
    m_shape.setSize({64.f, 64.f}); 
    m_shape.setFillColor(sf::Color::Blue); // Set the color of the trigger area
    m_shape.setPosition(position); // Set the position of the trigger area
    setWidth(64.f); // Set the width of the trigger area
    setHeight(64.f); // Set the height of the trigger area
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

void NextLevelTrigger::setTexture(const sf::Texture* texture, const sf::IntRect& textureRect) {
    if (textureRect != sf::IntRect({-1, -1}, {-1, -1})) {
        m_shape.setTextureRect(textureRect); // Set the texture rectangle for the trigger area
    }
    m_shape.setTexture(texture); // Set the texture for the trigger area
}

void NextLevelTrigger::setTextureRect(const sf::IntRect& textureRect) {
    m_shape.setTextureRect(textureRect); // Set the texture rectangle for the trigger area
}

void NextLevelTrigger::setColor(const sf::Color& color) {
    m_shape.setFillColor(color); // Set the color of the trigger area
}