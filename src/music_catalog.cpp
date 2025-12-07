//NOTE: Work-in-progress. Not used by the engine yet.
//TODO: Have custom music folder and have a dynamic script to cycle through any .mp3(or wahtever) file in the folder 
#include "music_catalog.h"
#include "music.h"

static const std::string MUSIC_CATALOG[] = {
	"theme.mp3",
	"intense.mp3"
};

static MusicTrack currentTrack = MusicTrack::THEME;

const std::string& getMusicFilename(MusicTrack track)
{
	return MUSIC_CATALOG[static_cast<int>(track)];
}

void setMusicTrack(MusicTrack track)
{
	currentTrack = track;
	changeBGMusic(getMusicFilename(track));
}

void setMusic(MusicTrack track) {
	currentTrack = track;
	changeBGMusic(getMusicFilename(track));
}

void nextMusic()
{
	int index = (int)currentTrack;
	index = index + 1;

	if (index >= (int)MusicTrack::COUNT)
		index = 0;

	setMusic((MusicTrack)index);
}

//TODO: Previous music?