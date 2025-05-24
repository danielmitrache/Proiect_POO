#ifndef UNLOCKLEVELTRIGGER_H
#define UNLOCKLEVELTRIGGER_H

#include <SFML/Graphics.hpp>
#include "triggers.h"

class UnlockLevelTrigger : public Triggers, public sf::Drawable {
private:
    sf::RectangleShape m_shape; // Shape for the trigger
    bool m_b_isActive = false; // State of the trigger
public:
    UnlockLevelTrigger();
    UnlockLevelTrigger(sf::Vector2f position, bool state = false);
    UnlockLevelTrigger(sf::Vector2f position, sf::Vector2f size, bool state = false);
    ~UnlockLevelTrigger();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setTexture(const sf::Texture* texture, const sf::IntRect& rect = sf::IntRect({-1, -1}, {-1, -1}));
    void setTextureRect(const sf::IntRect& rect);
    void setColor(const sf::Color& color);
};

#endif // UNLOCKLEVELTRIGGER_H