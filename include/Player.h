#include <SFML/Graphics.hpp>
#include "Actor.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public Actor, public sf::Drawable {
private:
    sf::RectangleShape m_shape;
    float m_f_speed = 7.0f; // Speed of the player
    float m_f_jumpStrength = 50.0f; // Jump strength of the player
    float m_f_verticalSpeed = 0.0f; // Vertical speed of the player
    bool m_b_isJumping = false; // Is the player jumping
public:
    Player();
    Player(sf::Vector2f position);
    ~Player();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();
    void move(sf::Vector2f position);
    virtual void applyGravity() override;
    float getVerticalSpeed();
    void resetVerticalSpeed();
};

#endif // PLAYER_H