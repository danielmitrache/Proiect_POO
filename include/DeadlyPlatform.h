#ifndef DEADLYPLATFORM_H
#define DEADLYPLATFORM_H
#include "Platform.h"
#include "Killer.h"
#include "CanChangeVisibility.h"	

class DeadlyPlatform : public Platform, public Killer, public CanChangeVisibility {
public:
    DeadlyPlatform(const sf::Vector2f& position, const sf::Vector2f& size, float damage, bool isVisible = true);
    ~DeadlyPlatform();

    virtual bool isDeadly() const override;

    virtual void turnInvisible() override;
    virtual void turnVisible() override;
};

#endif // DEADLYPLATFORM_H