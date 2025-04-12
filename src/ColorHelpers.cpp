#include "../include/ColorHelpers.h"

namespace ColorHelpers {
    // Function to convert a hex color string to an sf::Color object
    sf::Color hsvToRgb(float hue, float saturation, float value) {
        int h = static_cast<int>(hue / 60) % 6;
        float f = (hue / 60) - h;
        float p = value * (1 - saturation);
        float q = value * (1 - f * saturation);
        float t = value * (1 - (1 - f) * saturation);
    
        float r, g, b;
        switch (h) {
            case 0: r = value, g = t, b = p; break;
            case 1: r = q, g = value, b = p; break;
            case 2: r = p, g = value, b = t; break;
            case 3: r = p, g = q, b = value; break;
            case 4: r = t, g = p, b = value; break;
            case 5: r = value, g = p, b = q; break;
        }
    
        return sf::Color(
            static_cast<uint8_t>(r * 255),
            static_cast<uint8_t>(g * 255),
            static_cast<uint8_t>(b * 255)
        );
    }

    // Function that blends two colors
    sf::Color blendColors(const sf::Color& original, const sf::Color& overlay, float intensity){
        sf::Color blendedColor;
        blendedColor.r = static_cast<uint8_t>(original.r * (1 - intensity) + overlay.r * intensity);
        blendedColor.g = static_cast<uint8_t>(original.g * (1 - intensity) + overlay.g * intensity);
        blendedColor.b = static_cast<uint8_t>(original.b * (1 - intensity) + overlay.b * intensity);
        blendedColor.a = original.a; // Keep the original alpha value
        return blendedColor;
    }
}