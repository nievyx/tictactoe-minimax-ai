#include <cstdlib>
#include <conio.h>
#include <iostream>
#include "utils.h"
#include "music.h"
#include <vector>//Credits


//Credits
#include <string>
#include <Windows.h>

void clearScreen(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void waitForKey() {
	system("pause");
}

char getKey() {
	return _getch();
}

void exitGame() {
    std::cout << "Thanks for playing!\n";
	stopMusicEngine();
    exit(0);
}

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
//PENDING
void showCredits()
{
    const std::string spacing(20, ' '); // A space charcter times my an amount
    std::vector<std::string> credits = {
        BLUE"==============================================================",
        YELLOW"                       CREDITS",
        BLUE"==============================================================",
        "",
        std::string(GREEN) +  // Wrap GREEN in std::string() when concatenating (can't do GREEN + spacing).
        spacing + "NIAMH - Os + Xs",
        "",
        spacing+"A Tic-Tac-Toe Experience",
        "",
        spacing + "Programming",
        spacing + "Your Name",
        "",
        spacing + "AI Logic",
        spacing + "Your Name",
        "",
        spacing + "Special Thanks",
        spacing + "Stack Overflow Community",
        "",
        "",
        spacing + "Thanks for playing!"
    };

    const int consoleHeight = 20;   // How many lines on the screen
    const int frameDelay = 120;     // Delays between scroll steps

    // Start credits below the screen (so they scroll up into view)
    for (int offset = consoleHeight; offset >= -static_cast<int>(credits.size()); --offset) {
        clearScreen(); // Clear Screen between each frame

        // Print one window od the credit at correct offset
        for (int i = 0; i < consoleHeight; ++i) {
            int index = i - offset;

            // Only print valid lines; otherwise print empty spaces
            if (index >= 0 && index < static_cast<int>(credits.size())) {
                std::cout << credits[index] << "\n";
            }
            else {
                std::cout << "\n";
            }
        }

        Sleep(frameDelay); // Pause between frames to control scroll speed
    }
}

