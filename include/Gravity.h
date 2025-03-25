#ifndef GRAVITY_H
#define GRAVITY_H

#include <SFML/Graphics.hpp>

class Gravity {
protected:
    float m_f_gravity = 7.f;
    bool m_b_hasGravity = true;
public:
    virtual void applyGravity() = 0;

    bool getHasGravity() const;
    void setHasGravity(bool hasGravity);
};

#endif // GRAVITY_H