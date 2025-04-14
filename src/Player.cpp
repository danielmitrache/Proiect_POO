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
    m_f_attackCooldown = 1.f; // Initialize attack cooldown
    m_b_canAttack = false;
    m_b_isAttacking = false;
}

Player::Player(sf::Vector2f position, sf::Texture* texture) {
    setWidth(50.f);
    setHeight(50.f);
    setX(position.x);
    setY(position.y);
    m_shape.setSize(sf::Vector2f(50.f, 50.f));
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(position);
    m_v2f_lastSpawn = position;
    if (texture){
        m_texture = texture;
        m_shape.setTexture(m_texture);
    }
    m_f_attackCooldown = 1.f; // Initialize attack cooldown
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


    /// ATACK ///
    if (m_f_attackCooldown > 0.f) {
        m_f_attackCooldown -= 1.f / 60.f; // Decrease cooldown
    } else {
        m_b_canAttack = true; // Reset attack ability
    }
    if (m_b_isAttacking)
        m_b_isAttacking = false; // Reset attacking state
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        if (m_b_canAttack) {
            m_b_canAttack = false;
            m_f_attackCooldown = 1.f; // Reset cooldown

            // Attack logic
            m_b_isAttacking = true; // Set attacking state
        }
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

void Player::setHealth(float health) {
    m_f_health = health;
}

float Player::getHealth() const {
    return m_f_health;
}

void Player::setTexture(sf::Texture* texture) {
    m_texture = texture;
    m_shape.setTexture(m_texture);
}

void Player::setColor(sf::Color color) {
    m_shape.setFillColor(color);
}

void Player::setCanAttack(bool canAttack) {
    m_b_canAttack = canAttack;
}

bool Player::getCanAttack() const {
    return m_b_canAttack;
}

void Player::setAttackCooldown(float attackCooldown) {
    m_f_attackCooldown = attackCooldown;
}

float Player::getAttackCooldown() const {
    return m_f_attackCooldown;
}

bool Player::getIsAttacking() const {
    return m_b_isAttacking;
}