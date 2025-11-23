// music.cpp
#define MINIAUDIO_IMPLEMENTATION      // important: only in ONE .cpp file
#include "miniaudio.h"

#include "music.h"
#include <iostream>

// These are "global" inside this file only
static ma_engine gEngine;
static ma_sound gMusic;
static bool gAudioReady = false;
static bool gMusicLoaded = false;

bool initMusic() {
    if (gAudioReady) {
        return true; // already initialised
    }

    ma_result result = ma_engine_init(nullptr, &gEngine);
    if (result != MA_SUCCESS) {
        std::cout << "Failed to initialize audio engine. Error code: "
            << result << "\n";
        return false;
    }

    gAudioReady = true;
    return true;
}

bool playBackgroundMusic(const char* filePath, bool loop) {
    if (!gAudioReady) {
        std::cout << "Audio engine not initialised!\n";
        return false;
    }

    // If music was already loaded, unload it first
    if (gMusicLoaded) {
        ma_sound_uninit(&gMusic);
        gMusicLoaded = false;
    }

    ma_result result = ma_sound_init_from_file(
        &gEngine,
        filePath,
        0,
        nullptr,
        nullptr,
        &gMusic
    );

    if (result != MA_SUCCESS) {
        std::cout << "Failed to load music file '" << filePath
            << "'. Error code: " << result << "\n";
        return false;
    }

    ma_sound_set_looping(&gMusic, loop ? MA_TRUE : MA_FALSE);
    ma_sound_start(&gMusic);
    gMusicLoaded = true;

    return true;
}

void shutdownMusic() {
    if (gMusicLoaded) {
        ma_sound_uninit(&gMusic);
        gMusicLoaded = false;
    }

    if (gAudioReady) {
        ma_engine_uninit(&gEngine);
        gAudioReady = false;
    }
}
