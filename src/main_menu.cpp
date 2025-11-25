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
//
ma_sound bgm;   // <-- add this at the top of the file (global)

Difficulty currentDifficulty = HARD;
void toggleDifficulty(Difficulty& currentDifficulty);


const char* difficultyToString(Difficulty diff) {
    switch (diff) {
    case EASY: return "\033[32mEASY\033[34m"; //GREEN
    case MEDIUM: return "\033[33mMEDIUM\033[34m"; //YELLOW
    case HARD: return "\033[31mHARD\033[34m"; //RED
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
|_) Difficulty: )";std::cout << difficultyToString(currentDifficulty); std::cout << R"(                                           |
|3) Exit                                                     |
==============================================================
)"; //To make box size look good. IDEA: if mode isnt hard or easy add -2 from raw to fit (medium is 2 extra letters)
    std::cout << "\033[0m";//RESET TO WHITE
}

void handleMenuChoice(int choice) {
    switch (choice) {
        case 1: //Plays games
            std::cout << "Starting game......\n";
            playGame(currentDifficulty);
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
            std::cout << "Choose an option between 1 and 3\n";
            break;
    }
}

void runMenu() {
    int choice = 0;


    showMenu();

    while (true) {

        if (!(std::cin >> choice)) {
            // Handle non-numerical inpu
            std::cin.clear(); //Clear error flags
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Discard bad input
            std::cout << "Please enter a number!";
            continue;


        }

        handleMenuChoice(choice);
    }

}
// PENDING
void toggleDifficulty(Difficulty& diff) {
    if (diff == EASY)
        diff == MEDIUM;
    //if diff 0 + 1
    // if diff 1 + 1
    
    // if diff 3 - 3
    //debug message

    //Clear Screen
    clearScreen();
    //Reprint main menu showing off new difficulty selected
    showMenu();
    std::cout << "Difficulty changed, not!";
     
}

//int play(ma_engine* engine) {
//    ma_result result = ma_engine_play_sound(engine, "theme.mp3", NULL);
//    if (result != MA_SUCCESS) {
//        std::cout << "ma_engine_play_sound failed. Error code: " << (int)result << "\n";
//    }
//    return result;
//}
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
    //ma_engine engine;
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cout << "ma_engine_init failed. Error code: " << (int)result << "\n";
        return -1;
    }

    play(&engine);

  
   
    runMenu();
    ma_sound_uninit(&bgm);

    ma_engine_uninit(&engine);
    return 0;
}