#ifndef REDOVERLAY_H
#define REDOVERLAY_H

#include <SFML/Graphics.hpp>

class RedOverlay : public sf::Drawable {
private:
    sf::RectangleShape m_redOverlay;
public:
    RedOverlay();
    ~RedOverlay();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(sf::Vector2f position);
    void setColor(sf::Color color);
    sf::Color getColor() const;

    void setAlpha(float alpha);
    float getAlpha() const;
};  

#endif // REDOVERLAY_H