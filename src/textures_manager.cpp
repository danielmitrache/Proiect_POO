#include "../include/textures_manager.h"

// Definirea membrilor statici
sf::Texture TexturesManager::m_texture_tilesetTexture;
sf::Texture TexturesManager::m_texture_heartTexture;
sf::Texture TexturesManager::m_texture_enemyWalkerTexture_left;
sf::Texture TexturesManager::m_texture_enemyWalkerTexture_right;
sf::Texture TexturesManager::m_texture_playerTexture;
sf::Texture TexturesManager::m_texture_nextLevelTriggerTexture;
sf::Texture TexturesManager::m_texture_unlockLevelTriggerTexture;
sf::Texture TexturesManager::m_texture_enemyWalkerTexture;
sf::Texture TexturesManager::m_texture_enemyShooterTexture_right;
sf::Texture TexturesManager::m_texture_enemyShooterTexture_left;
sf::Texture TexturesManager::m_killAuraTexture;
sf::Texture TexturesManager::m_enemyChaserTexture;

TexturesManager::TexturesManager() {
    loadTextures();
}

TexturesManager::~TexturesManager() {}

void TexturesManager::loadTextures() {
    if (!m_texture_tilesetTexture.loadFromFile("./assets/textures/tileset_new.png")) {
        std::cerr << "Error loading tileset texture!" << std::endl;
    }
    if (!m_texture_heartTexture.loadFromFile("./assets/textures/heart.png")) {
        std::cerr << "Error loading heart texture" << std::endl;
    }
    if (!m_texture_enemyWalkerTexture_left.loadFromFile("./assets/textures/enemy.png")) {
        std::cerr << "Error loading enemy walker left texture" << std::endl;
    }
    if (!m_texture_enemyWalkerTexture_right.loadFromFile("./assets/textures/enemy.png")) {
        std::cerr << "Error loading enemy walker right texture" << std::endl;
    }
    if (!m_texture_playerTexture.loadFromFile("./assets/textures/player_heart.png")) {
        std::cerr << "Error loading player texture" << std::endl;
    }
    if (!m_texture_nextLevelTriggerTexture.loadFromFile("./assets/textures/star.png")) {
        std::cerr << "Error loading next level trigger texture" << std::endl;
    }
    if (!m_texture_unlockLevelTriggerTexture.loadFromFile("./assets/textures/coins.png")) {
        std::cerr << "Error loading unlock level trigger texture" << std::endl;
    }
    if (!m_texture_enemyShooterTexture_right.loadFromFile("./assets/textures/shootingEnemy.png")) {
        std::cerr << "Error loading enemy shooter texture" << std::endl;
    }
    if (!m_texture_enemyShooterTexture_left.loadFromFile("./assets/textures/shootingEnemyLeft.png")) {
        std::cerr << "Error loading enemy shooter left texture" << std::endl;
    }
    if (!m_killAuraTexture.loadFromFile("./assets/textures/killAura.png")) {
        std::cerr << "Error loading kill aura texture" << std::endl;
    }
    if (!m_enemyChaserTexture.loadFromFile("./assets/textures/enemyChaser.png")) {
        std::cerr << "Error loading enemy chaser texture" << std::endl;
    }
}

void TexturesManager::setTilesetTexture(const std::string& path) {
    if (!m_texture_tilesetTexture.loadFromFile(path)) {
        std::cerr << "Error loading tileset texture from: " << path << std::endl;
    }
}

void TexturesManager::setHeartTexture(const std::string& path) {
    if (!m_texture_heartTexture.loadFromFile(path)) {
        std::cerr << "Error loading heart texture from: " << path << std::endl;
    }
}

void TexturesManager::setEnemyWalkerTextureLeft(const std::string& path) {
    if (!m_texture_enemyWalkerTexture_left.loadFromFile(path)) {
        std::cerr << "Error loading enemy walker left texture from: " << path << std::endl;
    }
}

void TexturesManager::setEnemyWalkerTextureRight(const std::string& path) {
    if (!m_texture_enemyWalkerTexture_right.loadFromFile(path)) {
        std::cerr << "Error loading enemy walker right texture from: " << path << std::endl;
    }
}

void TexturesManager::setPlayerTexture(const std::string& path) {
    if (!m_texture_playerTexture.loadFromFile(path)) {
        std::cerr << "Error loading player texture from: " << path << std::endl;
    }
}

void TexturesManager::setNextLevelTriggerTexture(const std::string& path) {
    if (!m_texture_nextLevelTriggerTexture.loadFromFile(path)) {
        std::cerr << "Error loading next level trigger texture from: " << path << std::endl;
    }
}

void TexturesManager::setUnlockLevelTriggerTexture(const std::string& path) {
    if (!m_texture_unlockLevelTriggerTexture.loadFromFile(path)) {
        std::cerr << "Error loading unlock level trigger texture from: " << path << std::endl;
    }
}

void TexturesManager::setEnemyShooterRightTexture(const std::string& path) {
    if (!m_texture_enemyShooterTexture_right.loadFromFile(path)) {
        std::cerr << "Error loading enemy shooter texture from: " << path << std::endl;
    }
}

void TexturesManager::setEnemyShooterLeftTexture(const std::string& path) {
    if (!m_texture_enemyShooterTexture_left.loadFromFile(path)) {
        std::cerr << "Error loading enemy shooter left texture from: " << path << std::endl;
    }
}

void TexturesManager::setKillAuraTexture(const std::string& path) {
    if (!m_killAuraTexture.loadFromFile(path)) {
        std::cerr << "Error loading kill aura texture from: " << path << std::endl;
    }
}

void TexturesManager::setEnemyChaserTexture(const std::string& path) {
    if (!m_enemyChaserTexture.loadFromFile(path)) {
        std::cerr << "Error loading enemy chaser texture from: " << path << std::endl;
    }
}