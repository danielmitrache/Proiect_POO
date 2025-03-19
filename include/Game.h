#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();                // Constructor
    ~Game();               // Destructor

    void run();            // Loop-ul principal al jocului

private:
    void processEvents();  // Procesează input-ul utilizatorului
    void update();         // Actualizează starea jocului
    void render();         // Desenează pe ecran

    sf::RenderWindow window; // Fereastra jocului
};

#endif // GAME_H
