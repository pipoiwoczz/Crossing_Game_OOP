#include "setup.h"

char MOVING;
cGame cg = cGame();
bool isRunningDrawGame = true;


int main() {
	system("cls");
	Graphic graphic = Graphic();


	drawGameTitle();
	drawMainMenu();

	return 1;
}