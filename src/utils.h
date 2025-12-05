#pragma once

// Set Colors
#include <string>
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"

/// <summary>
/// Clear terminal screen. Compatible with Windows and Linux Machines.
/// </summary>
void clearScreen();

/// <summary>
/// Pauses screen and waits for a user input.
/// </summary>
void waitForKey();

/// <summary>
/// Reads a single input without needing the user to press Enter.
/// </summary>
/// <returns>The Character from user inputs</returns>
char getKey();

/// <summary>
/// Thanks user for playing and terminates program.
/// Also Stops all audio playback from the engine
/// </summary>
void exitGame();

void howToPlay();

//Credits
//void gotoXY(int x, int y);
//int credits();

void showCredits();