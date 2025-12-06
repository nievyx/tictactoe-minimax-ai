//#pragma once
#ifndef GAME_H
#define GAME_H

// Difficulty Settings
enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

/// <summary>
/// Main game loop, Handles initilasing spaces on board, calling checker winner / tie 
/// and calling player / computer moves funcitons as well as displaying boards inbetween
/// moves.
/// </summary>
/// <param name="difficulty">
/// Takes Difficulty level as a parameter.
/// </param>
/// <returns>
///  Returns 0 once complete.
/// </returns>
int playGame(Difficulty difficulty);




#endif