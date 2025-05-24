#include <SFML/Graphics.hpp>
#include "actor.h"
#include "gravity.h"
#include <iostream>
#ifndef PLAYER_H
#define PLAYER_H

enum class PlayerMode {
    Platformer,
    WASD
};

class Player : public Actor, public sf::Drawable, public Gravity {
private:
    sf::RectangleShape m_shape;
    float m_f_speed = 7.0f; // Speed of the player

    float m_f_verticalSpeed = 0.0f; // Vertical speed of the player
    float m_f_horizontalSpeed = 0.0f; // Horizontal speed of the player

    float m_f_jumpForce = 13.0f; // Jump force
    bool m_b_canJump = false;

    PlayerMode m_playerMode = PlayerMode::Platformer;

    sf::Vector2f m_v2f_lastSpawn{0.f, 0.f}; // Last spawn position

    float m_f_health = 100.f; // Health of the player

    /////////////////////////////

    // Texture for the player
    sf::Texture* m_texture;


    ///////////////////////////////

    // Attack
    bool m_b_canAttack = false;
    float m_f_attackCooldown = 5.f; // Attack cooldown
    float m_f_attackTimer = 0.f; // Attack timer
public:
    Player();
    Player(sf::Vector2f position);
    Player(sf::Vector2f position, sf::Texture* texture);
    ~Player();

    // Draw the payer
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Update the player position and speed based on the input
    void update();

    // Move the player to the given position (move both the shape and the actor)
    void move(sf::Vector2f position);

    float getVerticalSpeed();
    void setVerticalSpeed(float verticalSpeed);

    float getHorizontalSpeed();
    void setHorizontalSpeed(float horizontalSpeed);

    sf::Vector2f getLastSpawn() const;
    void setLastSpawn(sf::Vector2f lastSpawn);

    /// JUMPING ///
    bool getCanJump() const;
    void setCanJump(bool canJump);

    /// PLAYER MODE ///
    void setMode(PlayerMode mode);
    PlayerMode getMode() const;

    /// PLAYER HEALTH ///
    void setHealth(float health);
    float getHealth() const;

    /// PLAYER TEXTURE ///
    void setTexture(sf::Texture* texture);
    void setColor(sf::Color color);

    void setCanAttack(bool canAttack);
    bool getCanAttack() const;

    void setAttackCooldown(float attackCooldown);
    float getAttackCooldown() const;

    float getAttackTimer() const;
private:
    /// JUMPING ///
    // If it can jump, apply the jump force
    void _jump();

    /// GRAVITY ///
    // Apply gravity to the player
    void _applyGravity() override;
};

#endif // PLAYER_H