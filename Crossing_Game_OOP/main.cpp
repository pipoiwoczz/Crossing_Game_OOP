#include "setup.h"

char MOVING;

int main() {
	system("cls");
	fixConsoleWindow();
	
	drawGameTitle();
	//drawFrame();
	drawCharacter({ 12, 1 });

	MOVING = toupper(_getch());

	return 1;
}