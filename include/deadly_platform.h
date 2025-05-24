#ifndef DEADLYPLATFORM_H
#define DEADLYPLATFORM_H
#include "platform.h"
#include "killer.h"
#include "can_change_visibility.h"	

class DeadlyPlatform : public Platform, public Killer, public CanChangeVisibility {
public:
    DeadlyPlatform(const sf::Vector2f& position, const sf::Vector2f& size, float damage, bool isVisible = true);
    DeadlyPlatform(const sf::Vector2f& position, const sf::Vector2f& size, float damage, sf::Texture* texture, const sf::IntRect& textureRect, bool isVisible = true);
    ~DeadlyPlatform();

    virtual void turnInvisible() override;
    virtual void turnVisible() override; 
};

#endif // DEADLYPLATFORM_H