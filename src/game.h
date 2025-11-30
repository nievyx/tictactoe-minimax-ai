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
/// 
/// </summary>
/// <param name="difficulty">
/// 
/// </param>
/// <returns>
///  
/// </returns>
int playGame(Difficulty difficulty);

/// <summary>
/// 
/// </summary>
/// <param name="difficulty">
/// Returns 1 if player wins, 0 if computer wins or -1 for a tie
/// </param>
/// <returns></returns>
bool playAgain(Difficulty difficulty);

/// <summary>
/// Stops *all* audio output 
/// </summary>
void StopMusic();

#endif