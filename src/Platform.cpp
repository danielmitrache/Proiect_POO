#include "../include/Platform.h"

Platform::Platform() {
    setWidth(0.f);
    setHeight(0.f);
    setX(0.f);
    setY(0.f);
    m_shape.setSize(sf::Vector2f(0.f, 0.f));
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition(sf::Vector2f(0.f, 0.f));
}

Platform::Platform(sf::Vector2f position) {
    setWidth(50.f);
    setHeight(50.f);
    setX(position.x);
    setY(position.y);
    m_shape.setSize(sf::Vector2f(50.f, 50.f));
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition(position);
}

Platform::Platform(sf::Vector2f position, sf::Vector2f size) {
    setWidth(size.x);
    setHeight(size.y);
    setX(position.x);
    setY(position.y);
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition(position);
}

Platform::~Platform() { }

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}

void Platform::setColor(const sf::Color& color) {
    m_shape.setFillColor(color);
}

sf::Color Platform::getColor() const {
    return m_shape.getFillColor();
}

bool Platform::isDeadly() const {
    return false;
}