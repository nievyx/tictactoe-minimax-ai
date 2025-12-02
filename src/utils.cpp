#include <cstdlib>
#include <conio.h>
#include <iostream>
#include "utils.h"

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
|  1 | 2 | 3                  |
| ---+---+-- -                |
|  4 | 5 | 6                  |
| ---+---+---                 |
|  7 | 8 | 9                  |
|                             |
| Try to get 3 in a row!      |
+-----------------------------+
)";
	std::cout << howTo;
}