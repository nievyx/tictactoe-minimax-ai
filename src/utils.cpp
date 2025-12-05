#include <cstdlib>
#include <conio.h>
#include <iostream>
#include "utils.h"
#include "music.h"


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
|  7 | 8 | 9                  |
| ---+---+-- -                |
|  4 | 5 | 6                  |
| ---+---+---                 |
|  1 | 2 | 3                  |
|                             |
| Try to get 3 in a row!      |
+-----------------------------+
)";
	std::cout << howTo;
}
#include <vector>
//PENDING
void showCredits()
{
    std::vector<std::string> credits = {
        "NIAMH - Os + Xs",
        "",
        "A Tic-Tac-Toe Experience",
        "",
        "Programming",
        "  Your Name",
        "",
        "AI Logic",
        "  Your Name",
        "",
        "Special Thanks",
        "  Stack Overflow Community",
        "",
        "",
        "Thanks for playing!"
    };

    const int consoleHeight = 20;   // visible lines on screen
    const int frameDelay = 120;     // milliseconds per frame

    // Start credits below the screen (so they scroll up into view)
    for (int offset = consoleHeight; offset >= -static_cast<int>(credits.size()); --offset) {
        clearScreen();

        for (int i = 0; i < consoleHeight; ++i) {
            int index = i - offset;
            if (index >= 0 && index < static_cast<int>(credits.size())) {
                std::cout << credits[index] << "\n";
            }
            else {
                std::cout << "\n";
            }
        }

        Sleep(frameDelay);
    }

    std::cout << "\nPress Enter to return...";
    std::cin.get();
}


//PENDING @ whitenite1 @ https://cplusplus.com/forum/beginner/242670/
//This scrolls from side to side wanted, top to bottom
//HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//COORD CursorPosition;
//
//void gotoXY(int x, int y);
//
//int credits()
//{
//	std::string rotating_string = "This is a moving marquee, that shows an IMPORTANT"
//		"message... It could also be a poem, or short story : ";
//		std::string partial_string = "";
//
//	int len = rotating_string.length();
//	char letter_holder;
//
//	do
//	{
//		gotoXY(38, 28);
//		std::string partial_string = "";
//
//		for (int y = 0;y < 30;y++)
//			partial_string += rotating_string[y];
//
//		std::cout << partial_string;
//		Sleep(100);
//		letter_holder = rotating_string[0];
//
//		for (int x = 1; x < len; x++)
//		{
//			rotating_string[x - 1] = rotating_string[x];
//		}
//		rotating_string[len - 1] = letter_holder;
//
//	} while (true);
//
//	return 0;
//}
//
//void gotoXY(int x, int y)
//{
//	CursorPosition.X = x;
//	CursorPosition.Y = y;
//	SetConsoleCursorPosition(console, CursorPosition);
//}