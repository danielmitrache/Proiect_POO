#ifndef GAME_H
#define GAME_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Gravity.h"
#include "DeadlyPlatform.h"
#include "NextLevelTrigger.h"

class Game {
private:
    bool m_b_cameraFollowsPlayer = true;
    sf::RenderWindow window; // Fereastra jocului

    Player player;           // Jucatorul
    std::vector<std::unique_ptr<Platform>> platforms; // Platformele
    NextLevelTrigger nextLevelTrigger; // Trigger pentru nivelul urmator
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
    void _centerCameraOnPlayer(float offsetX = 0.f, float offsetY = 0.f);
    
    // Draw the actors
    void _drawActors(); 

    // Platformer level loader
    void _loadPlatformerLevel(const std::string& levelPath, float tileSize = 50.f);
};

#endif // GAME_H
