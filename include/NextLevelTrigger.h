#ifndef NEXTLEVELTRIGGER_H
#define NEXTLEVELTRIGGER_H

#include "Triggers.h"

class NextLevelTrigger : public Triggers, public sf::Drawable {
private:
    int m_i_nextLevelID; // Next level ID
    sf::CircleShape m_shape; // Shape for the trigger area
public:
    NextLevelTrigger(); // Default constructor
    NextLevelTrigger(sf::Vector2f position, int nextLevelID); // Constructor with position and level id
    ~NextLevelTrigger(); // Destructor

    // Set the next level path
    void setNextLevelID(const int nextLevelID);

    // Get the next level path
    const int getNextLevelID() const;

    // Draw the trigger area
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Move the trigger area (both the position and the shape)
    void move(const sf::Vector2f);

    // Build the next level path
    std::string getNextLevelPath(std::string BASE_PATH = "D:/ProiectPOO/assets/level_layouts/") const;
};

#endif // NEXTLEVELTRIGGER_H