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

//Wrking
void StopBGMusic();

//PENDING
//TODO: Make static??
bool loadBGMusic(const std::string& fileName);






//IDEAS
// Switch to a different BGM file (looped).
//void changeBGMusic(const std::string& fileName);