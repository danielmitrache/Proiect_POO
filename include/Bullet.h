#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Colisions.h"
#include "Killer.h"

class Bullet : public Actor, public Killer, public sf::Drawable {
private:
    // Bullet properties
    float m_f_speed; // Speed of the bullet
    sf::Vector2f m_v_direction; // Direction of the bullet
    float m_f_lifeTime;

    // Bullet texture
    sf::CircleShape m_shape; // Shape of the bullet
    sf::Texture* m_texture; // Texture of the bullet
public:
    Bullet(sf::Vector2f position, sf::Vector2f size, float speed, sf::Vector2f direction, float damage = 10.f);
    Bullet(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, const sf::IntRect& textureRect, float speed, sf::Vector2f direction, float damage = 10.f);   

    ~Bullet();

    void move();
    void setDirection(sf::Vector2f direction);

    // Override the draw function to draw the bullet
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float getLifeTime() const;

    friend std::ostream& operator<<(std::ostream& os, const Bullet& bullet);
};

#endif