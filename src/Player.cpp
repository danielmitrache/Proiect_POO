#include "../include/Player.h"

Player::Player() {
    m_shape.setSize(sf::Vector2f(50.f, 50.f));
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(sf::Vector2f(0.f, 0.f));
}

Player::Player(float x, float y) {
    m_shape.setSize(sf::Vector2f(50.f, 50.f));
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(sf::Vector2f(x, y));
}

Player::~Player() { }

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}

void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))  
        m_shape.move(sf::Vector2f(-m_f_speed, 0.f));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) 
        m_shape.move(sf::Vector2f(m_f_speed, 0.f));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
        m_shape.move(sf::Vector2f(0.f, -m_f_speed));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        m_shape.move(sf::Vector2f(0.f, m_f_speed));
}