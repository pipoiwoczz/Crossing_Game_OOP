#ifndef _CGAME_H
#define _CGAME_H
#include "cAnimal.h"
#include "cVehicle.h"
#include "cPeople.h"
#include "cObstacle.h"
#include "Map.h"

class cGame {
//	cTruck *truck;
//	cLion* lion;
//	cRhino * rhino;
//	cCrocodile *crocodile;
//	cHelicopter *helicopter;
//	cMotorbike *motorbike;

	//Map* map;
    
    vector<cObstacle> liveObstacles;
    
	//cPeople *people;
    vector<cPeople> livePeople;
	//cPeople people;

	short gameOrder, gameLevel; // order: 1 or 2 player
	bool isPause, isExit;
	int map = 0; // map = 1 -> city, map = 2 -> forest, map = 3 -> beach
	bool isLose = false;

	public:
		cGame() {
			gameOrder = 1;
			gameLevel = 1;
			map = 0;
			isPause = false;
			isExit = false;	
		}
    
		~cGame() {
//			delete[]truck;
//			delete[]lion;
//			delete[]rhino;
//			delete[]crocodile;
//			delete[]helicopter;
//			delete[]motorbike;
//			delete[]people;
			//delete map;
		}

		void gameThread();
		void checkImpactThread();
		void drawThread();
		void movingThread();
		void getMainMenuActionThread();

		void drawGame();
		void drawMap();

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
		void continueDrawAnimal() {
			//lion->resume();
		}

		void resetGame();
		void exitGame(HANDLE t);
		void startGame();
		void loadGame();
		void saveGame();
		void pauseGame();	
		void resumeGame();

		void updatePosPeople(char MOVING) {
			if (!isPause) {

			}
				//people->move(MOVING);
		}
		bool isImpact() {
	/*		if (people->isImpactLion(lion)) {
				isLose = true;
				return true;
			}*/
			return false;
		}
		
		void updatePosVehicle();
		void updatePosAnimal();

		short getGameOrder() {
			return gameOrder;
		}

		int getMenuChoice();

		void ScoreBoard();
		void MainGame();
		void LoadGame();
		void Setting();
		void GameOver();
		void GameWin();
};

#endif
