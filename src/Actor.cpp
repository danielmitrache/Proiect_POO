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

Actor::~Actor() { }

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

float Actor::getWidth() const {
    return m_f_width;
}

float Actor::getHeight() const {
    return m_f_height;
}

void Actor::setWidth(float width) {
    m_f_width = width;
}

void Actor::setHeight(float height) {
    m_f_height = height;
}