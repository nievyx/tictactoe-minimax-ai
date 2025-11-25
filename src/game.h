//#pragma once
#ifndef GAME_H
#define GAME_H

// Difficulty Settings
enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

//

int playGame(Difficulty difficulty);
bool playAgain(Difficulty difficulty);

void StopMusic();

#endif