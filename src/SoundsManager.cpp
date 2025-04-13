#include "../include/SoundsManager.h"

SoundsManager::SoundsManager() {
    loadSound("collideWithStar", "./assets/sounds/collideWithStar.wav");
    loadSound("hit", "./assets/sounds/hit.wav");
    loadSound("pickupCoin", "./assets/sounds/pickupCoin.wav");
    loadSound("selectLevel", "./assets/sounds/selectLevel.wav");
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
}

SoundsManager::~SoundsManager() {}

void SoundsManager::loadSound(const std::string& name, const std::string& filePath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "Error loading sound: " << filePath << std::endl;
        return;
    }
    m_soundBuffers[name] = buffer; // Store the sound buffer in the map
    // Construct the sound with the buffer and insert into the map
    m_sounds.emplace(name, m_soundBuffers[name]);
}

void SoundsManager::playSound(const std::string& name) {
    auto it = m_sounds.find(name);
    if (it != m_sounds.end()) {
        it->second.play(); // Play the sound
    } else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void SoundsManager::stopSound(const std::string& name) {
    auto it = m_sounds.find(name);
    if (it != m_sounds.end()) {
        it->second.stop(); // Stop the sound
    } else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void SoundsManager::setVolume(const std::string& name, float volume) {
    auto it = m_sounds.find(name);
    if (it != m_sounds.end()) {
        it->second.setVolume(volume); // Set the volume of the sound
    } else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}