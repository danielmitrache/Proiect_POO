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
public:
    std::vector<Bullet> m_bullets; // Vector of bullets
public:
    EnemyShooter(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, const sf::IntRect& textureRect, float speed, float damage, float fireRate, float health = 100.f);

    ~EnemyShooter() override;

    void turnToPlayer(sf::Vector2f& playerPosition, sf::Texture& leftTexture, sf::Texture& rightTexture);

    void shootToPlayer(sf::Vector2f& playerPosition, float bulletSpeed, float bulletDamage);

    void update(sf::Vector2f& playerPosition);
};

#endif // ENEMYSHOOTER_H