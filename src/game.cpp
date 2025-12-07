#include <iostream> // std::cout, std::string output
#include <ctime> // std::time for random seed
#include <cctype> //std::tolower
#include "music.h" // playSoundEffect, audio functions
#include "game.h" // Difficulty enum, playGame function prototype
#include <cstdlib> // std::rand, std::srand
#include "utils.h" //Utilites - for console colours and clearScreen etc.
#include <vector> // Minimax Ai - std::vector for dynamic arrays
 
//Forward declarations, these allow the program to know these functions exist before they are defined later in the file.
//A pointer to a char array representing the board spaces is used throughout.
//This allows functions to directly modify the board state without creating a copy.
void drawBoard(char* spaces);
void showInputAndDrawBoard(char* spaces);
void playerMove(char* spaces, char player);
void computerMoveEasy(char* spaces, char player);
void computerMoveMinimax(char* spaces, char player, char computer);
void computerMoveMedium(char* spaces, char player, char computer);
bool checkWinner(char* spaces, char player, char computer);
bool checkTie(char* spaces);
int playGame(Difficulty difficulty);

//Minimax AI helper functions
std::vector<int> getAvailableMoves(char* spaces);
int minimax(char* spaces, char player, char computer, bool isMaximising);

// Entry point for main game loop, called from main menu, board initialised here.
int playGame(Difficulty difficulty) {
    
	//1D array to represent board spaces, initialised to empty spaces
    char spaces[9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };
    char player = 'X';
    char computer = 'O';

    bool running = true;
    
	//Clear screen beofre drawing initial board
    clearScreen();

    //Print board, for the first time
    drawBoard(spaces); 
	//Board with input reference
    showInputAndDrawBoard(spaces);

	//Main game loop: Alternate between player and computer moves until win/tie
    while (running) {

        //Player move, player will always play first
        playerMove(spaces, player); 
        
        //Reflect changes
        drawBoard(spaces); 

		//Run check winner function and if false is returned continue game loop otherwise break loop
        if (checkWinner(spaces, player, computer)) {
			running = false; // Returns false to end game loop
			break; //Break out of while loop, a break statement immediately terminates the nearest enclosing loop. Otherwise program continues to next iteration of loop.
        }
		// Check for tie
        else if (checkTie(spaces)) {
            running = false;
            break;

        }

		//Clear screen before computer move
        clearScreen();

		//Switch case for different difficulty levels
        switch (difficulty) {
        case HARD:
			// Minimax Algorithm AI Move
            computerMoveMinimax(spaces, player, computer); 
            break;
        case EASY:
			// Random Move AI
            computerMoveEasy(spaces, computer);
            break;
        case MEDIUM:
			// Mix of Random and Minimax AI, determined in function by a dice roll
            computerMoveMedium(spaces, player, computer);
            // no break statement, is needed tdue to having no default case or anymore cases below.
        }

        //Prints board to reflect changes
        drawBoard(spaces); 
        showInputAndDrawBoard(spaces); 

		//Check winner block again after computer move
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
//Returns a string wrapped in an ASCII colour code.
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

//Renders current state of the game board to the console.
// Uses ASCII characters to draw the board and places Xs and Os in their respective positions.
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

// Prints a second board with references to the input numbers for player moves.
// Creates a temp array, doesn't modify the real board, shows possible moves with corresponding numbers.
void showInputAndDrawBoard(char* spaces) {
    char display[9];

    //Flip index to match keyboard numpad. for ease of playing.
    const char indexToNumpad[9] = {
        '7','8','9','4','5','6','1','2','3'
    };

	// Populate display either with current X/O or with number reference if empty.
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

//Takes player input and updates the board state accordingly.
//Number correspond with numpad.
void playerMove(char* spaces, char player) {
    int number; //user will enter a number between 1 and 9

    //Converts index to match keyboard numpad
	//Lookup table for numpad to array index
    int numpadToIndex[10] = { 
        -1, // Not used
        6,7,8,
        3,4,5,
        0,1,2
    };
    while (true) {
        std::cout << "Enter a place to play (1-9): ";
        
		//getKey() from utils.h, takes a simgle character without user need to press enter.
        char key = getKey();

		// Validate input via a range check on ASCII values for chars '1' to '9'
        if (key < '1' || key > '9') {
            std::cout << "Invalid input! Enter a place to play (1-9): ";
            continue;
        }
		//Convert char to int
        int number = key - '0';
		//Map numpad number to board index
        int index = numpadToIndex[number];
		//Check if space is occupied
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

//Easy Mode. AI makes random valid moves.
//Uses modulo arithmatic to limit random number to 0-8 range.
void computerMoveEasy(char* spaces, char computer) {
    int number;
    //Note: Seeding the random number generator here is not ideal as it can lead to repeated sequences if called multiple times in quick succession.
	// To fix this add initial seeding in main function or at start of program.
    srand(time(0));

    while (true) {
		// The modulo operator (%) returns the remainder of a division operation. 
        number = rand() % 9; // number will be random between 0 and 8
		//If that space of a given index is empty
        if (spaces[number] == ' ') {
			//Assign computer marker to that space
            spaces[number] = computer; //computers marker
			break; //if successful will break out of loop

        }
    }
}


//Medium Mode. Mix of random and minimax moves.
void computerMoveMedium(char* spaces, char player, char computer) {
    // Takes a dice roll to decide whether to play a perfect move or play a random move.
    int roll = rand() % 100;
	// 80% chance to play minimax move, 20% chance to play random move.
    if (roll < 80) {
        computerMoveMinimax(spaces, player, computer);
    }
    else {
        computerMoveEasy(spaces, computer);
    }

    }

// Checks whether the board has any empty spaces left.
bool checkTie(char* spaces) {
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
			// Found an empty space, not a tie
            return false;
        }

    }
    std::cout << "It's a tie!!\n";
    drawBoard(spaces); //Show final board state
	playSoundEffect("you_lose.mp3"); // Play tie sound effect (same as lose for now)
	return true; // No empty spaces, it's a tie
}

// Checks for a winner by evaluating all possible winning combinations.
// More indepth comments in minimax functions where similar logic is used. Check scoreBoard function for more details.
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


//Minimax AI Helper Functions below.

// Returns a vector of available moves (empty spaces) on the board.
// Used by minimax algorithm to explore possible moves.
std::vector<int> getAvailableMoves(char* spaces) {
    std::vector<int> availableMoves; //Python : availableMoves = [] 
    //Only need true false, append to list
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            availableMoves.push_back(i); //Python : availableMoves.append(i)

        }
    }
    return availableMoves;
}

// Returns an interger score repesenting the outcome of the board state.
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

//Returns true if the game is over (win or tie), false otherwise.
//Used by minimax to determine base case.
bool isGameOver(char* spaces) {
	//Note: Make a shared helper function for logic for checking winner, shared with Scoreboard and checkWinner functions for better code reuse.

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

// Hard Mode. (default)
// Minimax AI Move function, chooses best move for computer using minimax algorithm.
void computerMoveMinimax(char* spaces, char player, char computer) {
    //Create new Vector wth all possible/legal moves, will return a list of of playable indexes (0-8)
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
        newSpaces[move] = computer; // Ai will play their char on a simulated board. (Actual board left unchanged.)
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


// Note: Optimisation: Alpha-beta pruning to reduce number of nodes evaluated in minimax tree, however for tic tac toe its not really needed as the game tree is small enough to be fully evaluated quickly by modern computers.

// Minimax algorithm implementation. Recursively explores all possible moves and their outcomes to determine the optimal move for the AI.
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