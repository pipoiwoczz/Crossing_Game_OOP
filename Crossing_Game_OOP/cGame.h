#ifndef _CGAME_H
#define _CGAME_H

#include "cAnimal.h"
#include "cVehicle.h"
#include "cPeople.h"

class cGame {
	cTruck *truck;
	cLion* lion;
	cRhino * rhino;
	cCrocodile *crocodile;
	cHelicopter *helicopter;
	cMotorbike *motorbike;
	cPeople *people;

	short gameOrder, gameLevel; // order: 1 or 2 player
	bool isPause, isExit;
	

	public:
		cGame() {
			gameOrder = 1;
			gameLevel = 1;
			isPause = false;
			isExit = false;	
		}
		~cGame() {
			delete[]truck;
			delete[]lion;
			delete[]rhino;
			delete[]crocodile;
			delete[]helicopter;
			delete[]motorbike;
			delete[]people;
		}

		void drawGame();

		void getPeople();
		void getVehicle();
		void getAnimal();
		void getTruck();
		void getLion();
		void getRhino();
		void getCrocodile();
		void getHelicopter();
		void getMotorbike();
		
		void stopDrawAnimal() {
			//lion->stop();
		}

		void resetGame();
		void exitGame(HANDLE t);
		void startGame();
		void loadGame();
		void saveGame();
		void pauseGame(HANDLE t);
		void resumeGame(HANDLE t);

		void updatePosPeople(char MOVING) {
			people->move(MOVING);
		}
		//bool isImpact() {
		//	if (people->isImpactLion(lion))
		//		return true;
		//	return false;
		//}
		

		void updatePosVehicle();
		void updatePosAnimal();

		short getGameOrder() {
			return gameOrder;
		}
};

#endif