#include "Menu/SoundManager.h"
#include <iostream>

SoundManager::~SoundManager() {}

void SoundManager::UnloadAll() {
    // Unload all sound effects
    for (auto& sfx : soundEffects) {
        UnloadSound(sfx.second);
    }

    // Unload all music streams
    for (auto& music : musics) {
        UnloadMusicStream(music.second);
    }
}

void SoundManager::LoadSounds() {
    const std::string path = "SoundMario\\";

    soundEffects["1-up"] = LoadSound((path + "1-up.wav").c_str());
    soundEffects["bowserfalls"] = LoadSound((path + "bowserfalls.wav").c_str());
    soundEffects["bowserfire"] = LoadSound((path + "bowserfire.wav").c_str());
    soundEffects["breakblock"] = LoadSound((path + "breakblock.wav").c_str());
    soundEffects["bump"] = LoadSound((path + "bump.wav").c_str());
    soundEffects["coin"] = LoadSound((path + "coin.wav").c_str());
    soundEffects["fireball"] = LoadSound((path + "fireball.wav").c_str());
    soundEffects["fireworks"] = LoadSound((path + "fireworks.wav").c_str());
    soundEffects["flagpole"] = LoadSound((path + "flagpole.wav").c_str());
    soundEffects["jump-small"] = LoadSound((path + "jump-small.wav").c_str());
    soundEffects["jump-super"] = LoadSound((path + "jump-super.wav").c_str());
    soundEffects["kick"] = LoadSound((path + "kick.wav").c_str());
    soundEffects["pause"] = LoadSound((path + "pause.wav").c_str());
    soundEffects["pipe"] = LoadSound((path + "pipe.wav").c_str());
    soundEffects["powerup"] = LoadSound((path + "powerup.wav").c_str());
    soundEffects["powerup_appears"] = LoadSound((path + "powerup_appears.wav").c_str());
    soundEffects["stomp"] = LoadSound((path + "stomp.wav").c_str());
    soundEffects["vine"] = LoadSound((path + "vine.wav").c_str());

    SetSFXVolume(sfxVolume);
}

void SoundManager::LoadMusic() {
    const std::string path = "SoundMario\\";

    musics["gameover"] = LoadMusicStream((path + "gameover.wav").c_str());
    musics["mariodie"] = LoadMusicStream((path + "mariodie.wav").c_str());
    musics["warning"] = LoadMusicStream((path + "warning.wav").c_str());
    musics["stage_clear"] = LoadMusicStream((path + "stage_clear.wav").c_str());
    musics["world_clear"] = LoadMusicStream((path + "world_clear.wav").c_str());
    musics["playingMusic"] = LoadMusicStream((path + "playingMusic.mp3").c_str());
    musics["MenuMusic"] = LoadMusicStream((path + "MenuMusic.mp3").c_str());

    SetMusicVol(musicVolume);
}

void SoundManager::PlaySoundEffect(const std::string& name) {
    if (soundEffects.count(name)) {
        SetSoundVolume(soundEffects[name], sfxVolume);
        PlaySound(soundEffects[name]);
    }
    else {
        std::cerr << "[SoundManager] SFX not found: " << name << "\n";
    }
}

void SoundManager::PlayMusic(const std::string& name, bool loop) {
    if (musics.count(name)) {
        if (currentMusic != nullptr) {
            StopMusicStream(*currentMusic);
        }
        currentMusic = &musics[name];
        SetMusicVol( musicVolume);
        PlayMusicStream(*currentMusic);
        isLooping = loop;
    }
    else {
        std::cerr << "[SoundManager] Music not found: " << name << "\n";
    }
}

void SoundManager::PauseMusic() {
    if (currentMusic != nullptr) {
        PauseMusicStream(*currentMusic);
        isPaused = true;
    }
}

void SoundManager::ResumeMusic() {
    if (currentMusic != nullptr) {
        ResumeMusicStream(*currentMusic);
        isPaused = false;
    }
}

void SoundManager::StopMusic() {
    if (currentMusic != nullptr) {
        StopMusicStream(*currentMusic);
        currentMusic = nullptr;
    }
}

void SoundManager::Update() {
    if (currentMusic != nullptr && !isPaused) {
        UpdateMusicStream(*currentMusic);
        if (!IsMusicStreamPlaying(*currentMusic) && isLooping) {
            PlayMusicStream(*currentMusic);
        }
    }
}

void SoundManager::SetSFXVolume(float volume) {
    sfxVolume = volume;
    for (auto& sfx : soundEffects) {
        SetSoundVolume(sfx.second, sfxVolume);
    }
}

void SoundManager::SetMusicVol(float volume) {
    musicVolume = volume;
    for (auto& music : musics) {
        SetMusicVolume(music.second, musicVolume);
    }
    if (currentMusic != nullptr) {
        SetMusicVolume(*currentMusic, musicVolume);
    }
}
