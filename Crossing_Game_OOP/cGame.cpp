#include "cGame.h"
/*
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
}*/

void cGame::drawGame() {
	drawGameTitle();
}

