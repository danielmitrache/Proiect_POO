#ifndef KILER_H
#define KILER_H

class Killer {
protected:
    float m_f_damage;
public:
    Killer();
    Killer(float damage);
    ~Killer();

    void setDamage(float damage);
    float getDamage() const;
};

#endif // KILER_H