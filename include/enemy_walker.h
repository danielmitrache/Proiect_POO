#ifndef ENEMYWALKER_H
#define ENEMYWALKER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"
#include "killer.h"
#include "actor.h"
#include "color_helpers.h"

class EnemyWalker : public Enemy {
private:
    float m_f_bounceForce = 1.2f;
public:
    EnemyWalker(const sf::Vector2f& position, float speed = 10.f, float damage = 10.f, float bounceForce = 1.2f);
    EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, float speed = 10.f, float damage = 10.f, float bounceForce = 1.2f);
    EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, float speed = 10.f, float damage = 10.f, float bounceForce = 1.2f);
    EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, const sf::IntRect& textureRect, float speed = 10.f, float damage = 10.f, float bounceForce = 1.2f);

    ~EnemyWalker() override;

    void walk();
    void reverseDirection();

    void setBounceForce(float bounceForce);
    float getBounceForce() const;
};

#endif // ENEMYWALKER_H