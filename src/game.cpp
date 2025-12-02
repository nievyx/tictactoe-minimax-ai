#include <iostream>
#include <ctime>
#include <cctype>
#include "game.h"
#include <cstdlib>

//Utilites 
#include "utils.h"
//Minimax AI
#include <vector>

void drawBoard(char* spaces);
void showInputAndDrawBoard(char* spaces);
void playerMove(char* spaces, char player);
void computerMoveEasy(char* spaces, char player);
void computerMoveMinimax(char* spaces, char player, char computer);
void computerMoveMedium(char* spaces, char player, char computer);
bool checkWinner(char* spaces, char player, char computer);
bool checkTie(char* spaces);
int playGame(Difficulty difficulty);

//Modular Music
#include "music.h"

//Music
/*#include "miniaudio.h"     
extern ma_engine engine;  */ 


//This wil stop all audio
//void StopMusic() {
//    ma_engine_stop(&engine);
//}
//
//
//void PlayBGMusic() {
//    ma_result r = ma_engine_play_sound(&engine, "theme.mp3", NULL);
//}
//
//
//
//void playSoundEffect(const std::string& fileName) {
//    ma_engine_play_sound(&engine, fileName.c_str(), NULL);
//}

//Minimax AI
std::vector<int> getAvailableMoves(char* spaces);
int minimax(char* spaces, char player, char computer, bool isMaximising);


int playGame(Difficulty difficulty) {

    char spaces[9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };
    char player = 'X';
    char computer = 'O';
    bool running = true;
    

    //Clear screen
    clearScreen();

    howToPlay();//#DEBUG
    drawBoard(spaces); //Print board, for the first time
    showInputAndDrawBoard(spaces);

    while (running) {
        playerMove(spaces, player); //Player move, player will always play first
        

        drawBoard(spaces); //Reflect changes
        if (checkWinner(spaces, player, computer)) {
            running = false;
            clearScreen();
            break;
        }
        else if (checkTie(spaces)) {
            running = false;
            //clearScreen();
            break;

        }


        //Clear screen
        clearScreen();


        switch (difficulty) {
        case HARD:
            computerMoveMinimax(spaces, player, computer); //Computer move
            break;
        case EASY:
            computerMoveEasy(spaces, computer);
            break;
        case MEDIUM:
            computerMoveMedium(spaces, player, computer);

        }
        drawBoard(spaces); //Prints board to reflect changes
        showInputAndDrawBoard(spaces); 

        if (checkWinner(spaces, player, computer)) {
            running = false;
            break;
        }
        else if (checkTie(spaces)) {
            running = false;
            break;
        }
    }
    std::cout << "Thanks for playing!\n";
   
    return 0;
}


//Colours (Adds colour to 'X's and 'O's, as well as available spaces)
std::string colour(char c) {
    //Players character
    if (c == 'X')
        return BLUE + std::string(1, c) + RESET;
    //AI's character
    if (c == 'O')
        return RED + std::string(1, c) + RESET;
    //Availble spaces
    if (c >= '1' && c <= '9')
        return YELLOW + std::string(1, c) + RESET;

    //Anything else
    return std::string(1, c);

}





void drawBoard(char* spaces) {
    const std::string borderColour = YELLOW; 
    const std::string border = borderColour + "||"+ RESET;
    std::cout << '\n';
    std::cout << borderColour << "+====GAME BOARD=====+" << RESET <<"\n";
    std::cout << border << "     |     |     " << border <<'\n';
    std::cout << border <<"  " << colour(spaces[0]) << "  |  " << colour(spaces[1]) << "  |  " << colour(spaces[2]) << "  " << border << '\n';
    std::cout << border << "_____|_____|_____" << border << '\n';
    std::cout << border << "     |     |     " << border << '\n';
    std::cout << border << "  " << colour(spaces[3]) << "  |  " << colour(spaces[4]) << "  |  " << colour(spaces[5]) << "  " << border << '\n';
    std::cout << border << "_____|_____|_____" << border << '\n';
    std::cout << border << "     |     |     " << border << '\n';
    std::cout << border << "  " << colour(spaces[6]) << "  |  " << colour(spaces[7]) << "  |  " << colour(spaces[8]) << "  " << border << '\n';
    std::cout << border <<"     |     |     " << border << '\n';
    std::cout << borderColour << "+===================+" << RESET << "\n";
    std::cout << '\n';
}

