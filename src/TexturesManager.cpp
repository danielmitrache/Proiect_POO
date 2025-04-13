#include "../include/TexturesManager.h"

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
