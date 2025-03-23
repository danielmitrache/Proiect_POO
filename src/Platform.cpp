#include "../include/Platform.h"

Platform::Platform() {
    m_shape.setSize(sf::Vector2f(0.f, 0.f));
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition(sf::Vector2f(0.f, 0.f));
}

Platform::Platform(sf::Vector2f position) {
    m_shape.setSize(sf::Vector2f(50.f, 50.f));
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition(position);
}

Platform::Platform(sf::Vector2f position, sf::Vector2f size) {
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition(position);
}

Platform::~Platform() { }

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}