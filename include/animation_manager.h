#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace Animation_Manager {
    extern const std::vector<sf::IntRect> m_starAnimationRects;
    extern const std::vector<sf::IntRect> m_coinAnimationRects;
    extern int m_i_starAnimationIndex, m_i_coinAnimationIndex;
    extern float m_f_animationTimer;

    void updateAnimationTimer();
    float getAnimationTimer();
    void setAnimationTimer(float timer);
    void nextStarAnimationFrame();
    void nextCoinAnimationFrame();
    sf::IntRect getStarAnimationRect();
    sf::IntRect getCoinAnimationRect();
};

#endif // ANIMATIONMANAGER_H