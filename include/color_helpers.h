#ifndef COLORHELPERS_H
#define COLORHELPERS_H

#include <SFML/Graphics.hpp>

namespace Color_Helpers {
    // Function to convert a hex color string to an sf::Color object
    sf::Color hsvToRgb(float hue, float saturation, float value);

    // Function that blends two colors
    sf::Color blendColors(const sf::Color& original, const sf::Color& overlay, float intensity);
}

#endif // COLORHELPERS_H