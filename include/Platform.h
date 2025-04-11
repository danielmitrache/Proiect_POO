#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Actor.h"

class Platform : public Actor, public sf::Drawable {
private:
    sf::RectangleShape m_shape;

    bool m_b_isSticky = false;

    sf::Texture* m_texture; // Texture for the platform
public:
    Platform();
    Platform(sf::Vector2f position);
    Platform(sf::Vector2f position, sf::Vector2f size);
    Platform(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, const sf::IntRect& textureRect);
    Platform(sf::Vector2f position, sf::Vector2f size, bool isSticky);
    Platform(sf::Vector2f position, sf::Vector2f size, bool isSticky, sf::Texture* texture, const sf::IntRect& textureRect);
    ~Platform();

    // Draw the platform
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setColor(const sf::Color& color);
    sf::Color getColor() const;

    virtual bool isDeadly() const;

    bool isSticky() const;
    void setSticky(bool isSticky);

    // Set the texture for the platform
    void setTexture(sf::Texture* texture, const sf::IntRect& textureRect);
};

#endif // PLATFORM_H