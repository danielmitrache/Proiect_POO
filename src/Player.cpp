#include "../include/Player.h"

Player::Player() {
    setWidth(50.f);
    setHeight(50.f);
    setX(0.f);
    setY(0.f);
    m_shape.setSize(sf::Vector2f(50.f, 50.f));
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(sf::Vector2f(0.f, 0.f));
    m_v2f_lastSpawn = sf::Vector2f(0.f, 0.f);
}

Player::Player(sf::Vector2f position) {
    setWidth(50.f);
    setHeight(50.f);
    setX(position.x);
    setY(position.y);
    m_shape.setSize(sf::Vector2f(50.f, 50.f));
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(position);
    m_v2f_lastSpawn = position;
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
    m_f_horizontalSpeed = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
        if (m_playerMode == PlayerMode::Platformer) {
            m_playerMode = PlayerMode::WASD;
        } else {
            m_playerMode = PlayerMode::Platformer;
        }
    }
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && m_playerMode == PlayerMode::WASD) 
    {
        m_shape.move(sf::Vector2f(0.f, -m_f_speed));
        m_f_verticalSpeed = -m_f_speed;
        setY(m_shape.getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && m_playerMode == PlayerMode::WASD)
    {
        m_shape.move(sf::Vector2f(0.f, m_f_speed));
        m_f_verticalSpeed = m_f_speed;
        setY(m_shape.getPosition().y);
    }


    /// GRAVITY AND JUMPING ///
    if (m_playerMode == PlayerMode::Platformer) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) 
        {
            _jump();
        }
        _applyGravity();
    
        m_shape.move(sf::Vector2f(0.f, m_f_verticalSpeed));
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

void Player::_applyGravity() {
    if (m_b_hasGravity && m_playerMode == PlayerMode::Platformer) {
        m_f_verticalSpeed += m_f_gravity;
    }
}

void Player::_jump() {
    if (m_b_canJump && m_playerMode == PlayerMode::Platformer) {
        m_b_canJump = false;
        m_f_verticalSpeed = -m_f_jumpForce;
    }
}

bool Player::getCanJump() const {
    return m_b_canJump;
}

void Player::setCanJump(bool canJump) {
    m_b_canJump = canJump;
}

void Player::setMode(PlayerMode mode) {
    m_playerMode = mode;
}

PlayerMode Player::getMode() const {
    return m_playerMode;
}

sf::Vector2f Player::getLastSpawn() const {
    return m_v2f_lastSpawn;
}

void Player::setLastSpawn(sf::Vector2f lastSpawn) {
    m_v2f_lastSpawn = lastSpawn;
}