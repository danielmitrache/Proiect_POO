#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <regex>
#include <string>
#include <sstream>
#include "player.h"
#include "platform.h"
#include "colisions.h"
#include "gravity.h"
#include "deadly_platform.h"
#include "next_level_trigger.h"
#include "background.h"
#include "unlock_level_trigger.h"
#include "enemy_walker.h"
#include "textures_manager.h"
#include "animation_manager.h"
#include "red_overlay.h"
#include "color_helpers.h"
#include "progress_manager.h"
#include "sounds_manager.h"
#include "enemy_shooter.h"
#include "kill_aura.h"
#include "bullet.h"
#include "enemy_chaser.h"

struct PositionSpeed {
    sf::Vector2i position;
    float speed;
};

class Game {
private:
    int m_i_currentChapter = -1;
    bool m_b_isInStartMenu; // Flag for start menu

    bool m_b_cameraFollowsPlayer;
    float m_f_levelWidth, m_f_levelHeight; // Dimensiunile nivelului curent
    sf::RenderWindow window; // Fereastra jocului
    Background background; // Fundalul jocului

    std::deque<sf::Vector2f> m_playerPositionHistory;
    Player player;           // Jucatorul
    KillAura killAura;      // Aura de atac
    float m_f_playerInvincibilityTime = 0.f; // Timpul de invincibilitate al jucatorului
    int m_i_collectedCoins = 0, m_i_coinsNeededToPass = 0; // Numarul de monede colectate
    int m_i_deathCount = 0; // Numarul de morti al jucatorului

    std::vector<std::unique_ptr<Platform>> platforms; // Platformele
    NextLevelTrigger nextLevelTrigger; // Trigger pentru nivelul urmator
    std::vector<NextLevelTrigger> nextLevelTriggers; // Triggere pentru start menu
    std::vector<UnlockLevelTrigger> unlockLevelTriggers; // Trigger pentru deblocarea nivelului
    std::vector<EnemyWalker> enemyWalkers; // Inamicii care se misca
    std::vector<EnemyShooter> enemyShooters; // Inamicii care trag
    std::vector<EnemyChaser> enemyChasers; // Inamicii care urmaresc jucatorul


    std::vector<sf::Sprite> heartSprites; // Inimile jucatorului

    sf::Font m_font; // Fontul pentru text
    sf::Font m_pixelFont;
    sf::Text m_coinText;
    sf::Text m_deathCountText; // Textul pentru numarul de morti
    sf::Text m_levelNumberText; // Textul pentru numarul nivelului curent
    sf::Text m_wantToExitText; // Textul pentru a iesi din joc
    sf::Text m_attackCooldownText; // Textul pentru cooldown-ul de atac
    std::vector<sf::Text> m_startMenuTexts; // Vector de texte pentru UI-ul din start menu

    TexturesManager m_texturesManager; // Managerul de texturi

    SoundsManager m_soundsManager; // Managerul de sunete

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
    void _loadPlatformerLevel(const std::string& levelPath, bool comingFromMenu = false ,float tileSize = 64.f);

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

    // Function that updates the enemy shooters
    void _updateEnemyShooters(std::vector<EnemyShooter> &enemyShooters, Player &player);

    // Function for when the player gets hit
    void _playerHit(Player &player, float damage);

    // Function that checks if the player is killing an enemy
    void _checkEnemyKillAuraCollision(KillAura killAura, std::vector<EnemyShooter> &enemyShooters);

    // Function that updates kill aura position / animation
    void _updateKillAura(KillAura &killAura, Player &player);

    // Function that updates enemy chasers
    void _updateEnemyChasers(std::vector<EnemyChaser> &enemyChasers, Player &player);

    // Function that reads a config file
    std::vector< PositionSpeed > _readConfigFile(const std::string& filePath);

    // Function that checks if bullets go into walls
    void _checkBulletCollisions(std::vector<EnemyShooter> &enemyShooters, std::vector<std::unique_ptr<Platform>> &platforms);
};

#endif // GAME_H
