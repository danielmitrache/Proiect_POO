#include "../include/Game.h"

const unsigned int WINDOW_WIDTH = 1400u;
const unsigned int WINDOW_HEIGHT = 800u;
Game::Game() 
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "My game!"),
    player({50.f, 200.f}),
    nextLevelTrigger({-9999.f, -9999.f}, 0),
    background("./assets/textures/Backgrounds/1.png"),
    m_f_playerInvincibilityTime(0.f),
    m_coinText(m_font), m_deathCountText(m_font), m_levelNumberText(m_font), m_wantToExitText(m_font),
    m_i_deathCount(0),
    m_texturesManager(),
    m_soundsManager(),
    killAura({0.f, 0.f}, 100.f, sf::Color::White, &m_texturesManager.getKillAuraTexture(), sf::IntRect({0, 0}, {420, 420})) // Initialize kill aura
{
    this->window.setFramerateLimit(60);
    background.setScale({WINDOW_WIDTH, WINDOW_HEIGHT});

    _initTextElements(); // Initialize text elements

    player.setTexture(&m_texturesManager.getPlayerTexture());
    player.setColor(sf::Color::Blue);

    nextLevelTrigger.setTexture(&m_texturesManager.getNextLevelTriggerTexture(), sf::IntRect({0, 0}, {32, 32}));
    nextLevelTrigger.setColor(sf::Color::White); 
}

Game::~Game() {}

// Loop-ul principal al jocului
void Game::run() {
    ProgressManager::saveChapterToFile(1);
    std::vector<int> availableChapters = ProgressManager::loadSavedChaptersFromFile(); // Get available chapters from ProgressManager
    // Set the player color based on how many chapters he has unlocked
    float playerFadeFactor = std::min(1.f, ((availableChapters.size() - 1) * 0.12f));
    player.setColor(ColorHelpers::blendColors(sf::Color::Blue, sf::Color::White, playerFadeFactor)); // Set player color based on the number of unlocked chapters

    _loadStartMenu(availableChapters); // Load the start menu
    player.setHasGravity(true);
    player.setMode(PlayerMode::Platformer);
    while (window.isOpen()) {
        _processEvents();
        _update();
        _render();
    }
}

// Proceseaza input-ul utilizatorului
float escTimer = 0.f;
void Game::_processEvents() {
    if (escTimer > 0.f) {
        escTimer -= 1.f / 60.f;
    }
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (event->is<sf::Event::KeyPressed>()) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                if (escTimer <= 0.f) {
                    escTimer = 2.f;
                    if (m_b_isInStartMenu) {
                        m_wantToExitText.setString("Exit the game? Press ESC again to confirm.");
                    }
                    else {
                        m_wantToExitText.setString("Exit to main menu? Press ESC again to confirm.");
                    }
                }
                else {
                    if (!m_b_isInStartMenu) {
                        std::vector<int> availableChapters = ProgressManager::loadSavedChaptersFromFile(); // Get available chapters from ProgressManager
                        m_b_isInStartMenu = true; // Set the flag to true
                        _loadStartMenu(availableChapters); // Load the start menu
                    }
                    else {
                        window.close(); // Close the game window
                    }
                }
            }
        }
    }
}

// Update logica joc
void Game::_update() {
    player.update();
    player.setCanJump(false); // Presupunem ca nu putem sari pana cand nu verificam coliziunile



    if (m_f_playerInvincibilityTime > 0.f) {
        m_f_playerInvincibilityTime -= 1.f / 60.f; // Scadem timpul de invincibilitate
    }

    if (m_b_isInStartMenu) { // Daca suntem in start menu
        _checkStartMenuTriggersCollision(player, nextLevelTriggers); // Verificam coliziunile cu triggerele din start menu
    }

    _moveEnemyWalkers(enemyWalkers, platforms);
    _updateEnemyShooters(enemyShooters, player);
    _solvePlatformCollisions(player, platforms);
    _checkUnlockLevelTriggerCollision(player, unlockLevelTriggers);
    _checkNextLevelTriggerCollision(player, nextLevelTrigger, unlockLevelTriggers);
    _checkEnemyCollisions(player, enemyWalkers);
    _updateHearts(player.getHealth());
    _updateKillAura(killAura, player); // Update kill aura position and state
    _checkEnemyKillAuraCollision(killAura, enemyShooters); // Check if the player is killing an enemy

    /// ANIMATIONS
    _updateAnimations();
   
    if (!m_b_isInStartMenu) {
        m_f_backgroundHue ++;
        background.setColor(ColorHelpers::blendColors(sf::Color::White, ColorHelpers::hsvToRgb(fmod(m_f_backgroundHue, 360.f), 0.5f, 0.5f), 0.5f)); // Setam culoarea fundalului in functie de unghiul de rotatie    
    }
 
    if (player.getHealth() <= 0) {
        std::cout << "Game Over!" << std::endl;
        m_i_deathCount ++; // Increment death count
        _resetPlayerPositionAndHealth(); // Reset player position and health

        m_Overlay.setColor(sf::Color(255, 0, 0, 180)); // Set red overlay color to red with full opacity
    }


    // Fade out the overlay if it is visible
    if (m_Overlay.getAlpha() > 0) {
        m_Overlay.setAlpha(m_Overlay.getAlpha() - 3.f); // Fade out the overlay
    }
}

