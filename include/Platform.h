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
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // PLATFORM_H