#include <iostream>
//link to game.cpp
#include <limits>
#include "game.h"
#include "debug.h"


void showMenu() {
    std::cout << R"(
  __  .__                                  __                 
_/  |_|__| ____   ____________    ____   _/  |_  ____   ____  
\   __\  |/ ___\  \_  __ \__  \ _/ ___\  \   __\/  _ \_/ __ \ 
 |  | |  \  \___   |  | \// __ \\  \___   |  | (  <_> )  ___/ 
 |__| |__|\___  >  |__|  (____  /\___  >  |__|  \____/ \___  >
              \/              \/     \/                    \/ 
    )";
    std::cout << R"(
==============================================================
                          MAIN MENU
==============================================================
1) Play
2) Stats
3) Exit
)";
}

void handleMenuChoice(int choice) {
    switch (choice) {
    case 1:
        std::cout << "Starting game......\n";
        playGame();
        break;

    case 2:
        std::cout << "\n";
        break;

    case 3:
        std::cout << "\n";
        break;

    case 4:
        std::cout << "\n";
        runDebug();
        break;

        //missing default
    }
}

void runMenu() {
    int choice = 0;

    showMenu();
    while (choice < 3) {
        std::cin >> choice;
        handleMenuChoice(choice);
    }

}

int main() {
    runMenu();

    return 0;
}