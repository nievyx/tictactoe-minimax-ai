#include <iostream> 
#include <windows.h> 
// Include project headers
#include "game.h"
#include "debug.h"
#include "utils.h"
#include "music.h" 

// Global variable to track current difficulty (Minimax Ai difficulty by default).
// Passed into playGame function when a game is started.
Difficulty currentDifficulty = HARD;

//Forward declarations for helper function that cycles through difficulties.
void toggleDifficulty(Difficulty& currentDifficulty);

// Converts Difficulty enum to coloured string for display in menu.
// Uses ANSI escape codes for colour formatting.
static const char* difficultyToString(Difficulty diff) {
    switch (diff) {
    case EASY: return "\033[32mEASY\033[34m  "; //GREEN
    case MEDIUM: return "\033[33mMEDIUM\033[34m"; //YELLOW
    case HARD: return "\033[31mHARD\033[34m  "; //RED
    default: return "An error has occured!";
    }
}

/// <summary>
/// Renders a main menu to termainal window, with ASCII art and coloured text.
/// Dynamically shows current difficulty setting.
/// This function is called whenever the menu needs to be redrawn.
/// </summary>
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
|5) Change Background Music                                  |
|6) Exit                                                     |
==============================================================
)" + RESET; // Reset color

    std::cout << menuText;
}

/// <summary>
///  Prompts user to play again after a game ends.
/// Uses Getch wrapper getKey() to read single character input without user pressing enter.
/// </summary>
/// <param name="difficulty"></param>
/// <returns>
/// true -> Play again
/// false -> Do not play again
/// </returns>
static bool playAgain(Difficulty difficulty) {
	// NOTE: difficulty parameter is unused but kept for possible future use.
    std::cout << "Play Again? [y/n] \n";

    while (true) {
		//Convert to lowercase for easier comparison
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

/// <summary>
/// Handles user menu choice and calls appropriate functions.
/// </summary>
/// <param name="choice"></param>
static void handleMenuChoice(int choice) {
    switch (choice) {
        case 1: //Plays games
            std::cout << "Starting game......\n";
            while (true) {
				// Start game with current difficulty
                playGame(currentDifficulty);
				// After game ends, prompt user to play again
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


        //Change Background Music
        case 5: { // Braces create a scope so we can declare variables in this case
            std::cout << "\nEnter music file name (e.g. theme.mp3, mario.mp3)\nAdd files to project folder to play : ";

            std::string fileName;
            //Request file name from user.
			std::cin >> fileName;

            changeBGMusic(fileName);

            showMenu();
            break;
        }

        case 6: //Exits game
            std::cout << "\n";
            exitGame();

	    //case 7: //Open Hidden Debug Menu (Currenty disabled)
        //    std::cout << "\n";
        //    runDebug();
        //    break;

        default:
            std::cout << "Choose an option between 1 and 6\n";
            break;
    }
}

/// <summary>
/// Prints menu and handles user input loop.
/// </summary>
static void runMenu() {
	//Prints menu for the first time
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
/// <summary>
/// Cycles through difficulty settings. Abd redraws menu to show updated setting.
/// </summary>
/// <param name="diff"></param>
void toggleDifficulty(Difficulty& diff) {
    if (diff == EASY)
        diff = MEDIUM;
    else if (diff == MEDIUM)
        diff = HARD;
    else
        diff = EASY;
    

	//Immediatly redraw menu to show updated difficulty.
    showMenu();
     
}


int main() {
	// Initialise audio engine, if fails continues without audio.
    initAudio();
	// Start main menu loop
    runMenu();

    return 0;
}