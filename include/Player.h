#include <SFML/Graphics.hpp>
#include "Actor.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public Actor, public sf::Drawable {
private:
    sf::RectangleShape m_shape;
    float m_f_speed = 2.0f;
public:
    Player();
    Player(float x, float y);
    ~Player();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();
};

#endif // PLAYER_H