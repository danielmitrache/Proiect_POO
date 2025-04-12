#ifndef TEXTURESMANAGER_H
#define TEXTURESMANAGER_H
#include <SFML/Graphics.hpp>
#include <iostream>
class TexturesManager {
private:
    sf::Texture m_texture_tilesetTexture; // Texture for the tileset
    sf::Texture m_texture_heartTexture; // Texture for the heart
    sf::Texture m_texture_enemyWalkerTexture_left, m_texture_enemyWalkerTexture_right; // Texture for the enemy walker
    sf::Texture m_texture_playerTexture; // Texture for the player
    sf::Texture m_texture_nextLevelTriggerTexture; // Texture for the next level trigger
public:
    TexturesManager();
    ~TexturesManager();

    sf::Texture& getTilesetTexture() { return m_texture_tilesetTexture; }
    sf::Texture& getHeartTexture() { return m_texture_heartTexture; }
    sf::Texture& getEnemyWalkerTextureLeft() { return m_texture_enemyWalkerTexture_left; }
    sf::Texture& getEnemyWalkerTextureRight() { return m_texture_enemyWalkerTexture_right; }
    sf::Texture& getPlayerTexture() { return m_texture_playerTexture; }
    sf::Texture& getNextLevelTriggerTexture() { return m_texture_nextLevelTriggerTexture; }
    void setTilesetTexture(const std::string& path);
    void setHeartTexture(const std::string& path);
    void setEnemyWalkerTextureLeft(const std::string& path);
    void setEnemyWalkerTextureRight(const std::string& path);
    void setPlayerTexture(const std::string& path);
    void setNextLevelTriggerTexture(const std::string& path);

    void loadTextures();
};

#endif // TEXTURESMANAGER_H