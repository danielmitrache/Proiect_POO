#include "../include/AnimationManager.h"

namespace AnimationManager {
    const std::vector<sf::IntRect> m_starAnimationRects = {
        sf::IntRect({0, 0}, {32, 32}),
        sf::IntRect({32, 0}, {32, 32}),
        sf::IntRect({64, 0}, {32, 32}),
        sf::IntRect({96, 0}, {32, 32})
    };

    const std::vector<sf::IntRect> m_coinAnimationRects = {
        sf::IntRect({0, 36}, {18, 18}),
        sf::IntRect({18, 36}, {18, 18}),
        sf::IntRect({36, 36}, {18, 18}),
        sf::IntRect({54, 36}, {18, 18}),
        sf::IntRect({72, 36}, {18, 18}),
        sf::IntRect({90, 36}, {18, 18})
    };

    int m_i_starAnimationIndex = 0, m_i_coinAnimationIndex = 0;
    float m_f_animationTimer = 0.f;

    void updateAnimationTimer() {
        m_f_animationTimer += 1.f / 60.f;
    }

    float getAnimationTimer() {
        return m_f_animationTimer;
    }

    void setAnimationTimer(float timer) {
        m_f_animationTimer = timer;
    }

    void nextStarAnimationFrame() {
        m_i_starAnimationIndex = (m_i_starAnimationIndex + 1) % m_starAnimationRects.size();
    }

    void nextCoinAnimationFrame() {
        m_i_coinAnimationIndex = (m_i_coinAnimationIndex + 1) % m_coinAnimationRects.size();
    }

    sf::IntRect getStarAnimationRect() {
        return m_starAnimationRects[m_i_starAnimationIndex];
    }

    sf::IntRect getCoinAnimationRect() {
        return m_coinAnimationRects[m_i_coinAnimationIndex];
    }
}