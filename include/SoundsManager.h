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

    std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_backgroundMusics; // Use unique_ptr for sf::Music
public:
    SoundsManager(); // Constructor
    ~SoundsManager(); // Destructor


    /// Sound Effects Functions ///

    // Load a sound from a file and store it in the map
    void loadSfxSound(const std::string& name, const std::string& filePath);

    // Play a sound by its name
    void playSfxSound(const std::string& name);

    // Stop a sound by its name
    void stopSfxSound(const std::string& name);

    // Set the volume of a sound by its name
    void setSfxVolume(const std::string& name, float volume);

    // Set the volume of all sounds
    void setAllSfxSoundsVolume(float volume);


    /// Background Music Functions ///

    // Load background music from a file and store it in the map
    void loadBackgroundMusic(const std::string& name, const std::string& filePath);

    // Play background music by its name
    void playBackgroundMusic(const std::string& name);

    // Stop background music by its name
    void stopBackgroundMusic(const std::string& name);

    // Set the volume of background music by its name
    void setBackgroundMusicVolume(const std::string& name, float volume);

    // Set the volume of all background music
    void setAllBackgroundMusicVolume(float volume);

    // Stop all background music
    void stopAllBackgroundMusic();
};

#endif