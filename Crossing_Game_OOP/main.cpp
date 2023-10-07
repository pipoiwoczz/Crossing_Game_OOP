#include "setup.h"

char MOVING;

int main() {
	system("cls");
	fixConsoleWindow();
	
	drawFrame();
	drawCharacter({ 0, 1 });

	MOVING = toupper(_getch());

	return 1;
}