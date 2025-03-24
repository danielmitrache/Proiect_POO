#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>

class Actor {
private:
    float m_f_x, m_f_y;
    float m_f_width, m_f_height;
    bool m_b_hasGravity = false;
    float m_f_gravity = 5.0f;
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

    void setHasGravity(bool hasGravity);
    void setGravity(float gravity);
    bool getHasGravity() const;
    float getGravity() const;

    virtual void applyGravity();
};

#endif // ACTOR_H