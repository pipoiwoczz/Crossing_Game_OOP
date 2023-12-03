#ifndef _CGAME_H
#define _CGAME_H
#include "setup.h"
class cObstacle;
class cEnvironment;
class cPeople;
void cleanGame();

class cDWindow;
class cWidget;
class cGameEngine;
class cLabel;
class cGame;

class cGame {

	const vector <vector<string>> CreatedLevel{
		{"jungle1.txt"},
		{"jungle1.txt"},
		{"jungle1.txt"}
	};

	static cGame game;

	friend cGameEngine;
    vector<cObstacle*> liveObstacles;
	vector<cEnvironment*>  environmentObject;
    vector<cPeople *> livePeople;
	vector<cWidget*> listWidget;
	vector<cLabel*> listLabel;

	short gameOrder, gameLevel; // order: 1 or 2 player
	bool isPause, isExit, isLoad;
	bool isLose;
	bool tomainMenu;

	//Special events
	bool hasSuddenStop = false;
	bool suddenStop;
	int cooldown = 200;

	long totalPoint;
	double totalTime;
	double timeStart, timeEnd;
	double timePauseStart, timePauseEnd;
	double timePause;

	int currentTheme;
	int currentPhase;
	cGame();
	~cGame();
	public:
		static cWidget window;
		static cDWindow mainMenu;
		static bool mainloop;

		static bool InitGame();
		
		static void onGameReady();
		
		void clearObjects(bool clearPeople = false, bool clearEnvironment = false);

		void spawnObstacle(const string& levelFile);

		void spawnEnvironment(); //summon environment objects of current map theme
		
		void prepareGame();

		void GamePlayPanel();

		void GameNewGamePanel();

		void GamePausePanel();

		void GameSettingsPanel();

		void GameSavePanel();

		void GameLoadPanel();

		void GameQuitPanel(bool fullexit = false);

		void environmentImpact();

		vector<cPeople *> getPeople();
        vector<cObstacle *> getObstacles();


		void randomStopThread();
		
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
		
		bool isFinishLevel();
		double calculateTime();
		void resetTime();
		void calculatePoint();

		void nextLevel();
		void endlessMode();

};

#endif
