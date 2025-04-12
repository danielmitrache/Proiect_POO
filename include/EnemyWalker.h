#ifndef ENEMYWALKER_H
#define ENEMYWALKER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Killer.h"
#include "Actor.h"

class EnemyWalker : public Actor, public Killer, public sf::Drawable {
private:
    float m_f_speed; // Speed of the enemy walker
    sf::Vector2f m_v_direction; // Direction of the enemy walker
    sf::RectangleShape m_shape; // Shape of the enemy walker

    sf::Texture* m_texture; // Texture for the enemy walker
public:
    EnemyWalker(const sf::Vector2f& position, float speed = 10.f, float damage = 10.f);
    EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, float speed = 10.f, float damage = 10.f);
    EnemyWalker(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, float speed = 10.f, float damage = 10.f);
    ~EnemyWalker() override;
    void update();
    void reverseDirection();
    sf::Vector2f getDirection() const;
    void draw(sf::RenderTarget& targer, sf::RenderStates states) const override;
    void setTexture(sf::Texture* texture);
};

#endif // ENEMYWALKER_H