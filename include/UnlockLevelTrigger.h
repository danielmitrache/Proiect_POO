#ifndef UNLOCKLEVELTRIGGER_H
#define UNLOCKLEVELTRIGGER_H

#include <SFML/Graphics.hpp>
#include "Triggers.h"

class UnlockLevelTrigger : public Triggers, public sf::Drawable {
private:
    sf::CircleShape m_shape; // Shape for the trigger
    bool m_b_isActive = false; // State of the trigger
public:
    UnlockLevelTrigger();
    UnlockLevelTrigger(sf::Vector2f position, bool state = false);
    ~UnlockLevelTrigger();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // UNLOCKLEVELTRIGGER_H