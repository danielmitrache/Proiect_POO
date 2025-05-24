#ifndef TEXTURESMANAGER_H
#define TEXTURESMANAGER_H
#include <SFML/Graphics.hpp>
#include <iostream>
class TexturesManager {
private:
    // We declare the textures as static members so they can be shared across all instances of TexturesManager
    // This way we avoid loading the same texture multiple times
    static sf::Texture m_texture_tilesetTexture; // Texture for the tileset
    static sf::Texture m_texture_heartTexture; // Texture for the heart
    static sf::Texture m_texture_enemyWalkerTexture_left, m_texture_enemyWalkerTexture_right; // Texture for the enemy walker
    static sf::Texture m_texture_playerTexture; // Texture for the player
    static sf::Texture m_texture_nextLevelTriggerTexture; // Texture for the next level trigger
    static sf::Texture m_texture_unlockLevelTriggerTexture; // Texture for the unlock level trigger
    static sf::Texture m_texture_enemyWalkerTexture; // Texture for the enemy walker (default)
    static sf::Texture m_texture_enemyShooterTexture_right; // Texture for the enemy shooter
    static sf::Texture m_texture_enemyShooterTexture_left; // Texture for the enemy shooter (left)
    static sf::Texture m_killAuraTexture; // Texture for the kill aura
    static sf::Texture m_enemyChaserTexture; // Texture for the enemy chaser

public:
    TexturesManager();
    ~TexturesManager();

    sf::Texture& getTilesetTexture() { return m_texture_tilesetTexture; }
    sf::Texture& getHeartTexture() { return m_texture_heartTexture; }
    sf::Texture& getEnemyWalkerTextureLeft() { return m_texture_enemyWalkerTexture_left; }
    sf::Texture& getEnemyWalkerTextureRight() { return m_texture_enemyWalkerTexture_right; }
    sf::Texture& getPlayerTexture() { return m_texture_playerTexture; }
    sf::Texture& getNextLevelTriggerTexture() { return m_texture_nextLevelTriggerTexture; }
    sf::Texture& getUnlockLevelTriggerTexture() { return m_texture_unlockLevelTriggerTexture; }
    sf::Texture& getEnemyShooterRightTexture() { return m_texture_enemyShooterTexture_right; }
    sf::Texture& getEnemyShooterLeftTexture() { return m_texture_enemyShooterTexture_left; } 
    sf::Texture& getKillAuraTexture() { return m_killAuraTexture; }
    sf::Texture& getEnemyChaserTexture() { return m_enemyChaserTexture; }
    void setTilesetTexture(const std::string& path);
    void setHeartTexture(const std::string& path);
    void setEnemyWalkerTextureLeft(const std::string& path);
    void setEnemyWalkerTextureRight(const std::string& path);
    void setPlayerTexture(const std::string& path);
    void setNextLevelTriggerTexture(const std::string& path);
    void setUnlockLevelTriggerTexture(const std::string& path);
    void setEnemyShooterRightTexture(const std::string& path);
    void setEnemyShooterLeftTexture(const std::string& path);
    void setKillAuraTexture(const std::string& path);
    void setEnemyChaserTexture(const std::string& path);

    void loadTextures();
};

#endif // TEXTURESMANAGER_H