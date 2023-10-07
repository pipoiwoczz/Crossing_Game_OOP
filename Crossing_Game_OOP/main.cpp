#include "setup.h"

char MOVING;

int main() {
	system("cls");
	fixConsoleWindow();
	
	for (int i = 0; i < 33; i++) {
		if (i == 15) {
			printCenterCharacters(L"LOAD GAME CHECK LIST", Color::aqua, Color::bright_white, i, My_Windows);
			continue;
		}
		printCenterCharacters(L"++", Color::aqua, Color::bright_white, i, My_Windows);
	}

	MOVING = toupper(_getch());

	return 1;
}