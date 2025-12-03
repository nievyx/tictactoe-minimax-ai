//music
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <iostream>
#include <string>
#include "music.h"

static ma_engine gEngine;
static ma_sound gBgm; //names here can be set to anything
static bool gAudioInitialised = false;
static bool gBGMLoaded = false;


bool loadBGMusic(const std::string& fileName);

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

	//Set a default music
	if (!loadBGMusic("theme.mp3")) {
		ma_engine_uninit(&gEngine);
	return false;
	}



	//change so music can be changed in game
	////////////////////////////////////////////////////
	////Load Background Music
	
	//result = ma_sound_init_from_file(&gEngine, "theme.mp3", 0, nullptr, nullptr, &gBgm);
	//if (result != MA_SUCCESS) {
	//	std::cout << "Failed to load theme.mp3. Error code: " << (int)result << "\n";
	//	ma_engine_uninit(&gEngine);
	//	return false;
	//}

	//gBGMLoaded = true;
	//// Loop it forever
	//ma_sound_set_looping(&gBgm, MA_TRUE);

	//// Start playback
	//ma_sound_start(&gBgm);
	
	////////////////////////////////////////////////////

	gAudioInitialised = true;
	return true;
}

void playSoundEffect(const std::string& fileName) {
	if (!gAudioInitialised) initAudio(); //Changed from return
		ma_engine_play_sound(&gEngine, fileName.c_str(), nullptr);
}
// Working
void StopMusic()
{
	if (gAudioInitialised) {
		ma_engine_stop(&gEngine);
	}
}


//Working
void StopBGMusic()
{
	if (gAudioInitialised && gBGMLoaded) {
		ma_sound_stop(&gBgm);
	}
}


void changeBGMusic(const std::string& fileName)
{
	if (!gAudioInitialised) {
		if (!initAudio()) return;
	}
	loadBGMusic(fileName);
		

}

//TODO: Make static??
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


