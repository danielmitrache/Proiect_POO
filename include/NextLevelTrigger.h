#ifndef NEXTLEVELTRIGGER_H
#define NEXTLEVELTRIGGER_H

#include "Triggers.h"

class NextLevelTrigger : public Triggers, public sf::Drawable {
private:
    std::string m_s_nextLevelPath; // Path to the next level
    sf::CircleShape m_shape; // Shape for the trigger area
public:
    NextLevelTrigger(); // Default constructor
    NextLevelTrigger(sf::Vector2f position, std::string nextLevelPath); // Constructor with position and level path
    ~NextLevelTrigger(); // Destructor

    // Set the next level path
    void setNextLevelPath(const std::string& nextLevelPath);

    // Get the next level path
    const std::string& getNextLevelPath() const;

    // Draw the trigger area
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Move the trigger area (both the position and the shape)
    //void move(const sf::Vector2f )
};

#endif // NEXTLEVELTRIGGER_H