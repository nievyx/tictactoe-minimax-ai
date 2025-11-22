#include <iostream>
#include <windows.h> //for sleep function
#include "utils.h"

void runDebug() {
	std::cout << "=== DEBUG MODE ===\n";
	std::cout << "This is a simple test area\n";
	std::cout << "";

	Sleep(2000);  
	clearScreen();
	
}