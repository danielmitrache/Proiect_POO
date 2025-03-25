#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>

class Actor {
private:
    float m_f_x, m_f_y;
    float m_f_width, m_f_height;
public:
    Actor();
    Actor(float x, float y);
    ~Actor();
    
    float getX() const;
    float getY() const;

    void setX(float x);
    void setY(float y);

    float getWidth() const;
    float getHeight() const;
    
    void setWidth(float width);
    void setHeight(float height);
};

#endif // ACTOR_H