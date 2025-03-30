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
    background("D:/ProiectPOO/assets/textures/Backgrounds/2.png")
{
    this->window.setFramerateLimit(60);
    background.setScale({WINDOW_WIDTH, WINDOW_HEIGHT});
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

    _solvePlatformCollisions(player, platforms);
    _checkNextLevelTriggerCollision(player, nextLevelTrigger);
}

void Game::_render() {
    window.clear();

    if (m_b_cameraFollowsPlayer) {
        _centerCameraOnPlayer(0.f, -50.f);
    }

    background.setPositionToView(window.getView()); // Setam pozitia fundalului in functie de camera

    window.draw(background); // Desenam fundalul
    _drawActors();

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
                player.move(player.getLastSpawn());
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

void Game::_checkNextLevelTriggerCollision(Player &player, NextLevelTrigger &nextLevelTrigger) {
    if (Colisions::checkColision(player, nextLevelTrigger)) {
        _loadPlatformerLevel(nextLevelTrigger.getNextLevelPath());
    }
}

void Game::_deleteCurrentLevel() {
    platforms.clear();
}