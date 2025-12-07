#pragma once

#include <string>

/// <summary>
/// Initiilises miniAudio engine is initialised. Unless already initialised.
/// Also loads default background music file "theme.mp3".
/// </summary>
/// <returns>
///  true -> Successful
///  false -> Initilisation failed
/// </returns>
bool initAudio();

/// <summary>
/// Plays a non-block, non-looping sound effect from given file name.
/// Checks to see if audio engine is initialised, if not it initialises it first.
/// </summary>
/// <param name="fileName"></param>
void playSoundEffect(const std::string& fileName);


/// <summary>
/// Stops *all* audio output.
/// </summary>
void stopMusicEngine();

/// <summary>
/// Stops background music playback.
/// </summary>
void stopBGMusic();

/// <summary>
/// Loads a new background music file from given file name.
/// If a previous background music was loaded, it stops and unloads it first.
/// </summary>
/// <param name="fileName">
/// Path to an audio file to load as background music.
/// </param>
/// <returns></returns>
bool loadBGMusic(const std::string& fileName);

/// <summary>
/// 
/// </summary>
/// <param name="fileName"></param>
void changeBGMusic(const std::string& fileName);
