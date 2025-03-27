#ifndef DEADLYPLATFORM_H
#define DEADLYPLATFORM_H
#include "Platform.h"
#include "Killer.h"

class DeadlyPlatform : public Platform, public Killer {
public:
    DeadlyPlatform(const sf::Vector2f& position, const sf::Vector2f& size, float damage);
    ~DeadlyPlatform();

    virtual bool isDeadly() const override;
};

#endif // DEADLYPLATFORM_H