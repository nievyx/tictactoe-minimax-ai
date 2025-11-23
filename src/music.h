#pragma once

// Start the audio system (call this once at the beginning of the program)
bool initMusic();

// Start playing background music (optionally looping)
bool playBackgroundMusic(const char* filePath, bool loop);

// Stop music and shut down audio system (call this once before exiting)
void shutdownMusic();
