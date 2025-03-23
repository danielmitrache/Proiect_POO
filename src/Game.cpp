#include "../include/Game.h"

// Constructor: inițializează fereastra
Game::Game() 
    : window(sf::VideoMode({1400u, 800u}), "My game!"),
    player(100.f, 50.f) 
{
    this->window.setFramerateLimit(60);
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
    // Aici vei pune logica jocului (mișcare, coliziuni etc.)
    player.update();
}

// Randare pe ecran
void Game::render() {
    window.clear(); // Șterge ecranul
    // Aici vei desena elementele jocului
    window.draw(player);

    window.display(); // Afișează frame-ul
}
