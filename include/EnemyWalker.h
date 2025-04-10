#ifndef ENEMYWALKER_H
#define ENEMYWALKER_H
#include <SFML/Graphics.hpp>
#include "Killer.h"
#include "Actor.h"

class EnemyWalker : public Actor, public Killer, public sf::Drawable {
private:
    float m_f_speed; // Speed of the enemy walker
    sf::Vector2f m_v_direction; // Direction of the enemy walker
    sf::RectangleShape m_shape; // Shape of the enemy walker
public:
    EnemyWalker(const sf::Vector2f& position, float speed = 100.f, float damage = 10.f);
    ~EnemyWalker() override;
    void update(float deltaTime);
    void draw(sf::RenderTarget& targer, sf::RenderStates states) const override;
};

#endif // ENEMYWALKER_H