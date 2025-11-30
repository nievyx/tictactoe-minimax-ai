#include <cstdlib>
#include <conio.h>
#include "utils.h"

void clearScreen(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void waitForKey() {
	system("pause");
}

char getKey() {
	return _getch();
}