#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Gravity.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public Actor, public sf::Drawable, public Gravity {
private:
    sf::RectangleShape m_shape;
    float m_f_speed = 7.0f; // Speed of the player

    float m_f_verticalSpeed = 0.0f; // Vertical speed of the player
    float m_f_horizontalSpeed = 0.0f; // Horizontal speed of the player

    float m_f_jumpForce = 30.0f; // Jump force
public:
    Player();
    Player(sf::Vector2f position);
    ~Player();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();
    void move(sf::Vector2f position);

    float getVerticalSpeed();
    void setVerticalSpeed(float verticalSpeed);

    float getHorizontalSpeed();
    void setHorizontalSpeed(float horizontalSpeed);


    /// GRAVITY ///
    void applyGravity() override;
};

#endif // PLAYER_H