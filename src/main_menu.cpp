#include <iostream>
#include <windows.h>
#include <limits>
#include "game.h"
#include "debug.h"
#include "utils.h"

//music
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
ma_engine engine;
ma_sound bgm;  

Difficulty currentDifficulty = HARD;
void toggleDifficulty(Difficulty& currentDifficulty);


const char* difficultyToString(Difficulty diff) {
    switch (diff) {
    case EASY: return "\033[32mEASY\033[34m  "; //GREEN
    case MEDIUM: return "\033[33mMEDIUM\033[34m"; //YELLOW
    case HARD: return "\033[31mHARD\033[34m  "; //RED
    default: return "An error has occured!";
    }
}

void showMenu() {
    std::cout << "\033[31m";//RED
    std::cout << R"(
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

    )";
    std::cout << "\033[34m";//BLUE
    std::cout << R"(
==============================================================
|                         )";std::cout << "\033[33mDESCRIPTION\033[34m"; //YELLOW + BLUE
    std::cout << R"(                        |
==============================================================
|The AI in this game uses the Minimax algorithm, a perfect-  | 
|play search algorithm that looks ahead at all possible      |
|moves and counter-moves to guarantee that it never loses.   |
==============================================================
|                          )";std::cout << "\033[33mMAIN MENU\033[34m"; //YELLOW + BLUE
    std::cout << R"(                         |
==============================================================
|1) Play                                                     |
|2) Difficulty: )";std::cout << difficultyToString(currentDifficulty); std::cout << R"(                                       |
|3) Exit                                                     |
==============================================================
)"; 
    std::cout << "\033[0m";//RESET TO WHITE
}

bool playAgain(Difficulty difficulty) {
    char choice;

    std::cout << "Play Again? [y/n] \n";

    while (true) {
        std::cin >> choice;
        choice = std::tolower(choice);

        if (choice == 'y') {
            return true;
        }
        if (choice == 'n') {

            return false; 
        }
        std::cout << "Invalid input. Please enter 'y' or 'n'";
    }
}

void handleMenuChoice(int choice) {
    switch (choice) {
        case 1: //Plays games
            std::cout << "Starting game......\n";
            while (true) {
                playGame(currentDifficulty);
                if (!playAgain(currentDifficulty))
                    break;
            }

            clearScreen();
            showMenu();
            break;

        case 2: //Toggle Difficulty
            toggleDifficulty(currentDifficulty);
            break;

        case 3: //Exits game
            std::cout << "\n";
            exit(0);

        case 4: //Open Hidden Debug Menu
            std::cout << "\n";
            runDebug();
            break;

        default:
            clearScreen();
            //Reprint main menu showing off new difficulty selected //TODO: does this do this?
            showMenu();

            std::cout << "Choose an option between 1 and 3\n";
            break;
    }
}

void runMenu() {

    showMenu();

    while (true) {

        char key = getKey();
        
        // This works because program is comparing chars and not strings. (char of '0' has an ASCII number of 48 while 3 has an ASCII number of 51)
        // Validate input
        if (key < '1' || key > '4') {
            std::cout <<"Invalid choice!";
            clearScreen();  //TODO:  This is block if printed alot!
            showMenu();     //       Fix by clearing screen inside show menu
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
    

    //Clear Screen
    clearScreen();
    //Reprint main menu showing off new difficulty selected
    showMenu();
     
}

int play(ma_engine* engine) {
    ma_result result;

    // Initialize the music as a sound object
    result = ma_sound_init_from_file(engine, "theme.mp3", 0, NULL, NULL, &bgm);
    if (result != MA_SUCCESS) {
        std::cout << "Failed to load theme.mp3. Error: " << (int)result << "\n";
        return result;
    }

    // Loop it forever
    ma_sound_set_looping(&bgm, MA_TRUE);

    // Start playback
    ma_sound_start(&bgm);

    return MA_SUCCESS;
}

int main() {
    //TODO: make a ma_engine_init for this to live in.
    //Initialise Sound
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cout << "ma_engine_init failed. Error code: " << (int)result << "\n";
        return -1;
    }
    play(&engine);

    runMenu();
        
    // TODO: Cleanup audio (these lines might never be reached
    //       because exit(0) is called in handleMenuChoice -> case 3).
    ma_sound_uninit(&bgm);

    ma_engine_uninit(&engine);
    return 0;
}