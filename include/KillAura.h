#ifndef KILLAURA_H
#define KILLAURA_H

#include "Actor.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class KillAura : public Actor, public sf::Drawable {
private:
    float m_f_killAuraRadius;
    sf::Color m_color;
    sf::CircleShape m_killAuraShape;
    bool m_b_isActive;

    // Texture for the kill aura
    sf::Texture* m_killAuraTexture;
    sf::IntRect m_killAuraTextureRect; // Texture rectangle for the kill aura

public:
    KillAura(sf::Vector2f position, float radius, sf::Color color);
    KillAura(sf::Vector2f position, float radius, sf::Color color, sf::Texture* texture, sf::IntRect textureRect = {{-1, -1}, {-1, -1}});
    ~KillAura();

    void setRadius(float radius);
    float getRadius() const;

    void setColor(sf::Color color);
    sf::Color getColor() const;

    void setIsActive(bool active);
    bool getIsActive() const;

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // KILLAURA_H