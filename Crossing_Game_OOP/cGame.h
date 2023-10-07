#pragma once
#include "setup.h"

class cGame {
	cTruck *mTruck;

	cPeople *mPeople;

	int mLevel;

	public:
		cGame();
		~cGame();
		void drawGame();

		cPeople* getPeople();
		cVehicle* getVehicle();
		cAnimal* getAnimal();

		void resetGame();
		void exitGame(HANDLE t);
		void startGame();
		void loadGame();
		void saveGame();
		void pauseGame(HANDLE t);
		void resumeGame(HANDLE t);

		void updatePosPeople(char MOVING);
		void updatePosVehicle();
		void updatePosAnimal();
};