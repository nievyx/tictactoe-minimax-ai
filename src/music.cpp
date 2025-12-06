//music
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <iostream>
#include <string>
#include "music.h"

static ma_engine gEngine;
static ma_sound gBgm; 
static bool gAudioInitialised = false;
static bool gBGMLoaded = false;


bool loadBGMusic(const std::string& fileName);

bool initAudio()
{
	if (gAudioInitialised) {
		return true;
	}
	// // Initialize the Miniaudio engine. This sets up the audio system so the game
	// can play music and sound effects. If initialization fails (e.g., no audio
	// device or driver error), the game continues without sound.
	ma_result result = ma_engine_init(nullptr, &gEngine);
	if (result != MA_SUCCESS) {
		std::cout << "Music Engine failed to initialise! Continuing without sound. Error code : " << (int)result << "\n";
		return false;
	}

	//Set a default music
	if (!loadBGMusic("theme.mp3")) {
		std::cout << "[Audio Warning] Failed to load background music!\n";

	return false;
	}

	gAudioInitialised = true;
	return true;
}

void playSoundEffect(const std::string& fileName) {
	if (!gAudioInitialised) initAudio(); //If music engine not initialised, initiaise it.
		ma_engine_play_sound(&gEngine, fileName.c_str(), nullptr);
}

void stopMusicEngine(){
	if (gAudioInitialised) {
		ma_engine_stop(&gEngine);
	}
}


void stopBGMusic(){
	if (gAudioInitialised && gBGMLoaded) {
		ma_sound_stop(&gBgm);
	}
}


void changeBGMusic(const std::string& fileName){
	if (!gAudioInitialised) {
		if (!initAudio()) return;
	}
	loadBGMusic(fileName);
}

bool loadBGMusic(const std::string& fileName)
{
	if (gBGMLoaded)
	{
		ma_sound_stop(&gBgm);
		ma_sound_uninit(&gBgm);
		gBGMLoaded = false;
	}
	// Load new music
	ma_result result = ma_sound_init_from_file(&gEngine, fileName.c_str(), 0, nullptr, nullptr, &gBgm);

	if (result != MA_SUCCESS) {
		std::cout << "Failed to load file" << fileName <<".Error code : " << (int)result << "\n";
		return false;
	}
	// Loop it forever
	ma_sound_set_looping(&gBgm, MA_TRUE);

	// Start playback
	ma_sound_start(&gBgm);

	return true;
}


