#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

#include "Enemy.h"
#include "Bullet.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <vector>


class EnemyShooter : public Enemy {
private:
    float m_f_fireRate;
    float m_f_fireRateCounter;
    float m_f_health;
    float m_f_damage;
    std::vector<Bullet> m_bullets; // Vector of bullets
public:
    EnemyShooter(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, const sf::IntRect& textureRect, float speed, float damage, float fireRate, float health = 100.f);

    ~EnemyShooter() override;

    void turnToPlayer(sf::Vector2f& playerPosition, sf::Texture& leftTexture, sf::Texture& rightTexture);

    void shootToPlayer(sf::Vector2f& playerPosition, float bulletSpeed, float bulletDamage);

    void update(sf::Vector2f& playerPosition);

    std::vector<Bullet> getBullets() const { return m_bullets; }
    void setBullets(const std::vector<Bullet>& bullets) { m_bullets = bullets; }
    void removeBullet(size_t index) {
        if (index < m_bullets.size()) {
            m_bullets.erase(m_bullets.begin() + index); // Remove the bullet from the vector
        }
    }
};

#endif // ENEMYSHOOTER_H