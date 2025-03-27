#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Platform : public Actor, public sf::Drawable {
private:
    sf::RectangleShape m_shape;
public:
    Platform();
    Platform(sf::Vector2f position);
    Platform(sf::Vector2f position, sf::Vector2f size);
    ~Platform();

    // Draw the platform
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setColor(const sf::Color& color);
    sf::Color getColor() const;

    virtual bool isDeadly() const;
};

#endif // PLATFORM_H