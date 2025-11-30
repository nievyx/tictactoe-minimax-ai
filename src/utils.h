#pragma once

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