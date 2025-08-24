#pragma once
#include "raylib.h"
#include <map>
#include <string>

class SoundManager {
public:
    // Delete copy constructor and assignment operator
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    // Static method to get the singleton instance
    static SoundManager& GetInstance() {
        static SoundManager instance; // Meyer's Singleton: thread-safe, initialized on first call
        return instance;
    }

    void LoadSounds();
    void LoadMusic();

    void PlaySoundEffect(const std::string& name);
    void PlayMusic(const std::string& name, bool loop = false);
    void StopMusic();
    void StopSoundEffect(const std::string& name);
    void Update();  // Must be called each frame if music is playing

    void SetSFXVolume(float volume);    // 0.0f → 1.0f
    void SetMusicVol(float volume);     // 0.0f → 1.0f

    float GetSFXVolume() const { return sfxVolume; }
    float GetMusicVolume() const { return musicVolume; }

    void PauseMusic();
    void ResumeMusic();

    bool IsPaused() const { return isPaused; }
    void UnloadAll();

private:
    // Private constructor to prevent direct instantiation
    SoundManager() = default;
    ~SoundManager();

    std::map<std::string, Sound> soundEffects;
    std::map<std::string, Music> musics;
    Music* currentMusic = nullptr;
    bool isLooping = false;
    bool isPaused = false;
    float sfxVolume = 0.5f;
    float musicVolume = 0.3f;
};