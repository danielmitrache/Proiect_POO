#ifndef ENEMYWALKER_H
#define ENEMYWALKER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "Killer.h"
#include "Actor.h"
#include "ColorHelpers.h"

class EnemyWalker : public Enemy {
private:

public:
    EnemyWalker(const sf::Vector2f& position, float speed = 10.f, float damage = 10.f);
    EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, float speed = 10.f, float damage = 10.f);
    EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, float speed = 10.f, float damage = 10.f);
    EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, const sf::IntRect& textureRect, float speed = 10.f, float damage = 10.f);

    ~EnemyWalker() override;

    void walk();
    void reverseDirection();
};

#endif // ENEMYWALKER_H