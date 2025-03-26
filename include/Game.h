#ifndef GAME_H
#define GAME_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Gravity.h"

class Game {
private:
    bool m_b_cameraFollowsPlayer = true;
    sf::RenderWindow window; // Fereastra jocului

    Player player;           // Jucatorul
    std::vector <Platform> platforms; // Platformele
public:
    Game();               
    ~Game();               

    // Main game loop
    void run();

private:
    // Process user input
    void _processEvents();

    // Update game logic
    void _update();

    // Render the game
    void _render();

    // Center the camera on the player
    void _centerCameraOnPlayer();
    
    // Draw the actors
    void _drawActors(); 
};

#endif // GAME_H
