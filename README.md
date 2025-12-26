<!-- 
Planned:
## Running the game (Windows)

A prebuilt Windows executable is available.

To run:
1. Download the `.exe`
2. Place it in the same folder as the `.mp3` audio files
3. Double-click to play

No additional setup is required.
 -->
## File structure

```text
tictactoe-minimax-ai/
├─ src/
│  ├─ main_menu.cpp   # Main menu system and navigation. Program entry point (main)
│
│  ├─ game.cpp        # Core game logic and minimax AI implementation
│  ├─ game.h          # Game state definitions and function declarations
│
│  ├─ music.cpp       # Background music and sound effect handling
│  ├─ music.h
│
│  ├─ miniaudio.h     # Embedded audio library (single-header)
│
│  ├─ utils.cpp       # Helper / utility functions
│  ├─ utils.h
│
│  ├─ debug.cpp       # Debug helpers and experimental / unused functions
│  └─ debug.h         # Debug utilities (e.g. getch wrapper)
│
├─ notes/             # Development notes and scratch material
│
├─ intense.mp3        # Audio assets
├─ music.mp3
├─ placemove.mp3
├─ theme.mp3
├─ you_lose.mp3
├─ you_win.mp3
│
├─ tic_tac_toe_minimax.sln            # Visual Studio solution file
├─ tic_tac_toe_minimax.vcxproj        # Visual Studio C++ project file
├─ tic_tac_toe_minimax.vcxproj.filters
└─ .gitignore