void Game::_render() {
    window.clear(); 

    if (m_b_cameraFollowsPlayer) {
        _centerCameraOnPlayer(0.f, -50.f);
        background.setScale({4 * WINDOW_WIDTH, 4 * WINDOW_HEIGHT}); // Setam dimensiunea fundalului in functie de camera
        float parallaxFactor = 0.5f;
        background.setPosition(sf::Vector2f(-1000.f, -1 * m_f_levelHeight + 200.f) + sf::Vector2f(player.getX() * parallaxFactor, player.getY() * parallaxFactor)); // Setam pozitia fundalului in functie de camera
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
    if (m_b_isInStartMenu) { // Desenam actorii din start menu
        for (auto& nextLevelTrigger : nextLevelTriggers) {
            window.draw(nextLevelTrigger);
        }
    }

    window.draw(killAura); 
    window.draw(player);
    window.draw(nextLevelTrigger);
    for (auto& platform : platforms)
        window.draw(*platform);
    for (auto& unlockLevelTrigger : unlockLevelTriggers)
        window.draw(unlockLevelTrigger);
    for (auto& enemyWalker : enemyWalkers)
        window.draw(enemyWalker);
    for (auto& enemyShooter : enemyShooters){
        window.draw(enemyShooter);
        for (auto& bullet : enemyShooter.m_bullets) {
            window.draw(bullet); // Desenam gloantele
        }
    }
}

void Game::_drawUI() {

    if (m_b_isInStartMenu) { // Desenam UI-ul din start menu
        for (auto& text : m_startMenuTexts) {
            window.draw(text); // Desenam textul din start menu
        }
    }
    else {
        window.setView(window.getDefaultView()); // Setam camera la pozitia initiala
        for (auto& heart : heartSprites) {
            window.draw(heart); // Desenam inimile
        }

        // Desenam overlay-ul rosu
        window.draw(m_Overlay); // Desenam overlay-ul 

        // Desenam textul cu numarul de monede
        m_coinText.setString("Coins: " + std::to_string(m_i_collectedCoins) + " / " + std::to_string(m_i_coinsNeededToPass));
        window.draw(m_coinText); // Desenam textul cu numarul de monede

        // Desenam textul cu numarul de morti
        m_deathCountText.setString("Deaths: " + std::to_string(m_i_deathCount));
        window.draw(m_deathCountText); // Desenam textul cu numarul de morti

        // Desenam textul cu numarul nivelului curent
        m_levelNumberText.setString("Chapter: " + std::to_string(m_i_currentChapter));
        window.draw(m_levelNumberText); // Desenam textul cu numarul nivelului curent
    }

    if(escTimer > 0.f) {
        window.draw(m_wantToExitText); // Desenam textul pentru a iesi din joc
    }
}

void Game::_loadPlatformerLevel(const std::string &levelPath, bool comingFromMenu, float tileSize) {
    // Stergem nivelul curent
    _deleteCurrentLevel();

    std::ifstream file(levelPath);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << levelPath << std::endl;
        return;
    }

    sf::IntRect grassNormalTile({0, 0}, {512, 512});
    sf::IntRect wallNormalTile({512, 0}, {512, 512});
    sf::IntRect deadlyTile({0, 512}, {512, 512});
    sf::IntRect stickyTile({512, 512}, {512, 512});

    bool doesCameraFollowPlayer = true;
    file >> doesCameraFollowPlayer;
    m_b_cameraFollowsPlayer = doesCameraFollowPlayer;

    int previousChapter = m_i_currentChapter;
    file >> m_i_currentChapter;
    background.setTexture("./assets/textures/Backgrounds/" + std::to_string(m_i_currentChapter) + ".png");
    // std::cout << "Previous chapter: " << previousChapter << std::endl;
    // std::cout << "Current chapter: " << m_i_currentChapter << std::endl;
    // std::cout << "Coming from menu: " << comingFromMenu << std::endl;
    if (previousChapter != m_i_currentChapter && !comingFromMenu) {
        /// NEW CHAPTER
        std::cout << "New chapter: " << m_i_currentChapter << std::endl;
        m_Overlay.setColor(sf::Color(255, 255, 255, 210)); // Set white overlay color to white with full opacity
        m_i_collectedCoins = 0;
        m_i_coinsNeededToPass = 0;
        m_i_deathCount = 0;
        ProgressManager::saveChapterToFile(m_i_currentChapter); // Save the current chapter to the file

        /// Go back to the start menu
        m_b_isInStartMenu = true;
        std::vector<int> availableChapters = ProgressManager::loadSavedChaptersFromFile(); // Get available chapters from ProgressManager
        _loadStartMenu(availableChapters); // Load the start menu
        return;
    }
    

    std::string line;
    std::vector<int> prevRow, currentRow;
    int lineNumber = 0, columnNumber = 0;
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        columnNumber = 0;
        while (iss >> token) {
            int tileType = std::stoi(token);

            currentRow.push_back(tileType);

            if (tileType == 0){
                columnNumber ++;
                continue;
            }
            sf::Vector2f position(columnNumber * tileSize, lineNumber * tileSize);
            sf::Vector2f size(tileSize, tileSize);
            if (tileType == 1) {
                if (lineNumber == 0 || lineNumber > 0 && prevRow[columnNumber] != 1 && prevRow[columnNumber] != 2 && prevRow[columnNumber] != 3) {
                    platforms.push_back(std::make_unique<Platform>(position, size, &m_texturesManager.getTilesetTexture(), grassNormalTile));
                    // Daca nu avem platforma deasupra, adaugam platforma cu iarba
                }
                else {
                    platforms.push_back(std::make_unique<Platform>(position, size, &m_texturesManager.getTilesetTexture(), wallNormalTile));
                    // Daca avem platforma deasupra, adaugam platforma fara iarba
                }
            }
            else if (tileType == 2)
                platforms.push_back(std::make_unique<DeadlyPlatform>(position, size, 50.f, &m_texturesManager.getTilesetTexture(), deadlyTile));
            else if (tileType == 3)
                platforms.push_back(std::make_unique<Platform>(position, size, true, &m_texturesManager.getTilesetTexture(), stickyTile));
            else if (tileType == 4) {
                if (comingFromMenu) 
                    player.move(position); // Daca e primul nivel sau capitol nou
                
                player.setLastSpawn(position);
            }
            else if (tileType == 5) {
                nextLevelTrigger.move(position);
                nextLevelTrigger.setNextLevelID(nextLevelTrigger.getNextLevelID() + 1);
            }
            else if (tileType == 6) {
                unlockLevelTriggers.push_back(UnlockLevelTrigger(position + sf::Vector2f(16.f, 16.f), {32.f, 32.f}));
                m_i_coinsNeededToPass ++;
            }
            else if (tileType == 7) {
                enemyWalkers.push_back(EnemyWalker(position, {tileSize, tileSize}, &m_texturesManager.getEnemyWalkerTextureRight(), sf::IntRect({4, 4}, {32, 32}), 3.f, 30.f));
            }
            else if (tileType == 8) {
                enemyShooters.push_back(EnemyShooter(position, {tileSize, tileSize}, &m_texturesManager.getEnemyShooterLeftTexture(), sf::IntRect({0, 0}, {44, 44}), 0.f, 25.f, 0.5f, 100.f));
            }
            columnNumber ++;
        }

        prevRow = currentRow;
        currentRow.clear();

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

    for (auto& unlockLevelTrigger : unlockLevelTriggers) {
        unlockLevelTrigger.setTexture(&m_texturesManager.getUnlockLevelTriggerTexture(), sf::IntRect({0, 36}, {18, 18}));
        unlockLevelTrigger.setColor(sf::Color::White); // Set color to white
    }

    file.close();
    std::cout << "Level loaded from: " << levelPath << std::endl;
}

