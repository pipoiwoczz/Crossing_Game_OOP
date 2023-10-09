#include "setup.h"

char MOVING;
void subThread2(cLion *lion) {
	(*lion).move(40);
}

void subThread3(cLion* lion, cPeople* people) {
	while (true) {
		if ((*people).isImpactOne(lion)) {
			drawFrame();
		}
	}
}

int main() {
	system("cls");
	fixConsoleWindow();
	
	drawGameTitle();

	cLion lion(-20, 40);
	thread subThread(subThread2, &lion);

	cPeople people({50, 50});
	people.draw({ 50, 50 });
	thread t2(subThread3, &lion, &people);

	while (true) {
		MOVING = toupper(_getch());
		people.move(MOVING, &lion);
	}
	


	return 1;
}