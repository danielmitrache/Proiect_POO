#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>

class Actor {
private:
    float m_f_x, m_f_y;
public:
    Actor();
    Actor(float x, float y);
    ~Actor();
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);    
};

#endif // ACTOR_H