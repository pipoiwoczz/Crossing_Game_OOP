#ifndef _CGAME_H
#define _CGAME_H
#include "Graphics.h"
#include "cAnimal.h"
#include "cVehicle.h"
#include "cPeople.h"
#include "cObstacle.h"
#include "Sound.h"
#include "Map.h"
#include "gameEngine.h"
//#include "Map.h"

class cGame {

	friend cGameEngine;
    
    vector<cObstacle *> liveObstacles;
    
    vector<cPeople *> livePeople;

	short gameOrder, gameLevel; // order: 1 or 2 player
	bool isPause, isExit;
	int map = 0; // map = 1 -> city, map = 2 -> forest, map = 3 -> beach
	bool isLose = false;

	long totalPoint;
	double totalTime;
	double timeStart, timeEnd;
	double timePauseStart, timePauseEnd;
	double timePause;

	public:
		cGame() {
			gameOrder = 1;
			gameLevel = 1;
			map = 1;
			isPause = false;
			isExit = false;	
			totalPoint = 0;
			timePause = 0;
			totalTime = 0;
		}
    
        cGame (string saveFile);
    
		~cGame() {
			for (int i = 0; i < liveObstacles.size(); i++)
			{
				delete liveObstacles[i];
			}
			for (int i = 0; i < livePeople.size(); i++)
			{
				delete livePeople[i];
			}
			liveObstacles.clear();
			livePeople.clear();
		}


		void gameThread();
		void checkImpactThread();
		void drawThread();
		void movingThread();
		void getMainMenuActionThread();
        void despawnThread(); // loops objects that have gone offscreen to the other side
        void randomStopThread(); // stops a row of objects at random (or set) intervals
		

		void drawGame();
		void drawMap();

		vector<cPeople *> getPeople();
        vector<cObstacle *> getObstacles();
//		void getVehicle();
//		void getAnimal();
//		void getTruck();
//		void getLion();
//		void getRhino();
//		void getCrocodile();
//		void getHelicopter();
//		void getMotorbike();
		
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
        bool isImpact();
		
		void updatePosObstacle();

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

		void drawBackGround();
		void impactEffect(int i);
		void spawnPeople();
		void spawnObstacle();
		bool isFinishLevel();
		double calculateTime();
		void resetTime();
		void calculatePoint();

#define refreshBackGround drawBackGround
};
//cObstacle * createObject (short type, COORD position, int speed);

#endif
