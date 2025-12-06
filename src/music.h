#pragma once

#include <string>

/// <summary>
/// Initiilises Mini audio engine and started playing
/// </summary>
/// <returns></returns>
bool initAudio();

/// <summary>
/// 
/// </summary>
/// <param name="fileName"></param>
void playSoundEffect(const std::string& fileName);


/// <summary>
/// Stops *all* audio output 
/// </summary>
void stopMusicEngine();


void stopBGMusic();


bool loadBGMusic(const std::string& fileName);

void changeBGMusic(const std::string& fileName);
