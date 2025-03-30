#ifndef GAME_H
#define GAME_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Gravity.h"
#include "DeadlyPlatform.h"
#include "NextLevelTrigger.h"
#include "Background.h"
#include "UnlockLevelTrigger.h"

class Game {
private:
    bool m_b_cameraFollowsPlayer;
    sf::RenderWindow window; // Fereastra jocului
    Background background; // Fundalul jocului

    Player player;           // Jucatorul

    std::vector<std::unique_ptr<Platform>> platforms; // Platformele
    NextLevelTrigger nextLevelTrigger; // Trigger pentru nivelul urmator
    std::vector<UnlockLevelTrigger> unlockLevelTriggers; // Trigger pentru deblocarea nivelului
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

    // Function that makes sure the player does not go through walls and platforms
    void _solvePlatformCollisions(Player &player, std::vector<std::unique_ptr<Platform>> &platforms);

    // Function that solves trigger collisions
    void _checkNextLevelTriggerCollision(Player &player, NextLevelTrigger &nextLevelTrigger);

    // Function that deletes the current level
    void _deleteCurrentLevel();
};

#endif // GAME_H
