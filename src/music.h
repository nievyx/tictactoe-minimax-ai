#pragma once

#include <string>

/// <summary>
/// 
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