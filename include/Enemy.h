#ifndef ENEMY_h
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Killer.h"
#include "Actor.h"
#include "ColorHelpers.h"

class Enemy : public Actor, public Killer, public sf::Drawable {
protected:
    float m_f_speed; // Speed of the enemy walker
    sf::Vector2f m_v_direction; // Direction of the enemy walker
    sf::RectangleShape m_shape; // Shape of the enemy walker

    sf::Texture* m_texture; // Texture for the enemy walker

    float m_f_takeDamageTimer;
public:
    Enemy(const sf::Vector2f& position, float speed = 10.f, float damage = 10.f);
    Enemy(const sf::Vector2f& position, const sf::Vector2f& size, float speed = 10.f, float damage = 10.f);
    Enemy(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, float speed = 10.f, float damage = 10.f);
    Enemy(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, const sf::IntRect& textureRect, float speed = 10.f, float damage = 10.f);

    ~Enemy() override;
    
    sf::Vector2f getDirection() const;
    void draw(sf::RenderTarget& targer, sf::RenderStates states) const override;
    void setTexture(sf::Texture* texture, const sf::IntRect& rect = sf::IntRect({-1, -1} , {-1, -1}));
    void setTextureRect(const sf::IntRect& rect);
    void setColor(const sf::Color& color);

    void updateTakeDamageTimer(float deltaTime);
    void setTakeDamageTimer(float duration = 0.1f);
};

#endif // ENEMY_H