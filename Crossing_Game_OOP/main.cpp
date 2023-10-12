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

	//cLion lion(-20, 40);
	//thread subThread(subThread2, &lion);

	//cPeople people({50, 50});
	//people.draw({ 50, 50 });
	//thread t2(subThread3, &lion, &people);

	/*while (true) {
		MOVING = toupper(_getch());
		people.move(MOVING, &lion);
	}*/
	
	cg.getPeople();
	cg.getLion();
	thread t1(threadTest), t2(threadTest2, &t1);

	while (true) {
		MOVING = toupper(_getch());
		cg.updatePosPeople(MOVING);
	}
	

	return 1;
}