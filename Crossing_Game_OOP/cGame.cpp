#include "setup.h"

void cGame::getPeople() {
	short numOfPlayer = getGameOrder();
	if (numOfPlayer == 1) {
		people = new cPeople;
	} else {
		people = new cPeople[2];
		people[2].setPos({ 70, 50 });
	}
}

void cGame::getLion() {
	lion = new cLion[7];
	for (int i = 0; i < 7; i++) {
		lion[i].setPos({ short(-20 - i * 40), 40 });
	}
}

void cGame::drawGame() {
	drawGameTitle();
	lion->move(lion[0].getPos(), lion);
}


int cGame::getMenuChoice() {
	char MOVING;
	int choice = 1;
	while (true) {
		// drawMainMenu(choice);
		MOVING = toupper(_getch());
		if (MOVING == 'S' || MOVING == 40) {
			if (choice == 5) {
				choice = 1;
			}
			else {
				choice++;
			}
		}
		else if (MOVING == 'W' || MOVING == 38) {
			if (choice == 1) {
				choice = 5;
			}
			else {
				choice--;
			}
		}
	}
}

void cGame::startGame() {
	// create mainmenu with option
	// drawMainMenu(1)
	int choice = getMenuChoice();
	
	switch (choice) {
	case 1: 
		// Start new game
		break;
	case 2:
		// Load game
		break;
	case 3:
		// Setting
		break;
	case 4:
		// Scoreboard
		break;
	case 5:
		// Exit game
		break;
	default:
		break;
	}
}