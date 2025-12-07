#include <cstdlib> // For system()
#include <conio.h> // For _getch() on Windows
#include <iostream>
#include "utils.h"
#include "music.h"
//Below used for credits scrolling.
#include <vector>
#include <string> 
#include <Windows.h>

//Clears console screen, compatible with Windows and Linux.
void clearScreen(){
	#ifdef _WIN32
		system("cls"); //Windows
	#else
		system("clear"); //Linux / Unix
	#endif
}
// Pauses console window, Prints waits for user input.
void waitForKey() {
	system("pause");
}

//Windows specific implementation using conio.h _getch()
char getKey() {
	return _getch();
}
// Thanks user for playing and exits program.
void exitGame() {
	std::cout << "Thanks for playing!\n"; //Prints exit message
	stopMusicEngine(); // Stops all audio playback
    exit(0);
}
// Prints a simple instruction screen on how to play the game.
void howToPlay() {
	std::string howTo= R"(
+-----------------------------+
| HOW TO PLAY                 |
+-----------------------------+
| Enter a number 1-9 to       |
| place your move.            |
|                             |
| Mapped after numpad on      |
| large keyboard.             |
|                             |
|  7 | 8 | 9                  |
| ---+---+---                 |
|  4 | 5 | 6                  |
| ---+---+---                 |
|  1 | 2 | 3                  |
|                             |
| Try to get 3 in a row!      |
+-----------------------------+
)";
	std::cout << howTo;
}

// Displays scrolling credits in the console.
void showCredits()
{
    const std::string spacing(11, ' '); // A space charcter times by an amount
	//Static vector of strings to hold each line of the credits.
    std::vector<std::string> credits = {
        BLUE    "==============================================================",
        YELLOW  "|                       CREDITS                              |",                    
        BLUE    "==============================================================",
        "",
        std::string(GREEN) +  // Wrap GREEN in std::string() when concatenating (can't do GREEN + spacing).
        spacing+"Tic-Tac-Toe Minimax",
        "",
        spacing + "Programming",
        spacing + "Niamh (github.com/nievyx)",
        "",
        spacing + "AI Logic",
        spacing + "Niamh (github.com/nievyx)",
        "",
        spacing + "Special Thanks",
        spacing + "BrosCode (YouTube Tutorials) — helpful resources",
        spacing + "Stack Overflow Community",
        spacing + "Pixabay (Royality free music)",
        spacing + "miniAudio Engine (Audio Playback)",
        spacing + "Lee Holroyd - Tutor",
        "",
        "",
        spacing + "Thanks for playing!"
    };

	// Console dimensions and frame delay
    const int consoleHeight = 20;   // How many lines on the screen
    const int frameDelay = 120;     // Delays between scroll steps

    // Start credits below the screen (so they scroll up into view)
	// Begin from consoleHeight and go to negative size of credits
    for (int offset = consoleHeight; offset >= -static_cast<int>(credits.size()); --offset) {
		clearScreen(); // Clear Screen between each frame to simulate scrolling

        // Print one window od the credit at correct offset
        for (int i = 0; i < consoleHeight; ++i) {
			// Calculate the index in the credits vector to print
            int index = i - offset;

            // Only print valid lines; otherwise print a blacnk line.
            if (index >= 0 && index < static_cast<int>(credits.size())) {
				// Print the credit line
                std::cout << credits[index] << "\n";
            }
            else {
				std::cout << "\n"; // Print emplty line to ensure window height remains constant
            }
        }
        // Pause between frames to control scroll speed
        Sleep(frameDelay); 
    }
}

