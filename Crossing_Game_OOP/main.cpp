#include "setup.h"

char MOVING;
cGame cg;
bool isRunningDrawGame = true;

void subThread2(cLion *lion) {
	(*lion).move(lion->getPos());
}

void subThread(cGame cg) {
	cg.drawGame();
}

void subThread3(cLion* lion, cPeople* people) {
	while (true) {
		if ((*people).isImpactOneLion(lion)) {
			drawFrame();
		}
	}
}

void threadTest() {
	if (isRunningDrawGame) 
	{
		cg.drawGame();
	}
	
}

void threadTest2(thread *t) {
	while (true) {
		if (cg.isImpact()) {
			break;
		}
	}
	cg.stopDrawAnimal();
	clearConsole();
	drawLosingTitle();
}

int main() {
	system("cls");
	textSize(4);
	SetConsoleTitle(L"Crossing Road");
	fixConsoleWindow();
	showScrollBar(false);
	hideCursor(true);
	DisableCtrButton(false, true, true);
	disableUserSelection();

	drawGameTitle();

	return 1;
}