void showInputAndDrawBoard(char* spaces) {
    // temp array doesn't modify the real board, shows possible moves with corresponding numbers
    char display[9];

    //Flip index to match keyboard numpad. for ease of playing.
    const char indexToNumpad[9] = {
        '7','8','9','4','5','6','1','2','3'
    };


    for (int i = 0; i < 9; i++) {
        // This line chooses what to display in each square:
        // If spaces[i] is empty (' '), we show a number (1–9) so the player knows which key to press
        // if empty, show numbers 1–9
        if (spaces[i] == ' ') {
            display[i] = indexToNumpad[i];    // convert 0→'1', 1→'2', ... 8→'9'
        }
        else {
            display[i] = spaces[i];  // keep X or O
        }
    }
    const std::string borderColour = BLUE;
    const std::string border = borderColour + "||" + RESET;
    std::cout << '\n';
    std::cout << borderColour << "+==MOVE REFERENCE===+" << RESET << "\n";
    std::cout << border << "     |     |     " << border << "\n";
    std::cout << border << "  " << colour(display[0]) << "  |  " << colour(display[1]) << "  |  " << colour(display[2]) << "  " << border << '\n';
    std::cout << border << "_____|_____|_____"<< border << '\n';
    std::cout << border << "     |     |     " << border << '\n';
    std::cout << border << "  " << colour(display[3]) << "  |  " << colour(display[4]) << "  |  " << colour(display[5]) << "  " << border << '\n';
    std::cout << border << "_____|_____|_____" << border << '\n';
    std::cout << border << "     |     |     " << border << '\n';
    std::cout << border << "  " << colour(display[6]) << "  |  " << colour(display[7]) << "  |  " << colour(display[8]) << "  " << border << '\n';
    std::cout << border << "     |     |     " << border << '\n';
    std::cout << borderColour << "+===================+" << RESET << '\n';
}
//New way (number correspond with numpad.
void playerMove(char* spaces, char player) {
    int number; //user will enter a number between 1 and 9

    int numpadToIndex[10] = { //Converts index to match keyboard numpad
        -1, // Not used
        6,7,8,
        3,4,5,
        0,1,2
    };
    while (true) {
        std::cout << "Enter a place to play (1-9): ";
        
        char key = getKey();

        // Validate input
        if (key < '1' || key > '9') {
            std::cout << "Invalid input! Enter a place to play (1-9): ";
            continue;
        }
        int number = key - '0';
        int index = numpadToIndex[number];
        if (spaces[index] == ' ') { //if space isn't occupied
            spaces[index] = player; // now equals player marker
            playSoundEffect("placemove.mp3"); //Play sound effect after player places 'X'
            break;
        }
        else {
            std::cout << "That spaces is already taken.\n";
        }
    }
}

//Easy Mode
void computerMoveEasy(char* spaces, char computer) {
    int number;
    srand(time(0));

    while (true) {
        number = rand() % 9; // number will be random between 0 and 8
        if (spaces[number] == ' ') {
            spaces[number] = computer; //computers marker
            break; //if successful will break

        }
    }
}


//Medium Mode
void computerMoveMedium(char* spaces, char player, char computer) {
    // Takes a dice roll to decide whether to play a perfect move or play a random move.
    int roll = rand() % 100;
    if (roll < 80) {
        computerMoveMinimax(spaces, player, computer);
    }
    else {
        computerMoveEasy(spaces, computer);
    }

    }

bool checkTie(char* spaces) {
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            return false;
        }

    }
    std::cout << "It's a tie!!\n";
    drawBoard(spaces); //TODO: does this need another drawboard
    playSoundEffect("you_lose.mp3");
    return true;
}

bool checkWinner(char* spaces, char player, char computer) {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // rows
        {0,3,6}, {1,4,7}, {2,5,8}, // columns
        {0,4,8}, {2,4,6}           // diagonals
    };

    for (auto& line : wins) {
        int a = line[0], b = line[1], c = line[2];

        if (spaces[a] != ' ' && spaces[a] == spaces[b] && spaces[b] == spaces[c]) {
            if (spaces[a] == player) {
                std::cout << "You win!\n";
                playSoundEffect("you_win.mp3");
            }
            else {
                std::cout << "You lose!\n";
                playSoundEffect("you_lose.mp3");
            }
            return true;
        }
    }

    return false;
}


//Minimax AI
std::vector<int> getAvailableMoves(char* spaces) {
    std::vector<int> availableMoves; //Python : availableMoves = [] 
    //Only need true false, append to list
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            availableMoves.push_back(i); //Python : availableMoves.append(i)

            //std::cout << "Space " << i << " is available\n"; //TODO: Debug delete this
        }
    }
    return availableMoves;
}

