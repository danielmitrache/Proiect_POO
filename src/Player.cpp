#include "../include/Player.h"

Player::Player() {
    setWidth(50.f);
    setHeight(50.f);
    setX(0.f);
    setY(0.f);
    m_shape.setSize(sf::Vector2f(50.f, 50.f));
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(sf::Vector2f(0.f, 0.f));
}

Player::Player(sf::Vector2f position) {
    setWidth(50.f);
    setHeight(50.f);
    setX(position.x);
    setY(position.y);
    m_shape.setSize(sf::Vector2f(50.f, 50.f));
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(position);
}

Player::~Player() { }

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}

void Player::move(sf::Vector2f position) {
    m_shape.setPosition(position);
    setX(position.x);
    setY(position.y);
}

void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        m_shape.move(sf::Vector2f(-m_f_speed, 0.f));
        setX(m_shape.getPosition().x);
    }  
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) 
    {
        m_shape.move(sf::Vector2f(m_f_speed, 0.f));
        setX(m_shape.getPosition().x);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
    {
        m_shape.move(sf::Vector2f(0.f, -m_f_speed));
        setY(m_shape.getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        m_shape.move(sf::Vector2f(0.f, m_f_speed));
        setY(m_shape.getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) 
    {
        if (!m_b_isJumping) {
            m_f_verticalSpeed = -m_f_jumpStrength;
            m_b_isJumping = true;
        }
    }
}

void Player::applyGravity() {
    if (getHasGravity() || m_b_isJumping) {
        m_f_verticalSpeed += getGravity();
        m_shape.move(sf::Vector2f(0.f, m_f_verticalSpeed));
        setY(m_shape.getPosition().y);
    }
}

void Player::resetVerticalSpeed() {
    m_f_verticalSpeed = 0;
    m_b_isJumping = false;
}

float Player::getVerticalSpeed() {
    return m_f_verticalSpeed;
}