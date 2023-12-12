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
class cCoin;

class cGame {
	COORD oldPos;
	const vector <vector<string>> CreatedLevel{
		{"jungle1.txt"},
		{"beach1.txt"},
		{"city1.txt"}
	};

	static cGame game;

	friend cGameEngine;
	vector<COORD> obstacleLanes;
    vector<cObstacle*> liveObstacles;
	vector<cEnvironment*>  environmentObject;
    vector<cPeople *> livePeople;
	vector<cWidget*> listWidget;
	vector<cLabel*> listLabel;

	short gameOrder, gameLevel; // order: 1 or 2 player
	bool isPause, isExit;
	bool isStart = false;
	bool isLose;
	bool tomainMenu;
	bool suddenStop = false;
	//Special events
	bool hasSuddenStop = false;

	//Game info
	long coinBonus;
	long totalPoint;
	double totalTime;
	double timeStart, timeEnd;
	double timePauseStart, timePauseEnd;
	double timePause;

	int currentTheme;
	int currentPhase;

	//thread handler
	thread collisionThreadHandle;
	thread drawThreadHandle;
	thread randomStopThreadHandle;

	cObstacle* nemesis;
	cPeople* victim;

	//Skills
	int skillCooldown[2] = { 0, 0 };
	int defaultSkillCooldown[2] = { 400, 400 };
	int freezetime = 100;
	vector<cWidget*> listSkill;
	vector<cLabel*> cooldownLabel;
	int handlingSkillExec(cPeople* pPeople);
	void updateSkillState();
	void teleport(cPeople* pPeople);
	int skillValue = -1;

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

		void GameDiePanel();

		void environmentImpact();

		//short getNumberOfLane();

		//vector<COORD> getPositionLane(); 		// COORD X is pos Y and Y is direction
		void collisionThread();
		void drawThread();
		void pizzaDraw();


		vector<cPeople *> getPeople();
        vector<cObstacle *> getObstacles();

		void updateInfo();


		void randomStopThread();
		
		void resetGame();
		void exitGame(HANDLE t);
		void pauseGame();	
		static void resumeGame();
		void resumeFunction();
		void save(string fileName);

        bool isImpact();
		
		void updatePosObstacle();

		short getGameOrder();

		void ScoreBoard();
		void MainGame();
		void LoadGame();
		void load(string fileName);
		void Setting();
		void GameOver();
		void GameWin();

		void drawBackGround();
		//void impactEffect(cObstacle* obsta);
		void spawnPeople();
		
		bool isFinishLevel();
		double calculateTime();
		void resetTime();
		void calculatePoint();

		void nextLevel();
		void endlessMode();

		void spawnCoin();
};

#endif
