#ifndef _CGAME_H
#define _CGAME_H
#include "setup.h"
class cObstacle;
class cPeople;
void cleanGame();

class cDWindow;
class cWidget;
class cGameEngine;
class cLabel;
class cGame {
	friend cGameEngine;
    vector<cObstacle*> liveObstacles;
	vector<cObstacle*>  environmentObject;
    vector<cPeople *> livePeople;
	vector<cWidget*> listWidget;
	vector<cLabel*> listLabel;
	short gameOrder, gameLevel; // order: 1 or 2 player
	bool isPause, isExit, isLoad;
	int map = 0; // map = 1 -> city, map = 2 -> forest, map = 3 -> beach
	bool isLose = false;


	long totalPoint;
	double totalTime;
	double timeStart, timeEnd;
	double timePauseStart, timePauseEnd;
	double timePause;

	cDWindow* pPausePanel;

	public:
		static bool mainloop;
		cGame();
    
        cGame (string saveFile);
    
		~cGame();


        void despawnThread(); // loops objects that have gone offscreen to the other side
        void randomStopThread(); // stops a row of objects at random (or set) intervals
		

		vector<cPeople *> getPeople();
        vector<cObstacle *> getObstacles();

		void resetGame();
		void exitGame(HANDLE t);
		static void saveGame(cGame *pGame);
		void pauseGame();	
		static void resumeGame(cGame *pGame);
		void resumeFunction();
		void save(string fileName);


		//void updatePosPeople(char MOVING) {
		//	if (!isPause) {

		//	}
		//		//people->move(MOVING);
		//}
        bool isImpact();
		
		void updatePosObstacle();

		short getGameOrder();

		void ScoreBoard();
		void MainGame();
		void LoadGame();
		static void load(string fileName);
		void Setting();
		void GameOver();
		void GameWin();

		void drawBackGround();
		void impactEffect(cObstacle* obsta);
		void spawnPeople();
		void spawnObstacle();
		bool isFinishLevel();
		double calculateTime();
		void resetTime();
		void calculatePoint();

		void nextLevel();
		void endlessMode();

};

#endif
