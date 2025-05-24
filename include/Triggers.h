#ifndef TRIGEGERS_H
#define TRIGEGERS_H
#include <SFML/Graphics.hpp>
#include "actor.h"

class Triggers : public Actor {
private:
    bool m_b_isActive = false;
public:
    Triggers();
    Triggers(sf::Vector2f position);
    Triggers(sf::Vector2f position, bool state);
    ~Triggers();

    void setIsActive(bool isActive);
    bool isActive() const;

    // Switch the trigger state
    void switchState();
};

#endif // TRIGEGERS_H