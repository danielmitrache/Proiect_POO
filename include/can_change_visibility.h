#ifndef CANCHANGEVISIBILITY_H
#define CANCHANGEVISIBILITY_H

class CanChangeVisibility {
public:
    virtual ~CanChangeVisibility() = default;

    virtual void turnInvisible() = 0;
    virtual void turnVisible() = 0;
};

#endif // CANCHANGEVISIBILITY_H