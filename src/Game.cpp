#include "../include/Game.h"
#include "../include/Colisions.h"
#include <iostream>

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
}
// Destructor (dacă ai nevoie să cureți resurse)
Game::~Game() {}

// Loop-ul principal al jocului
void Game::run() {
    player.setHasGravity(true);
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
    // Aici vei pune logica jocului (mișcare, c./oliziuni etc.)
    player.update();

    // Gravitatie pentru fiecare obiect
    player.applyGravity();

    // Coliziuni
    for (auto& platform : platforms) {
        if (Colisions::checkColision(player, platform) && player.getVerticalSpeed() > 0)
        {
            player.setHasGravity(false);
            player.move({player.getX(), platform.getY() - player.getHeight()});
            player.resetVerticalSpeed();
        }
        else {
            player.setHasGravity(true);
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
