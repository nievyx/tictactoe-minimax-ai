#include <iostream>
//link to game.cpp
#include <limits>
#include "game.h"
#include "debug.h"

//music
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

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

    ma_engine engine;

    // 1) Init engine
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cout << "Failed to initialize engine. Error code: " << result << "\n";
        return -1;
    }

    // 2) Try to play sound
    result = ma_engine_play_sound(&engine, "music.mp3", NULL);
    //result = ma_engine_play_sound(&engine, "C:/Users/Niamh/projects/tic_tac_toe_minimax/x64/Debug/music.mp3", NULL);
    if (result != MA_SUCCESS) {
        std::cout << "Failed to play sound (check file path!). Error code: " << result << "\n";
        ma_engine_uninit(&engine);
        return -1;
    }

    std::cout << "Playing music.mp3 ... press Enter to quit.\n";

    // Use std::cin.get() twice in case there's a leftover newline
    std::cin.get();
    if (std::cin.peek() == '\n')
        std::cin.get();

    ma_engine_uninit(&engine);
    //return 0;


    runMenu();

    return 0;
}