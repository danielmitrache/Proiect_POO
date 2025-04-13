#ifndef SOUNDSMANAGER_H
#define SOUNDSMANAGER_H

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <iostream>

class SoundsManager {
private:
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers; // Map of sound buffers
    std::unordered_map<std::string, sf::Sound> m_sounds; // Map of sounds
public:
    SoundsManager(); // Constructor
    ~SoundsManager(); // Destructor

    // Load a sound from a file and store it in the map
    void loadSound(const std::string& name, const std::string& filePath);

    // Play a sound by its name
    void playSound(const std::string& name);

    // Stop a sound by its name
    void stopSound(const std::string& name);

    // Set the volume of a sound by its name
    void setVolume(const std::string& name, float volume);
};

#endif