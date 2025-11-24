#include <cstdlib>
#include "utils.h"

void clearScreen(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}
//TODO: put in utils.pp with utils.h
void waitForKey() {
	system("pause");
}