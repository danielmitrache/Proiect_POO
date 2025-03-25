#include "../include/Game.h"
#include "../include/Colisions.h"
#include <iostream>
#include <algorithm> // std::min, std::max

static unsigned int WINDOW_WIDTH = 1400u;
static unsigned int WINDOW_HEIGHT = 800u;
// Constructor: inițializează fereastra
Game::Game() 
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "My game!"),
    player({100.f, 50.f}) 
{
    this->window.setFramerateLimit(60);

    // Adaugă platforme
    platforms.push_back(Platform({0.f, 450.f}, {1400.f, 50.f}));
    platforms.push_back(Platform({200.f, 300.f}, {200.f, 50.f}));
    platforms.push_back(Platform({500.f, 300.f}, {50.f, 200.f}));
}
// Destructor (dacă ai nevoie să cureți resurse)
Game::~Game() {}

// Loop-ul principal al jocului
void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

// Procesează input-ul utilizatorului
void Game::processEvents() {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

// Update logică joc
void Game::update() {
    // Actualizează logica jucătorului (mișcări, salt, gravitație, etc.)
    player.update();

    // Rezolvă coliziunile pentru fiecare platformă
    for (auto& platform : platforms) {
        if (Colisions::checkColision(player, platform)) {
            // Extragem marginile jucătorului
            float pLeft   = player.getX();
            float pRight  = player.getX() + player.getWidth();
            float pTop    = player.getY();
            float pBottom = player.getY() + player.getHeight();

            // Margini platformă
            float platLeft   = platform.getX();
            float platRight  = platform.getX() + platform.getWidth();
            float platTop    = platform.getY();
            float platBottom = platform.getY() + platform.getHeight();

            // Calculăm overlap-ul pe fiecare axă
            float overlapX = std::min(pRight, platRight) - std::max(pLeft, platLeft);
            float overlapY = std::min(pBottom, platBottom) - std::max(pTop, platTop);

            // Aplică corecția doar pe axa cu suprapunerea minimă
            if (overlapX < overlapY) { // Rezolvare coliziune pe axa orizontală
                if (pLeft < platLeft) {
                    // Jucătorul vine din stânga platformei
                    player.move({ pLeft - overlapX, pTop });
                } else {
                    // Jucătorul vine din dreapta platformei
                    player.move({ pLeft + overlapX, pTop });
                }
            } else { // Rezolvare coliziune pe axa verticală
                if (pTop < platTop) {
                    // Jucătorul cade pe platformă
                    player.move({ pLeft, platTop - player.getHeight() });
                    player.setVerticalSpeed(0);
                    // Aici, de asemenea, poți marca că jucătorul nu mai sare (ex: m_b_isJumping = false)
                } else {
                    // Jucătorul lovește platforma de jos
                    player.move({ pLeft, platBottom });
                    player.setVerticalSpeed(0);
                }
            }
        }
    }
}

// Randare pe ecran
void Game::render() {
    window.clear(); // Șterge ecranul
    // Aici vei desena elementele jocului
    window.draw(player);

    for (auto& platform : platforms)
        window.draw(platform);

    window.display(); // Afișează frame-ul
}
