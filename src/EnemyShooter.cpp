#include "../include/EnemyShooter.h"

EnemyShooter::EnemyShooter(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, const sf::IntRect& textureRect, float speed, float damage, float fireRate, float health) 
: Enemy(position, size, texture, textureRect, speed, damage) {
    m_f_fireRate = fireRate;
    m_f_fireRateCounter = 0.0f;
    m_f_health = health;
}

EnemyShooter::~EnemyShooter() {}

void EnemyShooter::turnToPlayer(sf::Vector2f& playerPosition, sf::Texture& leftTexture, sf::Texture& rightTexture) {
    sf::Vector2f direction = playerPosition - m_shape.getPosition();
    if (direction.x < 0) {
        setTexture(&leftTexture, sf::IntRect({0, 0}, {44, 44})); // Set texture to right
    } else {
        setTexture(&rightTexture, sf::IntRect({0, 0}, {44, 44})); // Set texture to left
    }
}

void EnemyShooter::shootToPlayer(sf::Vector2f& playerPosition, float bulletSpeed, float bulletDamage) {
    // Calculate the direction to the player
    sf::Vector2f direction = playerPosition - m_shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction /= length; // Normalize the direction vector
    }

    std::cout << "Shooting!" << std::endl;
    std::cout << "----" << std::endl;
    
    // Create a new bullet and set its properties
    Bullet bullet(m_shape.getPosition() + sf::Vector2f(10.f, 20.f), {10.f, 10.f}, bulletSpeed, direction, bulletDamage);
    m_bullets.push_back(bullet); // Add the bullet to the vector
}

void EnemyShooter::update(sf::Vector2f &playerPosition) {
    m_f_fireRateCounter += 1.f / 60.f; // Increment the fire rate counter
    if (m_f_fireRateCounter >= m_f_fireRate) {
        shootToPlayer(playerPosition, 10.f, m_f_damage); // Shoot a bullet towards the player
        m_f_fireRateCounter = 0.0f; // Reset the fire rate counter
    }

    for (auto& bullet : m_bullets) {
        bullet.move(); // Move the bullet
    }

    for (size_t i = 0; i < m_bullets.size(); ++ i) {
        if (m_bullets[i].getLifeTime() > 5.f) {
            m_bullets.erase(m_bullets.begin() + i); // Remove the bullet if it exceeds its lifetime
            --i; // Adjust the index after erasing
        }
    }
}