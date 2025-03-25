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
    m_f_verticalSpeed = 0.0f;
    m_f_horizontalSpeed = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        m_shape.move(sf::Vector2f(-m_f_speed, 0.f));
        m_f_horizontalSpeed = -m_f_speed;
        setX(m_shape.getPosition().x);
    }  
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) 
    {
        m_shape.move(sf::Vector2f(m_f_speed, 0.f));
        m_f_horizontalSpeed = m_f_speed;
        setX(m_shape.getPosition().x);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
    {
        m_shape.move(sf::Vector2f(0.f, -m_f_speed));
        m_f_verticalSpeed = -m_f_speed;
        setY(m_shape.getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        m_shape.move(sf::Vector2f(0.f, m_f_speed));
        m_f_verticalSpeed = m_f_speed;
        setY(m_shape.getPosition().y);
    }
}

float Player::getVerticalSpeed() {
    return m_f_verticalSpeed;
}

void Player::setVerticalSpeed(float verticalSpeed) {
    m_f_verticalSpeed = verticalSpeed;
}

float Player::getHorizontalSpeed() {
    return m_f_horizontalSpeed;
}

void Player::setHorizontalSpeed(float horizontalSpeed) {
    m_f_horizontalSpeed = horizontalSpeed;
}

void Player::applyGravity() {
    if (m_b_hasGravity) {
        m_shape.move(sf::Vector2f(0.f, m_f_gravity));
        setY(m_shape.getPosition().y);
    }
}