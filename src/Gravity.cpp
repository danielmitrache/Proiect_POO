#include "../include/Gravity.h" 

bool Gravity::getHasGravity() const {
    return m_b_hasGravity;
}

void Gravity::setHasGravity(bool hasGravity) {
    m_b_hasGravity = hasGravity;
}