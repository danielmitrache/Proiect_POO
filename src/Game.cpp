#include "../include/Game.h"
#include "../include/Colisions.h"
#include <iostream>
#include <fstream>
#include <algorithm>

const unsigned int WINDOW_WIDTH = 1400u;
const unsigned int WINDOW_HEIGHT = 800u;
Game::Game() 
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "My game!"),
    player({50.f, 200.f}),
    nextLevelTrigger(),
    background("D:/ProiectPOO/assets/textures/Backgrounds/2.png"),
    m_f_playerInvincibilityTime(0.f),
    m_coinText(m_font),
    m_deathCountText(m_font),
    m_i_deathCount(0)
{
    this->window.setFramerateLimit(60);
    background.setScale({WINDOW_WIDTH, WINDOW_HEIGHT});

    /// Load the heart texture
    if(!m_texture_heartTexture.loadFromFile("D:/ProiectPOO/assets/textures/heart.png")) {
        std::cerr << "Error loading heart texture" << std::endl;
    }

    /// Load the font
    if (!m_font.openFromFile("D:/ProiectPOO/assets/fonts/airstrike.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    m_coinText = sf::Text(m_font);
    m_coinText.setCharacterSize(40);
    m_coinText.setFillColor(sf::Color(255, 215, 0));
    m_coinText.setPosition({50.f, 45.f});
    m_coinText.setString("Coins: 0 / 0");
    m_deathCountText = sf::Text(m_font);
    m_deathCountText.setCharacterSize(40);
    m_deathCountText.setFillColor(sf::Color::Red);
    m_deathCountText.setPosition({50.f, 5.f});
    m_deathCountText.setString("Deaths: 0");

}

Game::~Game() {}

// Loop-ul principal al jocului
void Game::run() {
    _loadPlatformerLevel("D:/ProiectPOO/assets/level_layouts/level0.txt");
    player.setHasGravity(true);
    player.setMode(PlayerMode::Platformer);
    while (window.isOpen()) {
        _processEvents();
        _update();
        _render();
    }
}

// Proceseaza input-ul utilizatorului
void Game::_processEvents() {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

// Update logica joc
void Game::_update() {
    player.update();
    player.setCanJump(false); // Presupunem ca nu putem sari pana cand nu verificam coliziunile

    if (m_f_playerInvincibilityTime > 0.f) {
        m_f_playerInvincibilityTime -= 1.f / 60.f; // Scadem timpul de invincibilitate
    }

    _moveEnemyWalkers(enemyWalkers, platforms);
    _solvePlatformCollisions(player, platforms);
    _checkUnlockLevelTriggerCollision(player, unlockLevelTriggers);
    _checkNextLevelTriggerCollision(player, nextLevelTrigger, unlockLevelTriggers);
    _checkEnemyCollisions(player, enemyWalkers);
    _updateHearts(player.getHealth());
    

    if (player.getHealth() <= 0) {
        std::cout << "Game Over!" << std::endl;
        m_i_deathCount ++; // Increment death count
        _resetPlayerPositionAndHealth(); // Reset player position and health
    }
}

void Game::_render() {
    window.clear(); 

    if (m_b_cameraFollowsPlayer) {
        _centerCameraOnPlayer(0.f, -50.f);
        background.setScale({4 * WINDOW_WIDTH, 4 * WINDOW_HEIGHT}); // Setam dimensiunea fundalului in functie de camera
        float parallaxFactor = 0.5f;
        background.setPosition(sf::Vector2f(-1000.f, -1 * m_f_levelHeight - 500.f) + sf::Vector2f(player.getX() * parallaxFactor, player.getY() * parallaxFactor)); // Setam pozitia fundalului in functie de camera
    }

    if (!m_b_cameraFollowsPlayer) {
        background.setScale({WINDOW_WIDTH, WINDOW_HEIGHT}); // Setam dimensiunea fundalului in functie de camera
        background.setPositionToView(window.getView()); // Setam pozitia fundalului in functie de camera
    }

    window.draw(background); // Desenam fundalul
    _drawActors();
    _drawUI(); // Desenam UI-ul

    window.display();
}

void Game::_centerCameraOnPlayer(float offsetX, float offsetY) {
    sf::View view = window.getDefaultView();
    view.setCenter({player.getX() + player.getWidth() / 2.f + offsetX,player.getY() + player.getHeight() / 2.f + offsetY});
    window.setView(view);
}

void Game::_drawActors() {
    window.draw(player);
    window.draw(nextLevelTrigger);
    for (auto& platform : platforms)
        window.draw(*platform);
    for (auto& unlockLevelTrigger : unlockLevelTriggers)
        window.draw(unlockLevelTrigger);
    for (auto& enemyWalker : enemyWalkers)
        window.draw(enemyWalker);
}

void Game::_drawUI() {
    window.setView(window.getDefaultView()); // Setam camera la pozitia initiala
    for (auto& heart : heartSprites) {
        window.draw(heart); // Desenam inimile
    }

    // Desenam textul cu numarul de monede
    m_coinText.setString("Coins: " + std::to_string(m_i_collectedCoins) + " / " + std::to_string(m_i_coinsNeededToPass));
    window.draw(m_coinText); // Desenam textul cu numarul de monede

    // Desenam textul cu numarul de morti
    m_deathCountText.setString("Deaths: " + std::to_string(m_i_deathCount));
    window.draw(m_deathCountText); // Desenam textul cu numarul de morti
}

void Game::_loadPlatformerLevel(const std::string &levelPath, float tileSize) {
    // Stergem nivelul curent
    _deleteCurrentLevel();

    std::ifstream file(levelPath);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << levelPath << std::endl;
        return;
    }

    bool doesCameraFollowPlayer = true;
    file >> doesCameraFollowPlayer;
    m_b_cameraFollowsPlayer = doesCameraFollowPlayer;

    std::string line;
    int lineNumber = 0, columnNumber = 0;
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        columnNumber = 0;
        while (iss >> token) {
            int tileType = std::stoi(token);

            if (tileType == 0){
                columnNumber ++;
                continue;
            }
            sf::Vector2f position(columnNumber * tileSize, lineNumber * tileSize);
            sf::Vector2f size(tileSize, tileSize);
            if (tileType == 1)
                platforms.push_back(std::make_unique<Platform>(position, size));
            else if (tileType == 2)
                platforms.push_back(std::make_unique<DeadlyPlatform>(position, size, 10.f));
            else if (tileType == 3)
                platforms.push_back(std::make_unique<Platform>(position, size, true));
            else if (tileType == 4) {
                player.move(position);
                player.setLastSpawn(position);
            }
            else if (tileType == 5) {
                nextLevelTrigger.move(position);
                nextLevelTrigger.setNextLevelID(nextLevelTrigger.getNextLevelID() + 1);
                std::cout << "Next Level ID: " << nextLevelTrigger.getNextLevelID() << std::endl;
            }
            else if (tileType == 6) {
                unlockLevelTriggers.push_back(UnlockLevelTrigger(position));
                m_i_coinsNeededToPass ++;
            }
            else if (tileType == 7) {
                enemyWalkers.push_back(EnemyWalker(position, 3.f, 30.f));
            }
            columnNumber ++;
        }
        lineNumber ++;
    }

    if (!m_b_cameraFollowsPlayer) {
        // Center the camera on the level
        sf::View view = window.getDefaultView();
        view.setCenter({columnNumber * tileSize / 2.f, lineNumber * tileSize / 2.f});
        window.setView(view);
    }

    // Add platform that kills the player if it falls into the void
    platforms.push_back(std::make_unique<DeadlyPlatform>(sf::Vector2f(-9999.f, lineNumber * tileSize + 400.f), sf::Vector2f(99999999.f, 10.f), 999999.f, false));

    m_f_levelHeight = lineNumber * tileSize;
    m_f_levelWidth = columnNumber * tileSize;

    file.close();
    std::cout << "Level loaded from: " << levelPath << std::endl;
}

void Game::_solvePlatformCollisions(Player &player, std::vector<std::unique_ptr<Platform>> &platforms) {
    for (auto& platform : platforms) {
        if (Colisions::checkColision(player, *platform)) {

            if (platform -> isDeadly()) {
                // Resetam nivelul
                //nextLevelTrigger.setNextLevelID(nextLevelTrigger.getNextLevelID() - 1);
                //_loadPlatformerLevel(nextLevelTrigger.getNextLevelPath());
                player.setHealth(-1.f); // Set health to 0 to trigger game over
                continue;
            }

            // Extragem marginile jucătorului
            float pLeft   = player.getX();
            float pRight  = player.getX() + player.getWidth();
            float pTop    = player.getY();
            float pBottom = player.getY() + player.getHeight();

            // Margini platforma
            float platLeft   = platform -> getX();
            float platRight  = platform -> getX() + platform -> getWidth();
            float platTop    = platform -> getY();
            float platBottom = platform -> getY() + platform -> getHeight();

            // Calculam overlap-ul pe fiecare axa
            float overlapX = std::min(pRight, platRight) - std::max(pLeft, platLeft);
            float overlapY = std::min(pBottom, platBottom) - std::max(pTop, platTop);

            // Aplica corectia doar pe axa cu suprapunerea minima
            if (overlapX < overlapY) { // Rezolvare coliziune pe axa orizontala
                if (platform -> isSticky()) {
                    player.setVerticalSpeed(0.f);
                    player.setCanJump(true);
                }
                if (pLeft < platLeft) {
                    // Jucatorul vine din stanga platformei
                    player.move({ pLeft - overlapX, pTop });
                } else {
                    // Jucatorul vine din dreapta platformei
                    player.move({ pLeft + overlapX, pTop });
                }
            } else { // Rezolvare coliziune pe axa verticala
                if (pTop < platTop) {
                    // Jucatorul cade pe platformă
                    player.move({ pLeft, platTop - player.getHeight() });
                    player.setVerticalSpeed(0.f);
                    player.setCanJump(true);
                } else {
                    // Jucatorul lovește platforma de jos
                    player.move({ pLeft, platBottom });
                    player.setVerticalSpeed(-0.75 * player.getVerticalSpeed());
                }
            }
        }
    }
}

void Game::_checkNextLevelTriggerCollision(Player &player, NextLevelTrigger &nextLevelTrigger, std::vector<UnlockLevelTrigger> &unlockLevelTriggers) {
    if (Colisions::checkColision(player, nextLevelTrigger) && unlockLevelTriggers.empty()) {
        _loadPlatformerLevel(nextLevelTrigger.getNextLevelPath());
    }
}

void Game::_deleteCurrentLevel() {
    platforms.clear();
    unlockLevelTriggers.clear();
    enemyWalkers.clear();
}

void Game::_checkUnlockLevelTriggerCollision(Player &player, std::vector<UnlockLevelTrigger> &unlockLevelTriggers) {
    for (size_t i = 0; i < unlockLevelTriggers.size(); ++i) {
        if (Colisions::checkColision(player, unlockLevelTriggers[i])) {
            unlockLevelTriggers.erase(unlockLevelTriggers.begin() + i);
            m_i_collectedCoins ++;
            i --;
        }
    }
}

void Game::_updateHearts(int health) {
    /// 1 HEART => 0 < H <= 25
    /// 2 HEARTS => 25 < H <= 50
    /// 3 HEARTS => 50 < H <= 75
    /// 4 HEARTS => 75 < H <= 100
    if (health > 75 && health <= 100) {
        heartSprites.clear();
        for(int i = 0; i < 4; i ++) {
            sf::Sprite heart(m_texture_heartTexture);
            heart.setPosition({WINDOW_WIDTH - 150.f - i * 50.f, 5.f});
            heart.setScale({2.f, 2.f});
            heartSprites.push_back(heart);
        }
    }
    else if (health > 50 && health <= 75) {
        heartSprites.clear();
        for(int i = 0; i < 3; i ++) {
            sf::Sprite heart(m_texture_heartTexture);
            heart.setPosition({WINDOW_WIDTH - 150.f - i * 50.f, 5.f});
            heart.setScale({2.f, 2.f});
            heartSprites.push_back(heart);
        }
    }
    else if (health > 25 && health <= 50) {
        heartSprites.clear();
        for(int i = 0; i < 2; i ++) {
            sf::Sprite heart(m_texture_heartTexture);
            heart.setPosition({WINDOW_WIDTH - 150.f - i * 50.f, 5.f});
            heart.setScale({2.f, 2.f});
            heartSprites.push_back(heart);
        }
    }
    else if (health > 0 && health <= 25) {
        heartSprites.clear();
        for(int i = 0; i < 1; i ++) {
            sf::Sprite heart(m_texture_heartTexture);
            heart.setPosition({WINDOW_WIDTH - 150.f - i * 50.f, 5.f});
            heart.setScale({2.f, 2.f});
            heartSprites.push_back(heart);
        }
    }
    else if (health <= 0) {
        heartSprites.clear();
    }
}

void Game::_checkEnemyCollisions(Player &player, std::vector<EnemyWalker> &enemyWalkers) {
    for (size_t i = 0; i < enemyWalkers.size(); ++i) {
        EnemyWalker& enemyWalker = enemyWalkers[i];
        if (Colisions::checkColision(player, enemyWalker)) {
            if (m_f_playerInvincibilityTime > 0.f) {
                // Player is invincible, ignore the hit
                continue;
            }
            if (player.getVerticalSpeed() > 0.f) {
                std::cout << "Player jumped on enemy!" << std::endl;
                // Player jumps on the enemy
                player.setVerticalSpeed(-player.getVerticalSpeed() * 1.3f); // Bounce off the enemy
                continue; // Skip the rest of the loop
            } 
            player.setHealth(player.getHealth() - enemyWalker.getDamage());
            std::cout << "Player hit by enemy! Health: " << player.getHealth() << std::endl;
            m_f_playerInvincibilityTime = 1.f; // Set invincibility time to 1 second
        }
    }
}

void Game::_moveEnemyWalkers(std::vector<EnemyWalker> &enemyWalkers, std::vector<std::unique_ptr<Platform>> &platforms) {
    for (auto& enemyWalker : enemyWalkers) {
        enemyWalker.update();
        for (auto& platform : platforms) {
            if (Colisions::checkColision(enemyWalker, *platform)) {
                enemyWalker.reverseDirection(); // Inversam directia inamicului
            }
        }
    }
}

void Game::_resetPlayerPositionAndHealth() {
    player.move(player.getLastSpawn());
    player.setHealth(100); // Reset health to 100
    for(int i = 0; i < 3; i ++) {
        sf::Sprite heart(m_texture_heartTexture);
        heart.setPosition({5.f + i * 50.f, 5.f});
        heart.setScale({2.f, 2.f});
        heartSprites.push_back(heart);
    }
}