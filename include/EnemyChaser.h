#ifndef ENEMYCHASER_H
#define ENEMYCHASER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <cmath>
#include <iostream>

class EnemyChaser : public Enemy {
private:
    bool m_b_isChasingPlayer; // Flag for chasing player
public:
    EnemyChaser(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, sf::IntRect textureRect, float speed, float damage, float health = 100.f);
    ~EnemyChaser() override;

    void update(sf::Vector2f playerPosition); // Update function for enemy chaser
};

#endif // ENEMYCHASER_H