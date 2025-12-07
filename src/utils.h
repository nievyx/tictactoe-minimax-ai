#pragma once

// Set Colors for console output.
// Only works on terminals that support ANSI escape codes.
#include <string>
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"

/// <summary>
/// Clear terminal screen. Compatible with Windows and Linux Machines.
/// </summary>
void clearScreen();

/// <summary>
/// Pauses screen and waits for a user input. Windows only.
/// </summary>
void waitForKey();

/// <summary>
/// Reads a single input without needing the user to press Enter. Windows only.
/// </summary>
/// <returns>The Character from user inputs</returns>
char getKey();

/// <summary>
/// Thanks user for playing and terminates program.
/// Also Stops all audio playback from the engine.
/// </summary>
void exitGame();

/// <summary>
/// Prints instructions on how to play the game to the console.
/// </summary>
void howToPlay();


/// <summary>
/// Displays scrolling credits in the console.
/// </summary>
void showCredits();