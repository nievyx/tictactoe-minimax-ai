//music
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <iostream>
#include <string>
#include "music.h"

static ma_engine gEngine;
static ma_sound gBgm; //gbgm can be set to anything
static bool gAudioInitialised = false;
static bool gBGMLoaded = false;

bool initAudio()
	{
		if (gAudioInitialised) {
			return true;
		}
	// 
	ma_result result = ma_engine_init(nullptr, &gEngine);
	if (result != MA_SUCCESS) {
		std::cout << "Music Engine failed to initialise! Error code : " << (int)result << "\n";
		return false;
	 }

	//Load Background Music
	result = ma_sound_init_from_file(&gEngine, "theme.mp3", 0, nullptr, nullptr, &gBgm);
	if (result != MA_SUCCESS) {
		std::cout << "Failed to load theme.mp3. Error code: " << (int)result << "\n";
		ma_engine_uninit(&gEngine);
		return false;
	}

	gBGMLoaded = true;
	// Loop it forever
	ma_sound_set_looping(&gBgm, MA_TRUE);

	// Start playback
	ma_sound_start(&gBgm);

	gAudioInitialised = true;
	return true;
}

void playSoundEffect(const std::string& fileName) {
	if (!gAudioInitialised) return; 
		ma_engine_play_sound(&gEngine, fileName.c_str(), nullptr);
}

void StopMusic()
{
	if (gAudioInitialised) {
		ma_engine_stop(&gEngine);
	}
}

//New
void StopBGMusic()
{
	if (gAudioInitialised && gBGMLoaded) {
		ma_sound_stop(&gBgm);
	}
}