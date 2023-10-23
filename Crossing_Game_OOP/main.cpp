#include "setup.h"

char MOVING;
cGame cg = cGame();
bool isRunningDrawGame = true;


int main() {
	system("cls");
	clearConsole();
	Graphic graphic = Graphic();
	drawGameTitle();
	cg.startGame();

	

	return 1;
}