void Game::_loadStartMenu(std::vector<int> &availableChapters) {
    m_soundsManager.stopAllBackgroundMusic(); // Stop the current background music
    m_soundsManager.playBackgroundMusic("mainMenuMusic", sf::seconds(4.f));
    m_b_isInStartMenu = true;
    m_b_cameraFollowsPlayer = true;
    const float tileSize = 64.f; 
    background.setColor(ColorHelpers::blendColors(sf::Color::White, sf::Color::Black, 0.5f)); // Set background color to black with 50% opacity
    background.setTexture("./assets/textures/Backgrounds/startmenu.png"); // Set background texture to start menu texture
    _deleteCurrentLevel(); // Delete the current level

    std::ifstream file("./assets/level_layouts/startmenu.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open file: startmenu.txt" << std::endl;
        return;
    }

    sf::IntRect grassNormalTile({0, 0}, {512, 512});

    int currentChapterTrigger = 0;

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
            if (tileType == 1) {
                platforms.push_back(std::make_unique<Platform>(position, size, &m_texturesManager.getTilesetTexture(), grassNormalTile));
                platforms.back()->setColor(ColorHelpers::blendColors(sf::Color::White, sf::Color::Black, 0.5f)); // Set color to gray
            }
            else if (tileType == 4) {
                player.move(position);
                player.setLastSpawn(position);
            }
            else if (tileType == 5) {
                currentChapterTrigger ++;
                if (std::find(availableChapters.begin(), availableChapters.end(), currentChapterTrigger) != availableChapters.end()) {
                    nextLevelTriggers.push_back(NextLevelTrigger(position, currentChapterTrigger, true));
                    nextLevelTriggers.back().setColor(sf::Color(34,244,218)); // Set color to white
                } else {
                    nextLevelTriggers.push_back(NextLevelTrigger(position, currentChapterTrigger, false));
                    nextLevelTriggers.back().setColor(ColorHelpers::blendColors(sf::Color(34,244,218), sf::Color::Black, 0.5f)); // Set color to red with full opacity
                }
                nextLevelTriggers.back().setTexture(&m_texturesManager.getNextLevelTriggerTexture(), sf::IntRect({0, 0}, {32, 32}));

                // Write text with chapter number above the trigger
                sf::Text chapterText(m_pixelFont, std::to_string(currentChapterTrigger));
                chapterText.setCharacterSize(30);
                if (std::find(availableChapters.begin(), availableChapters.end(), currentChapterTrigger) != availableChapters.end()) 
                    chapterText.setFillColor(sf::Color::White); // Set text color to white
                else
                    chapterText.setFillColor(sf::Color(128, 128, 128)); // Set text color to red
                
                chapterText.setPosition({position.x + 20.f, position.y - 40.f}); // Set text position above the trigger
                m_startMenuTexts.push_back(chapterText); // Add the text to the vector
            }
            else if( tileType == 2) {
                platforms.push_back(std::make_unique<DeadlyPlatform>(position, size, 9999.f, false));
            }
            columnNumber ++;
        }
        lineNumber ++;
    }
    // Add platform that kills the player if it falls into the void
    platforms.push_back(std::make_unique<DeadlyPlatform>(sf::Vector2f(-9999.f, lineNumber * tileSize + 400.f), sf::Vector2f(99999999.f, 10.f), 999999.f, false));
    m_f_levelHeight = lineNumber * tileSize;
    m_f_levelWidth = columnNumber * tileSize;

    sf::Text startMenuText(m_pixelFont, "Inherit the Stars");
    startMenuText.setCharacterSize(60);
    startMenuText.setFillColor(sf::Color::White); 
    startMenuText.setPosition({m_f_levelWidth / 2.f - 1600.f, m_f_levelHeight / 2.f}); // Set text position above the trigger
    m_startMenuTexts.push_back(startMenuText); // Add the text to the vector

    file.close();
}

