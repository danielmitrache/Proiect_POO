#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable {
private:
    sf::Texture m_texture;  // Texture for the background
    sf::Sprite m_sprite;    // Sprite for the background

public:
    Background(); // Default constructor
    ~Background(); // Destructor
    Background(const std::string& texturePath); // Constructor with texture path

    void setTexture(const std::string& texturePath);

    void setScale(const sf::Vector2f& size);

    void setPosition(const sf::Vector2f& position);

    void setPositionToView(const sf::View& view);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // BACKGROUND_H
