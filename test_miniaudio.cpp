#include <iostream>     // for std::cout, std::cin
#include <cstdio>       // for getchar (optional, but good practice)

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

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
    return 0;
}
