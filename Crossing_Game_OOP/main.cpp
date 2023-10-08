#include "setup.h"

char MOVING;

int main() {
	system("cls");
	fixConsoleWindow();
	
	drawGameTitle();
	//drawFrame();
	//moveTestting();

	cLion lion(-20, 40);
	lion.move(40);
	
	MOVING = toupper(_getch());

	return 1;
}