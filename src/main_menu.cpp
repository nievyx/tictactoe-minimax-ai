#include <iostream>
#include <windows.h>
#include <limits>
#include "game.h"
#include "debug.h"
#include "utils.h"
#include "music.h" 
#include "music_catalog.h" //New

Difficulty currentDifficulty = HARD;
void toggleDifficulty(Difficulty& currentDifficulty);


static const char* difficultyToString(Difficulty diff) {
    switch (diff) {
    case EASY: return "\033[32mEASY\033[34m  "; //GREEN
    case MEDIUM: return "\033[33mMEDIUM\033[34m"; //YELLOW
    case HARD: return "\033[31mHARD\033[34m  "; //RED
    default: return "An error has occured!";
    }
}

static void showMenu() {
    clearScreen();
    std::string menuText =
        std::string("\033[31m") + R"(
  __  .__           __                     __                 
_/  |_|__| ____   _/  |______    ____    _/  |_  ____   ____  
\   __\  |/ ___\  \   __\__  \ _/ ___\   \   __\/  _ \_/ __ \ 
 |  | |  \  \___   |  |  / __ \\  \___    |  | (  <_> )  ___/ 
 |__| |__|\___  >  |__|  (____  /\___  >  |__|  \____/ \___  >
              \/              \/     \/                    \/ 
          _____  .__       .__                       
         /     \ |__| ____ |__| _____ _____  ___  ___
        /  \ /  \|  |/    \|  |/     \\__  \ \  \/  /
       /    Y    \  |   |  \  |  Y Y  \/ __ \_>    < 
       \____|__  /__|___|  /__|__|_|  (____  /__/\_ \
               \/        \/         \/     \/      \/

)" +

BLUE R"(
==============================================================
|                         )" + YELLOW "DESCRIPTION" BLUE + R"(                        |
==============================================================
|The AI in this game uses the Minimax algorithm, a perfect-  | 
|play search algorithm that looks ahead at all possible      |
|moves and counter-moves to guarantee that it never loses.   |
==============================================================
|                          )" + YELLOW "MAIN MENU" + BLUE R"(                         |
==============================================================
|1) Play                                                     |
|2) Difficulty: )" + difficultyToString(currentDifficulty) + R"(                                       |
|3) How to play                                              |
|4) Show Credits                                             |
|5) Exit                                                     |
==============================================================
)" + RESET; // Reset color

    std::cout << menuText;
}

static bool playAgain(Difficulty difficulty) {
    char choice; //TODO: Don't think choice is being used anymore.

    std::cout << "Play Again? [y/n] \n";

    while (true) {
        char key = std::tolower(getKey());

        if (key == 'y') {
            return true;
        }
        if (key == 'n') {
            return false; 
        }
        std::cout << "Invalid input. Please enter 'y' or 'n'";
    }
}

static void handleMenuChoice(int choice) {
    switch (choice) {
        case 1: //Plays games
            std::cout << "Starting game......\n";
            while (true) {
                playGame(currentDifficulty);
                if (!playAgain(currentDifficulty))
                    break;
            }
            showMenu();
            break;

        case 2: //Toggle Difficulty
            toggleDifficulty(currentDifficulty);
            break;

        case 3: //Print How to Play
            std::cout << "\n";
            showMenu();
            howToPlay();
            break;

        case 4: //Open Credits 
            std::cout << "\n";
            showCredits();
            showMenu();
            break;

        case 5: //Exits game
            std::cout << "\n";
            exitGame();

        // Braces create a scope so we can declare variables in this case
        case 6: { //Hidden: Change Background Music
            std::cout << "\nEnter music file name (e.g. theme.mp3): ";

            std::string fileName;
            //Request file name from user.
			std::cin >> fileName;

            changeBGMusic(fileName);

            showMenu();
            break;
        }
        //case 7: //Open Hidden Debug Menu
        //    std::cout << "\n";
        //    runDebug();
        //    break;

        default:
            
            //Reprint main menu showing off new difficulty selected //TODO: does this do this? No! it does not! (its inside toggle diff)
            showMenu();

            std::cout << "Choose an option between 1 and 5\n";
            break;
    }
}

static void runMenu() {

    showMenu();

    while (true) {

        char key = getKey();
        
        // This works because program is comparing chars and not strings. (char of '0' has an ASCII number of 48 while 3 has an ASCII number of 51)
        // Validate input
        if (key < '1' || key > '6') {
            std::cout <<"Invalid choice!";
            showMenu();     
            continue;
        }


        int choice = key - '0';

        handleMenuChoice(choice);
    }
}

void toggleDifficulty(Difficulty& diff) {
    if (diff == EASY)
        diff = MEDIUM;
    else if (diff == MEDIUM)
        diff = HARD;
    else
        diff = EASY;
    

    //Reprint main menu showing off new difficulty selected
    showMenu();
     
}


int main() {
    initAudio();
    runMenu();

    return 0;
}