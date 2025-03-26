#include "../include/Colisions.h"
#include <iostream>

namespace Colisions {
    bool checkColision(Actor& actor1, Actor& actor2) {
        return actor1.getX() < actor2.getX() + actor2.getWidth() &&
               actor1.getX() + actor1.getWidth() > actor2.getX() &&
               actor1.getY() < actor2.getY() + actor2.getHeight() &&
               actor1.getY() + actor1.getHeight() > actor2.getY();
    }
}