int scoreBoard(char* spaces, char player, char computer) {
    //Return a score based on a current board, to be called as a base case.
    // +10 ai win, 0 tie, -10 player win

    //  Creates an array of winning line combinations
    // 8 for possible winning lines, 3 for the lines boards positions (rows, columns, diagonals)
    int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // rows
        {0,3,6}, {1,4,7},{2,5,8}, //columns
        {0,4,8}, {2,4,6} // diagonals
    };
    // Loop, for each winning line in the wins, treat it as a small array named line.
    for (auto& line : wins) {
        // Extract 3 board positions, a becomes 0, b becomes 1, c becomes 2, Second loop a becomes 3, b becomes 4, c becomes 5 etc.
        int a = line[0], b = line[1], c = line[2];
        // Check if all 3 positions are the same non-empty symbol. (If all 3 are equal and not empty somebody won!)
        if (spaces[a] != ' ' && spaces[a] == spaces[b] && spaces[b] == spaces[c]) {
            //Determine who won
            // Check for if player was winner
            if (spaces[a] == player)
                return -10;
            // If not computer wins
            else
                return 10;
        }
    }
    // If no winner
    return 0;
}

bool isGameOver(char* spaces) {
    //#TODO: Make a shared helper function for logic for checking winner, shared with Scoreboard

    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // rows
        {0,3,6}, {1,4,7}, {2,5,8}, // columns
        {0,4,8}, {2,4,6}           // diagonals
    };

    for (auto& line : wins) {
        int a = line[0], b = line[1], c = line[2];

        //Checks if someone won, doesn't care who!
        if (spaces[a] != ' ' && spaces[a] == spaces[b] && spaces[b] == spaces[c]) {
            return true; // Someone has 3 in a row
        }
    }
    // Check if theres still places to play
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            return false; // no winner, but spaces left, game continues
        }
    }
    // No winner and no spaces left
    return true;
}

void computerMoveMinimax(char* spaces, char player, char computer) {
    //Create new Vector wth al possible moves, will return a list of of playable indexes (0-8)
    std::vector<int> moves = getAvailableMoves(spaces);
    //Tracking Variable
    int bestScore = -1000; //Number starts very low 
    int bestMove = -1; //Starts at -1 bc no move has been chosen yet

    //Loop through every possible move
    for (int move : moves) { // Simulate a move, run minimax, see how good moves was.
        //Create a simulated board for the ai to test each move
        char newSpaces[9];
        for (int i = 0; i < 9; i++) {
            newSpaces[i] = spaces[i]; //newSpaces will be alter, leaving the actual board state the same, until computer has decided best move.
        }
        // Simulate Ai move
        newSpaces[move] = computer; // Ai will play there char on a simulated board. (Actual board left unchanged.)
        // Score the result using minimax, calling function on the simulated board, false means after Ai make a move and human player plays next. Minimax will swich to minimizing mode.
        //Score describes how good or bad a move is, all future moves are then explored recursively.
        int score = minimax(newSpaces, player, computer, false);
        // Get track of score
        // If this moves score is better than any other seen, update best move and store index of move in bestMove
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        } // By the end bestMove will contain the most optimal move to play.
    }
    // Apply best move to real board
    spaces[bestMove] = computer;
}


// TODO: Optimisation: Alpha-beta pruning 
//(it can reduce the time complexity from O(b^d) to O(b^(d/2)), 
//(where b is the branching factor and d is the depth.)

int minimax(char* spaces, char player, char computer, bool isMaximising) {
    // isMaximising = true  → AI turn (maximize score)
    // isMaximising = false → Player turn (minimize score)
    int bestScore;
    std::vector<int> moves;
    //1. Base case: Check if game over, return score
    if (isGameOver(spaces)) {
        return scoreBoard(spaces, player, computer);
    }


    //2. Get all empty positions
    moves = getAvailableMoves(spaces); // Merge with declaration - std::vector<int> moves = getAvailableMoves(spaces);

    // Check if isMaximising (check the boolean) 
    // need to return best
    // 3. Maximising Player (AI)
    if (isMaximising) {
        bestScore = -1000;
        for (int move : moves) {
            char newSpaces[9];
            for (int i = 0; i < 9; i++) {
                // Make copy of the board
                newSpaces[i] = spaces[i];
            }

            newSpaces[move] = computer; //Simulate AI move

            int score = minimax(newSpaces, player, computer, false);

            if (score > bestScore) {
                bestScore = score;
            }

        }
        //Otherwise
        //also return best
        return bestScore;
    }
    //4. Minimizing player (human)
    //Ai imagining what the player could do next
    else {
        bestScore = 1000;

        for (int move : moves) {
            char newSpaces[9];

            for (int i = 0; i < 9; i++) {
                // Make copy of the board
                newSpaces[i] = spaces[i];
            }

            newSpaces[move] = player;

            int score = minimax(newSpaces, player, computer, true);

            if (score < bestScore) {
                bestScore = score;
            }
        }

        return bestScore;
    }
}