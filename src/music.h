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
void StopMusic();

//New
void StopBGMusic();

//PENDING
// Switch to a different BGM file (looped).
//void changeBGMusic(const std::string& fileName);