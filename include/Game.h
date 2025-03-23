#ifndef GAME_H
#define GAME_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"

class Game {
private:
    sf::RenderWindow window; // Fereastra jocului
    Player player;           // Jucătorul
    std::vector <Platform> platforms; // Platformele
public:
    Game();                // Constructor
    ~Game();               // Destructor

    void run();            // Loop-ul principal al jocului

private:
    void processEvents();  // Procesează input-ul utilizatorului
    void update();         // Actualizează starea jocului
    void render();         // Desenează pe ecran
};

#endif // GAME_H
