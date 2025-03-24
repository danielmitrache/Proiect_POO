#ifndef COLISIONS_H
#define COLISIONS_H
#include <SFML/Graphics.hpp>
#include "Actor.h"

namespace Colisions {
    bool checkColision(Actor& actor1, Actor& actor2);
}

#endif // COLISIONS_H