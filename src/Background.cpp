#include "../include/Background.h"
#include <iostream>

Background::Background() : m_sprite(m_texture) {}

Background::Background(const std::string& texturePath): m_sprite(m_texture) {
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading texture: " << texturePath << std::endl;
    }
    m_sprite = sf::Sprite(m_texture);
}
 
Background::~Background() {}

void Background::setTexture(const std::string& texturePath) {
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading texture: " << texturePath << std::endl;
    }
    m_sprite = sf::Sprite(m_texture);
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

void Background::setScale(const sf::Vector2f& size) {
    sf::Vector2u textureSize = m_texture.getSize();
    if (textureSize.x > 0 && textureSize.y > 0) {
        float scaleX = size.x / static_cast<float>(textureSize.x);
        float scaleY = size.y / static_cast<float>(textureSize.y);
        m_sprite.setScale({scaleX, scaleY});
    }
}

void Background::setPosition(const sf::Vector2f& position) {
    m_sprite.setPosition(position);
}

void Background::setPositionToView(const sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    
    // Calculate top-left corner position based on view center and size
    sf::Vector2f topLeft = {viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2};

    m_sprite.setPosition(topLeft);
}

