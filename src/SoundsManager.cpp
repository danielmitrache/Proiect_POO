#include "../include/SoundsManager.h"

SoundsManager::SoundsManager() {
    loadSfxSound("collideWithStar", "./assets/sounds/collideWithStar.wav");
    loadSfxSound("hit", "./assets/sounds/hit.wav");
    loadSfxSound("pickupCoin", "./assets/sounds/pickupCoin.wav");
    loadSfxSound("selectLevel", "./assets/sounds/selectLevel.wav");

    loadBackgroundMusic("mainMenuMusic", "./assets/sounds/mainMenuMusic.ogg");
    loadBackgroundMusic("chapter1", "./assets/sounds/chapter1.ogg");
    loadBackgroundMusic("chapter2", "./assets/sounds/chapter2.ogg");

    setAllSfxSoundsVolume(20.f); // Set default volume for all sounds
    setAllBackgroundMusicVolume(20.f); // Set default volume for all background music
}

SoundsManager::~SoundsManager() {}

void SoundsManager::loadSfxSound(const std::string& name, const std::string& filePath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "Error loading sound: " << filePath << std::endl;
        return;
    }
    m_soundBuffers[name] = buffer; // Store the sound buffer in the map
    // Construct the sound with the buffer and insert into the map
    m_sounds.emplace(name, m_soundBuffers[name]);
}

void SoundsManager::playSfxSound(const std::string& name) {
    auto it = m_sounds.find(name);
    if (it != m_sounds.end()) {
        it->second.play(); // Play the sound
    } else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void SoundsManager::stopSfxSound(const std::string& name) {
    auto it = m_sounds.find(name);
    if (it != m_sounds.end()) {
        it->second.stop(); // Stop the sound
    } else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void SoundsManager::setSfxVolume(const std::string& name, float volume) {
    auto it = m_sounds.find(name);
    if (it != m_sounds.end()) {
        it->second.setVolume(volume); // Set the volume of the sound
    } else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void SoundsManager::setAllSfxSoundsVolume(float volume) {
    for (auto& sound : m_sounds) {
        sound.second.setVolume(volume); // Set the volume of all sounds
    }
}





void SoundsManager::loadBackgroundMusic(const std::string& name, const std::string& filePath) {
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filePath)) {
        std::cerr << "Error loading background music: " << filePath << std::endl;
        return;
    }
    m_backgroundMusics[name] = std::move(music); // Store the unique_ptr in the map
}

void SoundsManager::playBackgroundMusic(const std::string& name, sf::Time loopStart, sf::Time loopCutoff) {
    auto it = m_backgroundMusics.find(name);
    if (it != m_backgroundMusics.end()) {
        sf::Music* music = it->second.get();

        // Set loop points to loop the entire music
        sf::Time duration = music->getDuration();
        music->setLoopPoints({loopStart, duration - loopCutoff}); // Set loop points to avoid a small gap at the end
        music->setLooping(true);
        music->play(); // Play the music
    } else {
        std::cerr << "Background music not found: " << name << std::endl;
    }
}

void SoundsManager::stopBackgroundMusic(const std::string& name) {
    auto it = m_backgroundMusics.find(name);
    if (it != m_backgroundMusics.end()) {
        it->second->stop(); // Stop the music
    } else {
        std::cerr << "Background music not found: " << name << std::endl;
    }
}

void SoundsManager::setBackgroundMusicVolume(const std::string& name, float volume) {
    auto it = m_backgroundMusics.find(name);
    if (it != m_backgroundMusics.end()) {
        it->second->setVolume(volume); // Set the volume of the music
    } else {
        std::cerr << "Background music not found: " << name << std::endl;
    }
}

void SoundsManager::setAllBackgroundMusicVolume(float volume) {
    for (auto& music : m_backgroundMusics) {
        music.second->setVolume(volume); // Set the volume of all background music
    }
}

void SoundsManager::stopAllBackgroundMusic() {
    for (auto& music : m_backgroundMusics) {
        music.second->stop(); // Stop all background music
    }
}