void Game::_solvePlatformCollisions(Player &player, std::vector<std::unique_ptr<Platform>> &platforms) {
    for (auto& platform : platforms) {
        if (Colisions::checkColision(player, *platform)) {
            
            DeadlyPlatform* deadlyPlatform = dynamic_cast<DeadlyPlatform*>(platform.get());
            if (deadlyPlatform && m_f_playerInvincibilityTime <= 0.f) {
                _playerHit(player, deadlyPlatform->getDamage()); // Player hit by deadly platform
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
        m_soundsManager.playSfxSound("collideWithStar"); // Play sound when player collides with the next level trigger
        _loadPlatformerLevel(nextLevelTrigger.getNextLevelPath(), false, 64.f);

        // Yellow overlay for a split second
        m_Overlay.setColor(sf::Color(255, 255, 0, 120)); // Set yellow overlay color to yellow with full opacity
    }
}

void Game::_deleteCurrentLevel() {
    platforms.clear();
    unlockLevelTriggers.clear();
    enemyWalkers.clear();
    enemyShooters.clear();
}

void Game::_checkUnlockLevelTriggerCollision(Player &player, std::vector<UnlockLevelTrigger> &unlockLevelTriggers) {
    for (size_t i = 0; i < unlockLevelTriggers.size(); ++i) {
        if (Colisions::checkColision(player, unlockLevelTriggers[i])) {
            m_soundsManager.playSfxSound("pickupCoin"); // Play sound when player collects a coin
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
            sf::Sprite heart(m_texturesManager.getHeartTexture());
            heart.setPosition({WINDOW_WIDTH - 150.f - i * 50.f, 5.f});
            heart.setScale({2.f, 2.f});
            heartSprites.push_back(heart);
        }
    }
    else if (health > 50 && health <= 75) {
        heartSprites.clear();
        for(int i = 0; i < 3; i ++) {
            sf::Sprite heart(m_texturesManager.getHeartTexture());
            heart.setPosition({WINDOW_WIDTH - 150.f - i * 50.f, 5.f});
            heart.setScale({2.f, 2.f});
            heartSprites.push_back(heart);
        }
    }
    else if (health > 25 && health <= 50) {
        heartSprites.clear();
        for(int i = 0; i < 2; i ++) {
            sf::Sprite heart(m_texturesManager.getHeartTexture());
            heart.setPosition({WINDOW_WIDTH - 150.f - i * 50.f, 5.f});
            heart.setScale({2.f, 2.f});
            heartSprites.push_back(heart);
        }
    }
    else if (health > 0 && health <= 25) {
        heartSprites.clear();
        for(int i = 0; i < 1; i ++) {
            sf::Sprite heart(m_texturesManager.getHeartTexture());
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

            if (player.getVerticalSpeed() > 0.f) {
                // Player jumps on the enemy
                player.setVerticalSpeed(std::max(-player.getVerticalSpeed() * 1.3f, -25.f)); // Bounce off the enemy
                enemyWalker.setTakeDamageTimer(); // Set the take damage timer to 0.2 seconds
                continue; // Skip the rest of the loop
            } 
            if (m_f_playerInvincibilityTime > 0.f) {
                // Player is invincible, ignore the hit
                continue;
            }
            _playerHit(player, enemyWalker.getDamage()); // Player hit by enemy
        }
    }


    for (auto & enemyShooter : enemyShooters) {
        for (size_t i = 0; i < enemyShooter.m_bullets.size(); ++ i) {
            Bullet& bullet = enemyShooter.m_bullets[i];
            if (Colisions::checkColision(player, bullet)) {
                if (m_f_playerInvincibilityTime > 0.f) {
                    // Player is invincible, ignore the hit
                    continue;
                }
                _playerHit(player, bullet.getDamage()); // Player hit by bullet
                enemyShooter.m_bullets.erase(enemyShooter.m_bullets.begin() + i); // Remove the bullet from the vector
                i --;
            }
        }
    }
}

void Game::_moveEnemyWalkers(std::vector<EnemyWalker> &enemyWalkers, std::vector<std::unique_ptr<Platform>> &platforms) {
    for (auto& enemyWalker : enemyWalkers) {
        enemyWalker.walk();
        enemyWalker.updateTakeDamageTimer(1.f / 60.f); // Update the take damage timer
        // Check if the enemy walker has a platform to walk on
        bool hasPlatformBelow = false;
        sf::Vector2f edgePosition = enemyWalker.getPosition();

        // Determine the edge position based on the direction
        if (enemyWalker.getDirection().x < 0.f) {
            // Moving left, check the bottom-left corner
            edgePosition.x -= 1.f; // Slightly outside the left edge
        } else {
            // Moving right, check the bottom-right corner
            edgePosition.x += enemyWalker.getWidth() + 1.f; // Slightly outside the right edge
        }
        edgePosition.y += enemyWalker.getHeight() + 1.f; // Slightly below the bottom edge

        // Check if there is a platform below the edge
        for (auto& platform : platforms) {
            if (sf::FloatRect({platform -> getX(), platform ->getY()}, {platform->getWidth(), platform ->getHeight() }).contains(edgePosition)) {
                hasPlatformBelow = true;
                break;
            }
        }

        if (!hasPlatformBelow) {
            enemyWalker.reverseDirection();
            if (enemyWalker.getDirection().x < 0.f) {
                enemyWalker.setTexture(&m_texturesManager.getEnemyWalkerTextureLeft()); // Setam textura inamicului
            } else {
                enemyWalker.setTexture(&m_texturesManager.getEnemyWalkerTextureRight()); // Setam textura inamicului
            }
        }

        for (auto& platform : platforms) {
            if (Colisions::checkColision(enemyWalker, *platform)) {
                enemyWalker.reverseDirection(); // Inversam directia inamicului
                if (enemyWalker.getDirection().x < 0.f) {
                    enemyWalker.setTexture(&m_texturesManager.getEnemyWalkerTextureLeft()); // Setam textura inamicului
                } else {
                    enemyWalker.setTexture(&m_texturesManager.getEnemyWalkerTextureRight()); // Setam textura inamicului
                }
            }
        }
    }
}

void Game::_resetPlayerPositionAndHealth() {
    player.move(player.getLastSpawn());
    player.setHealth(100); // Reset health to 100
    for(int i = 0; i < 3; i ++) {
        sf::Sprite heart(m_texturesManager.getHeartTexture());
        heart.setPosition({5.f + i * 50.f, 5.f});
        heart.setScale({2.f, 2.f});
        heartSprites.push_back(heart);
    }
}

void Game::_updateAnimations() {
    AnimationManager::updateAnimationTimer(); // Update animation timer
    if (AnimationManager::getAnimationTimer() >= 0.1f) { // Check if it's time to update the animation frame
        AnimationManager::setAnimationTimer(0.f); // Reset animation timer

        nextLevelTrigger.setTexture(&m_texturesManager.getNextLevelTriggerTexture(), AnimationManager::getStarAnimationRect()); // Update the texture of the next level trigger
        AnimationManager::nextStarAnimationFrame(); // Update the animation frame for the star

        for (auto& unlockLevelTrigger : unlockLevelTriggers) {
            unlockLevelTrigger.setTexture(&m_texturesManager.getUnlockLevelTriggerTexture(), AnimationManager::getCoinAnimationRect()); // Update the texture of the unlock level trigger
        }
        AnimationManager::nextCoinAnimationFrame(); // Update the animation frame for the coin

        if (m_b_isInStartMenu) {
            for (auto& nLT : nextLevelTriggers) {
                if (nLT.isInteractable())
                    nLT.setTexture(&m_texturesManager.getNextLevelTriggerTexture(), AnimationManager::getStarAnimationRect()); // Update the texture of the next level trigger
            }
        }
    }
}

void Game::_initTextElements() {
    /// Load the font
    if (!m_font.openFromFile("./assets/fonts/airstrikechrome.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    if (!m_pixelFont.openFromFile("./assets/fonts/DePixelHalbfett.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    /// INITIALIZE TEXTS
    m_coinText = sf::Text(m_pixelFont);
    m_coinText.setCharacterSize(30);
    m_coinText.setFillColor(sf::Color(200, 200, 200));
    m_coinText.setPosition({50.f, 45.f});
    m_coinText.setString("Coins: 0 / 0");
    m_deathCountText = sf::Text(m_pixelFont);
    m_deathCountText.setCharacterSize(30);
    m_deathCountText.setFillColor(sf::Color::Red);
    m_deathCountText.setPosition({50.f, 5.f});
    m_deathCountText.setString("Deaths: 0");
    m_levelNumberText = sf::Text(m_pixelFont);
    m_levelNumberText.setCharacterSize(30);
    m_levelNumberText.setFillColor(sf::Color::Black);
    m_levelNumberText.setPosition({50.f, 85.f});

    m_wantToExitText = sf::Text(m_pixelFont);
    m_wantToExitText.setCharacterSize(20);
    m_wantToExitText.setFillColor(sf::Color(200, 200, 200));
    m_wantToExitText.setPosition({WINDOW_WIDTH / 2.f - 300.f, 30.f});

    /// END INITIALIZE TEXTS
}

void Game::_loadChapter(int chapterID) {
    // We determine the level ID
    m_soundsManager.stopAllBackgroundMusic(); // Stop the current background music
    m_soundsManager.playBackgroundMusic("chapter" + std::to_string(chapterID), sf::seconds(4.f)); // Play the chapter music

    int levelID = _getLevelIDFromChapterID(chapterID);

    // We load the level based on the level ID
    _loadPlatformerLevel("./assets/level_layouts/level" + std::to_string(levelID) + ".txt", true, 64.f);
    nextLevelTrigger.setNextLevelID(levelID + 1); // Set the next level ID to the next level
}

int Game::_getLevelIDFromChapterID(int chapterID) const {
    // We determine the level ID based on the chapter ID
    int levelID = -1;
    switch(chapterID) {
        case 1:
            levelID = 0;
            break;
        case 2:
            levelID = 7;
            break;
    }
    return levelID;
}

void Game::_checkStartMenuTriggersCollision(Player &player, std::vector<NextLevelTrigger> &nextLevelTriggers) {
    for (size_t i = 0; i < nextLevelTriggers.size(); ++i) {
        if (Colisions::checkColision(player, nextLevelTriggers[i]) && nextLevelTriggers[i].isInteractable()) {
            m_soundsManager.playSfxSound("selectLevel");
            _loadChapter(nextLevelTriggers[i].getNextLevelID()); // Load the chapter based on the trigger ID
            m_b_isInStartMenu = false; // Exit the start menu
            m_Overlay.setColor(sf::Color(255, 255, 255, 210));
            nextLevelTriggers.clear();
        }
    }
}

void Game::_updateEnemyShooters(std::vector<EnemyShooter> &enemyShooters, Player &player) {
    for (auto& enemyShooter : enemyShooters) {
        sf::Vector2f playerPosition = player.getPosition();
        enemyShooter.turnToPlayer(playerPosition, m_texturesManager.getEnemyShooterLeftTexture(), m_texturesManager.getEnemyShooterRightTexture()); // Turn to player
        enemyShooter.update(playerPosition); // Update the enemy shooter
    }
}

void Game::_playerHit(Player &player, float damage) {
    if (m_f_playerInvincibilityTime <= 0.f) {
        player.setHealth(player.getHealth() - damage);
        m_soundsManager.playSfxSound("hit"); // Play sound when player collides with a deadly platform
        m_f_playerInvincibilityTime = 2.f; // Set invincibility time to 1 second
        m_Overlay.setColor(sf::Color(255, 0, 0, 60)); // Set red overlay color to red with full opacity
    }
}

void Game::_checkEnemyKillAuraCollision(KillAura killAura, std::vector<EnemyShooter> &enemyShooters) {
    for (size_t i = 0; i < enemyShooters.size(); ++i) {
        if (Colisions::checkColision(killAura, enemyShooters[i])) {
            enemyShooters.erase(enemyShooters.begin() + i); // Remove the enemy from the vector
            i --;
        }
    }
}

void Game::_updateKillAura(KillAura &killAura, Player &player) {
    if (player.getAttackTimer() > 0.f) {
        if (player.getAttackTimer() == 0.5) {
            killAura.setIsActive(true); // Set kill aura to active
            m_soundsManager.playSfxSound("killAura"); // Play attack sound
        }
        killAura.setPosition({player.getX() - (killAura.getWidth() - player.getWidth()) / 2.f, player.getY() - (killAura.getHeight() - player.getHeight()) / 2.f}); // Set kill aura position to player position
        killAura.update(1.f / 60.f, player.getPosition()); // Update kill aura
    } else{
        killAura.setPosition({-9999.f, -9999.f}); // Set kill aura position to offscreen
    }
}
