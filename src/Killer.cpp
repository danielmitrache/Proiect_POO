#include "../include/killer.h"

Killer::Killer() 
    : m_f_damage(0.f) {}

Killer::Killer(float damage)
    : m_f_damage(damage) {}

Killer::~Killer() {}

void Killer::setDamage(float damage) {
    m_f_damage = damage;
}

float Killer::getDamage() const {
    return m_f_damage;
}