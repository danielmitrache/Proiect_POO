#include "../include/Actor.h"
#include <iostream>

Actor::Actor() {
    m_f_x = 0.0f;
    m_f_y = 0.0f;
}

Actor::Actor(float x, float y) {
    m_f_x = x;
    m_f_y = y;
}

Actor::~Actor() {
    std::cout << "Actor destroyed" << std::endl;   
}

float Actor::getX() const {
    return m_f_x;
}

float Actor::getY() const {
    return m_f_y;
}

void Actor::setX(float x) {
    m_f_x = x;
}

void Actor::setY(float y) {
    m_f_y = y;
}