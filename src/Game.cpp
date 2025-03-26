#include "../include/Game.h"
#include "../include/Colisions.h"
#include <iostream>
#include <algorithm>

const unsigned int WINDOW_WIDTH = 1400u;
const unsigned int WINDOW_HEIGHT = 800u;
Game::Game() 
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "My game!"),
    player({100.f, 50.f}) 
{
    this->window.setFramerateLimit(60);

    // Adauga platforme
    platforms.push_back(Platform({0.f, 450.f}, {1400.f, 50.f}));
    platforms.push_back(Platform({200.f, 350.f}, {200.f, 50.f}));
    platforms.push_back(Platform({500.f, 300.f}, {50.f, 200.f}));
}

Game::~Game() {}

// Loop-ul principal al jocului
void Game::run() {
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


    for (auto& platform : platforms) {
        if (Colisions::checkColision(player, platform)) {
            // Extragem marginile jucătorului
            float pLeft   = player.getX();
            float pRight  = player.getX() + player.getWidth();
            float pTop    = player.getY();
            float pBottom = player.getY() + player.getHeight();

            // Margini platforma
            float platLeft   = platform.getX();
            float platRight  = platform.getX() + platform.getWidth();
            float platTop    = platform.getY();
            float platBottom = platform.getY() + platform.getHeight();

            // Calculam overlap-ul pe fiecare axa
            float overlapX = std::min(pRight, platRight) - std::max(pLeft, platLeft);
            float overlapY = std::min(pBottom, platBottom) - std::max(pTop, platTop);

            // Aplica corectia doar pe axa cu suprapunerea minima
            if (overlapX < overlapY) { // Rezolvare coliziune pe axa orizontala
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

void Game::_render() {
    if (m_b_cameraFollowsPlayer) {
        _centerCameraOnPlayer();
    }

    window.clear();

    _drawActors();

    window.display();
}

void Game::_centerCameraOnPlayer() {
    sf::View view = window.getDefaultView();
    view.setCenter({player.getX() + player.getWidth() / 2.f,player.getY() + player.getHeight() / 2.f});
    window.setView(view);
}

void Game::_drawActors() {
    window.draw(player);
    for (auto& platform : platforms)
        window.draw(platform);
}