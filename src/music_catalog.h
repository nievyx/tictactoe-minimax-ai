#pragma once
#include <string>

enum class MusicTrack {
	THEME,
	INTENSE,
	COUNT //Needs to stay last
};

const std::string& getMusicFilename(MusicTrack);
void nextMusic();
void setMusicTrack(MusicTrack track);

