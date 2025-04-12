#include "../include/TexturesManager.h"

TexturesManager::TexturesManager() {
    loadTextures();
}

TexturesManager::~TexturesManager() {}

void TexturesManager::loadTextures() {
    if (!m_texture_tilesetTexture.loadFromFile("D:/ProiectPOO/assets/textures/tileset_new.png")) {
        std::cerr << "Error loading tileset texture!" << std::endl;
    }
    if (!m_texture_heartTexture.loadFromFile("D:/ProiectPOO/assets/textures/heart.png")) {
        std::cerr << "Error loading heart texture" << std::endl;
    }
    if (!m_texture_enemyWalkerTexture_left.loadFromFile("D:/ProiectPOO/assets/textures/enemy_left.png")) {
        std::cerr << "Error loading enemy walker left texture" << std::endl;
    }
    if (!m_texture_enemyWalkerTexture_right.loadFromFile("D:/ProiectPOO/assets/textures/enemy_right.png")) {
        std::cerr << "Error loading enemy walker right texture" << std::endl;
    }
    if (!m_texture_playerTexture.loadFromFile("D:/ProiectPOO/assets/textures/player_heart.png")) {
        std::cerr << "Error loading player texture" << std::endl;
    }
    if (!m_texture_nextLevelTriggerTexture.loadFromFile("D:/ProiectPOO/assets/textures/star.png")) {
        std::cerr << "Error loading next level trigger texture" << std::endl;
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