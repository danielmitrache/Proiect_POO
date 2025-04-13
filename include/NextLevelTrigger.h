#ifndef NEXTLEVELTRIGGER_H
#define NEXTLEVELTRIGGER_H

#include "Triggers.h"

class NextLevelTrigger : public Triggers, public sf::Drawable {
private:
    int m_i_nextLevelID = 0; // Next level ID
    bool m_b_canInteract = false; // Flag for interaction
    sf::RectangleShape m_shape; // Shape for the trigger area
public:
    NextLevelTrigger(); // Default constructor
    NextLevelTrigger(sf::Vector2f position, int nextLevelID, bool canInteract = true); // Constructor with position and level id
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

    // Set texture for the trigger area
    void setTexture(const sf::Texture* texture, const sf::IntRect& textureRect = sf::IntRect({-1, -1}, {-1, -1}));

    // Set texure rect for the trigger area
    void setTextureRect(const sf::IntRect& textureRect);

    // Set the color of the trigger area
    void setColor(const sf::Color& color);

    // Get if the trigger is interactable
    bool isInteractable() const;
};

#endif // NEXTLEVELTRIGGER_H