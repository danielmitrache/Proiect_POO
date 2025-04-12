#include "../include/RedOverlay.h"

RedOverlay::RedOverlay() {
    m_redOverlay.setSize(sf::Vector2f(2000.f, 2000.f)); // Set the size of the overlay to match the window size
    m_redOverlay.setFillColor(sf::Color(255, 0, 0, 0)); // Start with a fully transparent red color
    m_redOverlay.setPosition({0.f, 0.f}); // Set the initial position of the overlay
}

RedOverlay::~RedOverlay() {}

void RedOverlay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_redOverlay, states); // Draw the overlay
}

void RedOverlay::setPosition(sf::Vector2f position) {
    m_redOverlay.setPosition(position); // Set the position of the overlay
}

void RedOverlay::setAlpha(float alpha) {
    m_redOverlay.setFillColor(sf::Color(255, 0, 0, alpha)); // Set the alpha value for the overlay
}

float RedOverlay::getAlpha() const {
    return m_redOverlay.getFillColor().a; // Get the current alpha value of the overlay
}