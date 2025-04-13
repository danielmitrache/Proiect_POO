#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <random>
#include "Player.h"
#include "Platform.h"
#include "Colisions.h"
#include "Gravity.h"
#include "DeadlyPlatform.h"
#include "NextLevelTrigger.h"
#include "Background.h"
#include "UnlockLevelTrigger.h"
#include "EnemyWalker.h"
#include "TexturesManager.h"
#include "AnimationManager.h"
#include "RedOverlay.h"
#include "ColorHelpers.h"
#include "ProgressManager.h"

class Game {
private:
    int m_i_currentChapter;
    bool m_b_isInStartMenu; // Flag for start menu

    bool m_b_cameraFollowsPlayer;
    float m_f_levelWidth, m_f_levelHeight; // Dimensiunile nivelului curent
    sf::RenderWindow window; // Fereastra jocului
    Background background; // Fundalul jocului

    Player player;           // Jucatorul
    float m_f_playerInvincibilityTime = 0.f; // Timpul de invincibilitate al jucatorului
    int m_i_collectedCoins = 0, m_i_coinsNeededToPass = 0; // Numarul de monede colectate
    int m_i_deathCount = 0; // Numarul de morti al jucatorului

    std::vector<std::unique_ptr<Platform>> platforms; // Platformele
    NextLevelTrigger nextLevelTrigger; // Trigger pentru nivelul urmator
    std::vector<NextLevelTrigger> nextLevelTriggers; // Triggere pentru start menu
    std::vector<UnlockLevelTrigger> unlockLevelTriggers; // Trigger pentru deblocarea nivelului
    std::vector<EnemyWalker> enemyWalkers; // Inamicii

    std::vector<sf::Sprite> heartSprites; // Inimile jucatorului

    sf::Font m_font; // Fontul pentru text
    sf::Font m_pixelFont;
    sf::Text m_coinText;
    sf::Text m_deathCountText; // Textul pentru numarul de morti
    sf::Text m_levelNumberText; // Textul pentru numarul nivelului curent
    std::vector<sf::Text> m_startMenuTexts; // Vector de texte pentru UI

    TexturesManager m_texturesManager; // Managerul de texturi

    RedOverlay m_Overlay; // Overlay rosu pentru efecte vizuale

    float m_f_backgroundHue = 0.f;
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

    // Draw UI elements
    void _drawUI();

    // Platformer level loader
    void _loadPlatformerLevel(const std::string& levelPath, float tileSize = 64.f);

    // Function that makes sure the player does not go through walls and platforms
    void _solvePlatformCollisions(Player &player, std::vector<std::unique_ptr<Platform>> &platforms);

    // Function that solves trigger collisions
    void _checkNextLevelTriggerCollision(Player &player, NextLevelTrigger &nextLevelTrigger, std::vector<UnlockLevelTrigger> &unlockLevelTriggers);

    // Function that deletes the current level
    void _deleteCurrentLevel();

    // Function that checks if the player is in the trigger area of the unlock level trigger
    void _checkUnlockLevelTriggerCollision(Player &player, std::vector<UnlockLevelTrigger> &unlockLevelTriggers);

    // Function that updates hearts based on player health
    void _updateHearts(int health);

    // Function that checks all enemies collisions
    void _checkEnemyCollisions(Player &player, std::vector<EnemyWalker> &enemyWalkers);

    // Function that moves all enemy walkers
    void _moveEnemyWalkers(std::vector<EnemyWalker> &enemyWalkers, std::vector<std::unique_ptr<Platform>> &platforms);

    // Function that resets player position and health
    void _resetPlayerPositionAndHealth();

    // Function that updates all animations
    void _updateAnimations();

    // Function that initializez text elements for the UI
    void _initTextElements();

    // Function that loads a chapter of the game
    void _loadChapter(int chapterID);

    // Function that loads the start menu
    void _loadStartMenu(std::vector<int> &availableChapters);

    // Function that determines the levelID based on chapterID
    int _getLevelIDFromChapterID(int chapterID) const;

    // Function that checks if the player is in the trigger area of the start menu triggers
    void _checkStartMenuTriggersCollision(Player &player, std::vector<NextLevelTrigger> &nextLevelTriggers);
};

#endif // GAME_H
