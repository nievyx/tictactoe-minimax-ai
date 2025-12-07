//miniAudio wrapper for playing background music and sound effects in the game.
#define MINIAUDIO_IMPLEMENTATION //Enable miniaudio implementation, can only be defined in one source file.
#include "miniaudio.h" //Single file audio playback library.

#include <iostream>
#include <string> // std::string, std::cout. Used for file names and console output.
#include "music.h" //

// Global audio engine and background music sound objects
static ma_engine gEngine;
static ma_sound gBgm; 
// Flags to track audio initialization and background music loading status
static bool gAudioInitialised = false; //Set to false initially, set to true once audio engine is initialised.
static bool gBGMLoaded = false; //Set to true once background music is loaded successfully.

// Forward declaration 
bool loadBGMusic(const std::string& fileName);

/// Initializes the audio engine and loads default background music.
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
//Play a sound effect from a given file name. Initialises audio engine if not already initialised.
void playSoundEffect(const std::string& fileName) {
	if (!gAudioInitialised) initAudio(); //If music engine not initialised, initiaise it.
		ma_engine_play_sound(&gEngine, fileName.c_str(), nullptr);
}
/// Stops all audio output from the music engine.
void stopMusicEngine(){
	if (gAudioInitialised) {
		ma_engine_stop(&gEngine);
	}
}

// Stops background music playback.
void stopBGMusic(){
	if (gAudioInitialised && gBGMLoaded) {
		ma_sound_stop(&gBgm);
	}
}

// Changes background music to a given filename.
void changeBGMusic(const std::string& fileName){
	if (!gAudioInitialised) {
		if (!initAudio()) return; //If engine fails to initialise, silently exit function.
	}
	loadBGMusic(fileName);
}
// Loads background music from a specified file.
bool loadBGMusic(const std::string& fileName)
{
	if (gBGMLoaded) // If we have existing BGM loaded, stop and unload it first.
	{
		ma_sound_stop(&gBgm); // Stop playback
		ma_sound_uninit(&gBgm); // Uninitialize sound object
		gBGMLoaded = false; // Mark as unloaded
	}
	// Load new music
	ma_result result = ma_sound_init_from_file(&gEngine, fileName.c_str(), 0, nullptr, nullptr, &gBgm);

	// Checks for loading errors 
	if (result != MA_SUCCESS) {
		std::cout << "Failed to load file" << fileName <<".Error code : " << (int)result << "\n";
		return false;
	}
	// Loop it forever
	ma_sound_set_looping(&gBgm, MA_TRUE);

	// Start playback
	ma_sound_start(&gBgm);

	// Mark that we now have a valid, initialized BGM!!
	gBGMLoaded = true;

	// Successful load
	return true;
}


