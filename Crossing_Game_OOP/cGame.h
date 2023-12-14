#ifndef _CGAME_H
#define _CGAME_H
#include "setup.h"
class cObstacle;
class cEnvironment;
class cPeople;

class cDWindow;
class cWidget;
class cGameEngine;
class cLabel;
class cGame;
class cCoin;

class cGame {
	const vector <vector<string>> CreatedLevel{
		{"jungle1.txt","jungle2.txt", "jungle3.txt","jungle4.txt","jungle5.txt"},
		{"beach1.txt","beach2.txt","beach3.txt","beach4.txt","beach5.txt"},
		{"city1.txt","city2.txt","city3.txt","city4.txt","city5.txt"}
	};

	static cGame game;

	friend cGameEngine;
	vector<COORD> obstacleLanes;
    vector<cObstacle*> liveObstacles;
	vector<cEnvironment*>  environmentObject;
	vector<cCoin*> coins;
    vector<cPeople *> livePeople;
	vector<cDWindow*> listWidget;
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
	long coinNow = 0;
	long coinBonus = 0;
	long totalPoint = 0;
	double totalTime;
	double timeStart, timeEnd;
	double timePauseStart, timePauseEnd;
	double timePause;
	int time;

	int currentTheme;
	int currentPhase;

	//thread handler
	thread collisionThreadHandle;
	thread drawThreadHandle;
	thread randomStopThreadHandle;

	cObstacle* nemesis = nullptr;
	cPeople* victim = nullptr;

	int singleSkin = 0;
	//Skills
	vector<vector<cWidget*>> SkillIcon;
	vector<vector<cLabel*>> Skillcooldown;
	int defaultSkillCooldown[2] = { 60000, 60000 };
	int freeze = -1;
	int defaultFreezetime = 200;
	void handlingSkillFx();
	int handlingSkillExec(cPeople* pPeople, long long &startTime);
	void updateSkillState();
	void teleport(cPeople* pPeople);

	cGame();
	~cGame();

	public:
		
		static cWidget window;
		static cDWindow mainMenu;
		static bool mainloop;

		static bool InitGame();
		
		static void onGameReady();
		
		void clearObjects(bool clearPeople = false, bool clearEnvironment = false, bool clearCoin = false);

		void spawnObstacle(const string& levelFile);

		void spawnEnvironment(); //summon environment objects of current map theme
		
		bool checkPassLevel();

		void prepareGame();
		void prepareUI();
		void clearUI();
		void clearSkillUI();
		void prepareSkillUI();

		void GamePlayPanel();

		bool GameCharacterPanel();

		void GameNewGamePanel();

		void GamePausePanel();

		void GameSettingsPanel();

		void chooseCharacter();

		void GameSavePanel();

		bool GameLoadPanel();

		void GameQuitPanel(bool fullexit = false);

		void GameDiePanel();

		void GameHelpPanel();

		void environmentImpact();

		//short getNumberOfLane();

		//vector<COORD> getPositionLane(); 		// COORD X is pos Y and Y is direction
		void collisionThread();
		void drawThread();
		void pizzaDraw(long long startTime[2]);



		void updateInfo();


		void randomStopThread();
		
		bool isComplete();

		void resumeFunction();
		void save(string fileName);

        bool isImpact();
		

		short getGameOrder();

		void ScoreBoard();
		void MainGame();
		void load(string fileName);
		void GameWinPanel();
		void processLose();

		//void impactEffect(cObstacle* obsta);
		void spawnPeople();
		
		bool isFinishLevel();
		double calculateTime();
		void resetTime();
		void calculatePoint();

		void nextLevel();

		void spawnCoin();
};

#endif
