#ifndef GRAVITY_H
#define GRAVITY_H

#include <SFML/Graphics.hpp>

class Gravity {
protected:
    float m_f_gravity = 0.5f;
    bool m_b_hasGravity = true;

    // Purely virtual function that defines how gravity is applied to an object
    virtual void _applyGravity() = 0;
public:
    bool getHasGravity() const;
    void setHasGravity(bool hasGravity);
};

#endif // GRAVITY_H