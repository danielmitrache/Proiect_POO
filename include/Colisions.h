#ifndef COLISIONS_H
#define COLISIONS_H
#include <SFML/Graphics.hpp>
#include "actor.h"

namespace Colisions {
    // Function that checks whether two actors are colliding
    bool checkColision(Actor& actor1, Actor& actor2);
}

#endif // COLISIONS_H