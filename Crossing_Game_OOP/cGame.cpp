#include "cGame.h"
#include "cObstacle.h" 
#include "cPeople.h"
#include "Sound.h"
#include "Map.h"
#include "hitbox.h"
#include "cAnimal.h"
#include "cVehicle.h"
#include "cEnvironment.h"
#include "cAsset.h"
#include "gameEngine.h"
#include "cTime"

bool cGame::InitGame()
{
	window.IsVisible = true;
	window.topleft = { My_Windows.Left, My_Windows.Top };
	window.botright = { My_Windows.Right, My_Windows.Bottom };
	window.parentWindow = nullptr;
	window.WidgetFace = cAsset::assetLoader(UIPrefix + "mainWD.txt");

	mainMenu.IsVisible = true;
		
	mainMenu.topleft = { My_Windows.Left, My_Windows.Top };
	mainMenu.botright = { My_Windows.Right, My_Windows.Bottom };
	mainMenu.parentWindow = &window;
	mainMenu.WidgetFace = cAsset::assetLoader(UIPrefix + "menuBg.txt");
	mainMenu.show();
	return true;
}
void cGame::onGameReady()
{
	mainMenu.show();
	cDWindow panel(&mainMenu, { 479, 71 }, "panelmainmenu.txt", true);

	cButton panelButton[4] = {
		cButton(&panel, { 0, 0 }, "buttonplay.txt", 1),
		cButton(&panel, { 0, 22 }, "buttonscoreboard.txt", 1),
		cButton(&panel, { 0, 44 }, "buttonsettingsm.txt", 1),
		cButton(&panel, { 0, 66 }, "buttonexitm.txt", 1)
	};

	function<void()> panelFunction[4]{
		[]() {game.GamePlayPanel(); },
		[]() {game.ScoreBoard(); },
		[]() {game.GameSettingsPanel(); },
		[]() {game.GameQuitPanel(true); }
	};

	int current = 0;
	panelButton[current].show();

	while (mainloop)
	{
		if (GetAsyncKeyState(VK_UP) && current > 0)
		{
			panelButton[current].unshow();
			current--;
			panelButton[current].show();
		}

		if (GetAsyncKeyState(VK_DOWN) && current < 3)
		{
			panelButton[current].unshow();
			current++;
			panelButton[current].show();
		}

		if (GetAsyncKeyState(0x0D) & 0x8000)
		{
			panelFunction[current]();
			mainMenu.show();
			panel.show();
			panelButton[current].show();
		}
		Sleep(200);
	}
}
void cGame::clearObjects(bool clearPeople, bool clearEnvironment)
{
	for (int i = 0; i < liveObstacles.size(); i++)
		delete liveObstacles[i];
	liveObstacles.clear();
	if (clearEnvironment)
	{
		for (int i = 0; i < environmentObject.size(); i++)
			delete environmentObject[i];
		environmentObject.clear();
	}

	if (clearPeople)
	{
		for (int i = 0; i < livePeople.size(); i++)
			delete livePeople[i];
		livePeople.clear();
	}
}

void cGame::spawnEnvironment() //summon environment objects of current map theme
{
	if (currentTheme == 0)
	{
		cEnvironment* lily = new cLilyleaf({ 0, 73 });
		environmentObject.push_back(lily);

		environmentObject.push_back(new cRiver(73, lily));
		lily = new cLilyleaf({ 30, 55 });
		environmentObject.push_back(lily);
		environmentObject.push_back(new cRiver(55, lily));

	}
	else if (currentTheme == 1)
	{

	}
	else if (currentTheme == 2)
	{
		environmentObject.push_back(new cTrafficLight({ 0, 73 }));
		hasSuddenStop = true;
		suddenStop = false;
	}
}

void cGame::prepareGame()
{
	clearObjects();
	spawnEnvironment();
	spawnObstacle(CreatedLevel[currentTheme][currentPhase]);
	spawnPeople();
}

void cGame::GamePlayPanel()
{	
	tomainMenu = false;
	cDWindow panel(&mainMenu, { 30, 6 }, "panelplay.txt", true);
	cButton panelButton[4] = {
		cButton(&panel, {2, 21}, "buttonnewgame.txt", 1),
		cButton(&panel, {2, 50}, "buttonnewgame.txt", 1),
		cButton(&panel, {2, 79}, "buttonnewgame.txt", 1),
		cButton(&panel, {2, 108}, "buttonnewgame.txt", 1)
	};

	function<void()> panelFunct[4] = {
		[]() {game.GameNewGamePanel(); },
		[]() {},
		[]() {},
		[]() {}
	};

	int current = 0;
	panelButton[current].show();

	while (!tomainMenu)
	{
		if (GetAsyncKeyState(VK_UP) && current > 0)
		{
			panelButton[current].unshow();
			current--;
			panelButton[current].show();
		}
		if (GetAsyncKeyState(VK_DOWN) && current < 3)
		{
			panelButton[current].unshow();
			current++;
			panelButton[current].show();
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
		if (GetAsyncKeyState(0x0D) & 0x8000)
		{
			panelFunct[current]();
			mainMenu.show();
			panel.show();
			panelButton[current].show();
		}
		Sleep(200);
	}
}

void cGame::GameNewGamePanel()
{
	cDWindow panel(&mainMenu, { 30, 6 }, "panelnewgame.txt", true);
	cButton panelButton[3] = {
		cButton(&panel, { 20, 33 }, "iconmapjungle.txt", 1, true),
		cButton(&panel, { 20, 65 }, "iconmapbeach.txt", 1, true),
		cButton(&panel, { 20, 97 }, "iconmapcity.txt", 1, true)
	};

	int current = 0;
	panelButton[current].onSelect();

	while (true)
	{
		if (GetAsyncKeyState(VK_UP) && current > 0)
		{
			panelButton[current].onDeSelect();
			current--;
			panelButton[current].onSelect();
		}
		if (GetAsyncKeyState(VK_DOWN) && current < 2)
		{
			panelButton[current].onDeSelect();
			current++;
			panelButton[current].onSelect();
		}
		Sleep(100);
		if (GetAsyncKeyState(0x51) & 0x8000)
			break;
		if (GetAsyncKeyState(0x0D) & 0x8000)
		{
			gameMap::changeMapTheme(current);
			currentTheme = current;
			currentPhase = 0;
			prepareGame();
			MainGame();
			break;
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
		Sleep(75);
	}
}

void cGame::GamePausePanel()
{
	isPause = true;
	timePauseStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	cDWindow panel(&window, { 122, 11 }, "panelpause.txt", true);
	cButton panelButton[6]{
		cButton(&panel, { 42, 21 }, "buttonresume.txt", 1),
		cButton(&panel, { 42, 39 }, "buttonsettingsp.txt", 1),
		cButton(&panel, { 42, 57 }, "buttonsave.txt", 1),
		cButton(&panel, { 42, 75 }, "buttonload.txt", 1),
		cButton(&panel, { 42, 93 }, "buttonexitdesktop.txt", 1),
		cButton(&panel, { 42, 111 }, "buttonexitmain.txt", 1)
	};

	std::function<void()> panelFunct[6] = {
		[]() {
			cGameEngine::fillScreenWithLastFrame(true);
			game.resumeFunction();
			game.isPause = false;
		},
		[]() {game.GameSettingsPanel(); },
		[]() {game.GameSavePanel(); },
		[]() {game.GameLoadPanel(); },
		[]() {game.GameQuitPanel(true); },
		[]() {game.GameQuitPanel();	 }
	};

	int current = 0;
	panelButton[current].show();
	while (isPause)
	{
		if (GetAsyncKeyState(VK_DOWN) < 0 && current < 5)
		{
			panelButton[current].unshow();
			current++;
			panelButton[current].show();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && current > 0)
		{
			panelButton[current].unshow();
			current--;
			panelButton[current].show();
		}
		Sleep(200);
		if (GetAsyncKeyState(0x0D) && 0x8000)
		{
			panelFunct[current]();
			panel.show();
			panelButton[current].show();
		}
	}
}

void cGame::GameSettingsPanel()
{
	cDWindow panel(&window, { 122, 11 }, "panelsettings.txt", true);
	void (*panelFunct[2][2])() = {
	{ Sound::reduceSoundBackground, Sound::increaseSoundBackground},
	{Sound::reduceEffectSound, Sound::increaseEffectSound}
	};
	int (*getVolume[2])() = { Sound::getCurrentMusicVolume, Sound::getCurrentEffectVolume };

	cLabel panelInfo[2][2] = {
		{cLabel(&panel, { 30, 30 }, "Music Volume", 1, Color::black, true), cLabel(&panel, { 177, 30 }, to_string(getVolume[0]() / 10), 1, Color::black,true)},
		{cLabel(&panel, { 30 , 60 }, "Effect Volume", 1, Color::black, true), cLabel(&panel, { 177, 60 }, to_string(getVolume[1]() / 10), 1, Color::black, true)}
	};

	cDWindow selectarrow(&panel, { 210, 30 }, "arrowL.txt", true);
	short arrowPos[2] = { 30, 60 };
	int currentarrowpos = 0;

	while (true)
	{

		if (GetAsyncKeyState(VK_DOWN) < 0 && currentarrowpos < 1)
		{
			currentarrowpos++;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, arrowPos[currentarrowpos] });
			selectarrow.show();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && currentarrowpos > 0)
		{
			currentarrowpos--;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, arrowPos[currentarrowpos] });
			selectarrow.show();
		}
		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			panelFunct[currentarrowpos][0]();
			panelInfo[currentarrowpos][1].updateText(to_string(getVolume[currentarrowpos]() / 10));
			Sleep(250);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			panelFunct[currentarrowpos][1]();
			panelInfo[currentarrowpos][1].updateText(to_string(getVolume[currentarrowpos]() / 10));
			Sleep(250);
		}
		Sleep(200);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
	}
}

void cGame::GameSavePanel()
{
	cDWindow panel(&window, { 122, 11 }, "menusave.txt", true);
	cButton slots[4]{
		cButton(&panel, {10, 21}, "slot1.txt", true),
		cButton(&panel, {10, 47}, "slot1.txt", true),
		cButton(&panel, {10, 73}, "slot1.txt", true),
		cButton(&panel, {10, 99}, "slot1.txt", true),
	};

	int current = 0;
	slots[current].onSelect();
	while (true)
	{

		if (GetAsyncKeyState(VK_DOWN) < 0 && current < 2)
		{
			slots[current].onDeSelect();
			current++;
			slots[current].onSelect();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && current > 0)
		{
			slots[current].onDeSelect();
			current--;
			slots[current].onSelect();
		}
		Sleep(100);
		if (GetAsyncKeyState(0x0D) & 0x8000)
		{
			//SAVE FUNCTION
		}
		Sleep(100);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
	}
}

void cGame::GameLoadPanel()
{
	cDWindow panel(&window, { 122, 11 }, "menuLoad.txt", true);
	cButton slots[4]{
		cButton(&panel, {10, 21}, "slot1.txt", true),
		cButton(&panel, {10, 47}, "slot1.txt", true),
		cButton(&panel, {10, 73}, "slot1.txt", true),
		cButton(&panel, {10, 99}, "slot1.txt", true),
	};

	int current = 0;
	slots[current].onSelect();
	while (true)
	{

		if (GetAsyncKeyState(VK_DOWN) < 0 && current < 2)
		{
			slots[current].onDeSelect();
			current++;
			slots[current].onSelect();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && current > 0)
		{
			slots[current].onDeSelect();
			current--;
			slots[current].onSelect();
		}
		Sleep(100);
		if (GetAsyncKeyState(0x0D) & 0x8000)
		{
			//LOAD FUNCTION
		}
		Sleep(100);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
	}
}

void cGame::GameQuitPanel(bool fullexit)
{
	cDWindow confirm(&window, { 177, 30 }, "panelconfirmexit.txt", true);
	cDWindow selectarrow(&confirm, { 96, 37 }, "arrowenter.txt", true);

	short arrowPos[2] = { 24, 37 };
	int currentarrowpos = 1;
	while (true)
	{
		if (GetAsyncKeyState(VK_DOWN) < 0 && currentarrowpos < 1)
		{
			currentarrowpos++;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, arrowPos[currentarrowpos] });
			selectarrow.show();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && currentarrowpos > 0)
		{
			currentarrowpos--;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, arrowPos[currentarrowpos] });
			selectarrow.show();
		}
		Sleep(100);
		if (GetAsyncKeyState(0x0D) & 0x8000)
		{
			if (currentarrowpos == 0)
			{
				this->tomainMenu = true;
				this->isPause = false;
				this->isExit = true;
				if (fullexit)
					cGame::mainloop = false;
			}
			break;
		}
		Sleep(100);
	}
}

void cGame::environmentImpact()
{
	bool isCook = false;
	for (int j = 0; j < environmentObject.size(); j++)
	{
		if (!environmentObject[j]->friendly)
		{

			for (int u = 0; u < livePeople.size(); u++)
			{
				if (environmentObject[j]->Box.isOverlap(livePeople[u]->mBox))
				{
					livePeople[u]->mState = false;
					isCook = true;
					if (environmentObject[j]->pSafe->Box.isOverlap(livePeople[u]->mBox))
					{
						livePeople[u]->mState = true;
						isCook = false;
					}
					if (isCook)
						break;
				}
			}
		}
	}
	if (isCook)
	{
		Sleep(200);
		isLose = true;
	}
}




void cleanGame()
{
	cGameEngine::cleanEngine();
}
void doNothing() {
}
cGame::cGame()
{
	gameOrder = 1;
	gameLevel = 1;
	isPause = false;
	isExit = false;
	totalPoint = 0;
	timePause = 0;
	totalTime = 0;
}
cGame::~cGame()
{
	for (int i = 0; i < liveObstacles.size(); i++)
	{
		delete liveObstacles[i];
	}
	for (int i = 0; i < livePeople.size(); i++)
	{
		delete livePeople[i];
	}
	for (int i = 0; i < environmentObject.size(); i++)
	{
		delete environmentObject[i];
	}
	liveObstacles.clear();
	livePeople.clear();
	environmentObject.clear();
	//cleanGame();
}
short cGame::getGameOrder()
{
	return gameOrder;
}


void cGame::updatePosObstacle()
{
	for (int i = 0; i < liveObstacles.size(); i++)
	{
		liveObstacles[i]->move();
	}
}


void cGame::MainGame() {
	isExit = false;
	isLoad = false;
	
	//resetTime();

	Sound::playSoundList();
	Sound::playBackGroundSound();
	//Sound::musicThread();	

	cDWindow rr(&window, { 504, 0 }, "panelinfo.txt", true);
	cLabel t1(&rr, { 10, 5 }, "SCORES", 1, Color::red, true);
	string point = to_string(totalPoint);
	cLabel t2(&rr, { 10, 15 }, point, 2, Color::red, true);

	listWidget.push_back(&rr);
	rr.show();
	listLabel.push_back(&t1);
	t1.show();
	listLabel.push_back(&t2);
	t2.unshow();
	int i = 0;
	thread drawingThread(&cGameEngine::maindraw, this);


	while (!isExit) {
		if (hasSuddenStop)
		{
			if (cooldown > 0)
				cooldown--;
			else {
				cooldown = 200;
				suddenStop = !suddenStop;
				for (cEnvironment* p : environmentObject)
				{
					if (p->hasEvent)
					{
						p->playEvent();
					}
				}
			}
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			GamePausePanel();
		}

		if (GetAsyncKeyState(0x51) & 0x8000) {
			isExit = true;
			break;
		}
	
		environmentImpact();
		
		if (!isLose)
			isImpact();
		if (isLose)
		{
			cGameEngine::fillScreenWithLastFrame(true);
			Sound::pauseCurrentSound();
			Sleep(2000);
			cDWindow pa(&window, { 101, 31 },"panelfailed.txt");
			pa.show();
			while (true)
			{
				if (GetAsyncKeyState(0x51) & 0x8000)
				{
					tomainMenu = true;
					break;
				}

				if (GetAsyncKeyState(0x11) & 0x8000)
				{
					for (int i = 0; i < livePeople.size(); i++)
					{
						delete livePeople[i];
					}
					livePeople.resize(0);
					spawnPeople();
					totalPoint = 0;
					resetTime();
					t2.updateText(to_string(totalPoint));
					isLose = false;
					isPause = false;
					Sound::playBackGroundSound();
					break;
				}
			}
			pa.unshow();
		}
		
		if (livePeople[0]->passLevel) {
			nextLevel();
			t2.updateText(to_string(totalPoint));
			livePeople[0]->passLevel = false;
		}
		Sleep(10);
	}
	drawingThread.join();
	clearObjects(true, true);
	Sound::pauseCurrentSound();
}

void onLoad1(cGame* pGame) {
	pGame->load("save1.txt");
}
void onLoad2(cGame* pGame) {
	pGame->load("save2.txt");
}
void onLoad3(cGame* pGame) {
	pGame->load("save3.txt");
}

void cGame::LoadGame()
{
	// check file is save or not
	// if not icon = empty map
	// if yes icon = map saved

	/*string mapSaved[3] = { "emptyLoadIcon.txt", "emptyLoadIcon.txt" , "emptyLoadIcon.txt" };
	string saved[3] = { "save1.txt" ,"save2.txt" , "save3.txt" };
	string labelText[3] = { "empty", "empty", "empty" };
	ifstream ifs;
	for (int i = 0; i < 3; i++) {
		ifs.open("Save//" +saved[i]);
		if (ifs.is_open()) {
			Time t;
			ifs >> t;
			labelText[i] = t.dateString();
			int j;
			for (int k = 0; k < 3; k++) {
				ifs >> j;
			}
			if (j == 0) {
				mapSaved[i] = "jungleMapIcon.txt";
			}
			else if (j == 1) {
				mapSaved[i] = "cityMapIcon.txt";
			}
			else if (j == 2) {
				mapSaved[i] = "beachMapIcon.txt";
			}
			ifs.close();
		}
	}

		cDWindow loadWindow(&cGameEngine::pWindow, { 200, 40 }, "loadWindow", "LoadPanel.txt");
		loadWindow.show();

		cButton button1(&loadWindow, { 10, 25 }, "button1", mapSaved[0], 2, onLoad1);
		cButton button2(&loadWindow, { 10, 50 }, "button2", mapSaved[1], 2, onLoad2);
		cButton button3(&loadWindow, { 10, 75 }, "button2", mapSaved[2], 2, onLoad3);
		string label[3] = { "save1", "save2", "save3" };
		cLabel Label1(&button1, { 5, 1 }, label[0], labelText[0], 1, Color::bright_white);
		cLabel Label2(&button2, { 5, 1 }, label[1], labelText[1], 1, Color::bright_white);
		cLabel Label3(&button3, { 5, 1 }, label[2], labelText[2], 1, Color::bright_white);
		cButton buttonList[] = { button1, button2, button3 };
		cLabel labelList[] = { Label1, Label2, Label3 };
		int x = 0;
		for (int i = 0; i < 3; i++) {
			buttonList[i].show();
			labelList[i].show();
		}

		buttonList[0].onSelect();
		while (true) {
			if (GetAsyncKeyState(0x51) < 0 && 0x8000)
				break;
			if (GetAsyncKeyState(0x0D) < 0 && 0x8000)
			{
				buttonList[x].onDeSelect();
				for (int i = 0; i < 3; i++)
				{
					buttonList[i].unshow();
					labelList[i].unshow();
				}
				loadWindow.unshow();
				isLoad = true;
				buttonList[x].onEnter();
				break;
			}
			if (GetAsyncKeyState(VK_LEFT) && x > 0 && 0x8000)
			{
				buttonList[x].onDeSelect();
				x--;
				buttonList[x].onSelect();

			}
			if (GetAsyncKeyState(VK_RIGHT) && x < 2 && 0x8000)
			{
				buttonList[x].onDeSelect();
				x++;
				buttonList[x].onSelect();
			}
			for (int i = 0; i < 3; i++) {
				labelList[i].show();
			}
			Sleep(100);
		}
		cGameEngine::pGame.MainGame();*/
}



bool cGame::isImpact()
{
    for (int i = 0; i < livePeople.size(); i++)
    {
		int cnt = -1;
        if (livePeople[i] -> getState())
			for (cObstacle* obstacle : liveObstacles)
			{
				cnt++;
				if (obstacle->Box.isOverlap(livePeople[i]->mBox))
				{
					livePeople[i]->mState = false;
					Sleep(200);
					isPause = true;
					isLose = true;
					Sound::pauseCurrentSound();
					//Sound::playHitSound();
					cGameEngine::playEffect(obstacle, livePeople[i]);
					return true;
				}
			}
    }
	return false;
    //return livePeople.empty();
}

void cGame::randomStopThread()
{
    long long lastTime = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
    long long stopDuration = 0;
    long long stopCooldown = 0;
    short stopped = -1;
    
    vector<short> linePos;
    for (cObstacle * element : liveObstacles)
    {
        if (find(linePos.begin(), linePos.end(), element -> getPos().Y) == linePos.end())
        {
            linePos.push_back(element -> getPos().Y);
        }
    }
    int size = (int) linePos.size();
    
    srand((unsigned int) time(NULL));
    while (!isLose && !isExit)
    {
        if (isPause)
            continue;
        long long timePassed = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count() - lastTime;
        if (timePassed <= 0)
            continue;
        
        if (stopCooldown > 0)
        {
            if (stopDuration > 0)
            {
                stopDuration -= timePassed;
                if (stopDuration <= 0)
                {
                    for (cObstacle * element : liveObstacles)
                    {
                        if (element -> getPos().Y == stopped)
                            element -> resume();
                    }
                }
            }
            stopCooldown -= timePassed;
        }
        else
        {
            int roll = rand() % 30000 + 1;
            if (roll > timePassed)
                continue;
            roll = rand() % size;
            for (cObstacle * element : liveObstacles)
            {
                if (element -> getPos().Y == linePos[roll])
                    element -> stop();
            }
            
            roll = rand() % 10000;
            stopDuration = roll + 5000;
            stopCooldown = stopDuration + 10000;
        }
    }
}

void exit() {
	return;
}

void cGame::resumeFunction()
{	
	cDWindow panel(&window, { 204, 50 }, "panelcountdown.txt", true);
	cDWindow countdown[3] = {
		cDWindow(&panel, {28, 6}, "Count3.txt"),
		cDWindow(&panel, {28, 6}, "Count2.txt"),
		cDWindow(&panel, {20, 6}, "Count1.txt")

	};
	for (int i = 0; i < 3; i++)
	{
		countdown[i].show();
		Sleep(750);
		countdown[i].unshow();
	}
	timePauseEnd = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	timePause += (timePauseEnd - timePauseStart) / 1000;

	//string countDown[4] = { "Count3.txt", "Count2.txt", "Count1.txt", "GO.txt" };
	//for (int i = 0; i < 4; i++) {
	//	cButton temp(&cGameEngine::pWindow, { 240, 40 }, "temp", countDown[i], 0, doNothing);
	//	temp.show();
	//	Sleep(500);
	//	temp.unshow();
	//}

	
	//isPause = false;
	
}

//void cGame::resumeGame(cGame *pGame) {
//	// draw a box to count down 3 sec 
//	// then continue game
//	pGame->resumeFunction();
//	//continueDrawAnimal();
//}


void cGame::save(string fileName) {
	//ofstream ofs("Save//" + fileName);
	//if (!ofs.is_open())
	//	return;

	//Time time;
	//time.getTime();
	//ofs << time << endl;

	//ofs << gameOrder << " " << gameLevel << " " << map << " " << totalPoint << " " << totalTime << " " << timePause << endl;
	//// people and their position
	//ofs << livePeople.size() << endl;
	//for (cPeople* element : livePeople)
	//{
	//	ofs << element->getPos().X << " " << element->getPos().Y << endl;
	//}

	//// obstacles and their position
	//int obstacleCount = (int)liveObstacles.size();

	//ofs << obstacleCount << endl;

	//for (int i = 0; i < obstacleCount; i++)
	//{
	//	ofs << liveObstacles[i]->getType() << " " << liveObstacles[i]->getPos().X << " " << liveObstacles[i]->getPos().Y << " " << liveObstacles[i]->getSpeed() << endl;
	//}

	///*int environmentCount = (int)environmentObject.size();
	//ofs << environmentCount << endl;
	//for (int i = 0; i < environmentCount; i++)
	//{
	//	ofs << environmentObject[i]->getType() << " " << environmentObject[i]->getPos().X << " " << environmentObject[i]->getPos().Y << " " << environmentObject[i]->getSpeed() << endl;
	//}*/

	//ofs.close();


	//string filename = "Save//" + fileName; // placeholder filename

	/*ofstream ofs;
	ofs.open(filename, ios::binary);


	Time time;
	time.getTime();
	ofs << time;
	

	ofs.write((char*)&gameOrder, sizeof(short));
	ofs.write((char*)&gameLevel, sizeof(short));
	ofs.write((char*)&map, sizeof(int));
	ofs.write((char*)&totalPoint, sizeof(long));
	ofs.write((char*)&totalTime, sizeof(double));

	short* peoplePosition = new short[gameOrder * 2];
	int count = 0;
	for (cPeople* element : livePeople)
	{
		peoplePosition[count] = element->getPos().X;
		count++;
		peoplePosition[count] = element->getPos().Y;
		count++;
	}
	ofs.write((char*)peoplePosition, sizeof(short) * gameOrder * 2);
	delete[] peoplePosition;
	peoplePosition = nullptr;

	int obstacleCount = (int)liveObstacles.size();
	ofs.write((char*)&obstacleCount, sizeof(int));

	char* obstacleType = new char[obstacleCount];

	short* obstacleInfo = new short[obstacleCount * 3];
	for (int i = 0; i < obstacleCount; i++)
	{
		obstacleType[i] = liveObstacles[i]->getType();
		obstacleInfo[3 * i] = liveObstacles[i]->getPos().X;
		obstacleInfo[3 * i + 1] = liveObstacles[i]->getPos().Y;
		obstacleInfo[3 * i + 2] = liveObstacles[i]->getSpeed();
	}

	ofs.write(obstacleType, obstacleCount);
	ofs.write((char*)obstacleInfo, sizeof(short) * obstacleCount * 3);

	delete[] obstacleType;
	obstacleType = nullptr;
	delete[] obstacleInfo;
	obstacleInfo = nullptr;

	ofs.close();*/

	
}

void saveTest() {
	return;
}

void onSave1(cGame* pGame) {
	pGame->save("save1.txt");
}
void onSave2(cGame* pGame) {
	pGame->save("save2.txt");
}
void onSave3(cGame* pGame) {
	pGame->save("save3.txt");
}

/*void cGame::saveGame(cGame* pGame) {
	Time time[3];
	string mapSaved[3] = { "emptyLoadIcon.txt", "emptyLoadIcon.txt" , "emptyLoadIcon.txt" };
	string saved[3] = { "save1.txt" ,"save2.txt" , "save3.txt" };
	string labelText[3] = { "empty", "empty", "empty" };
	ifstream ifs;
	for (int i = 0; i < 3; i++) {
		ifs.open("Save//" + saved[i]);
		if (ifs.is_open()) {
			Time t;
			ifs >> t;
			labelText[i] = t.dateString();
			int j;
			for (int k = 0; k < 3; k++) {
				ifs >> j;
			}
			if (j == 1) {
				mapSaved[i] = "jungleIcon.txt";
				if (j == 0) {
					mapSaved[i] = "jungleMapIcon.txt";
				}
				else if (j == 1) {
					mapSaved[i] = "cityMapIcon.txt";
				}
				else if (j == 2) {
					mapSaved[i] = "beachMapIcon.txt";
				}
				else if (j == 3) {
					mapSaved[i] = "beachIcon.txt";
				}
				ifs.close();
			}
		}
	}


	cDWindow saveWindow(&cGameEngine::pWindow, { 100, 30 }, "saveWindow", "loadPanel.txt");
	saveWindow.show();

	cButton button1(&saveWindow, { 10, 25 }, "button1", mapSaved[0], 2, onSave1);
	cButton button2(&saveWindow, { 10, 50 }, "button2", mapSaved[1], 2, onSave2);
	cButton button3(&saveWindow, { 10, 75 }, "button2", mapSaved[2], 2, onSave3);
	string label[3] = { "save1", "save2", "save3" };
	cLabel Label1(&button1, { 0, 1 }, label[0], labelText[0], 1, Color::bright_white);
	cLabel Label2(&button2, { 0, 1 }, label[1], labelText[1], 1, Color::bright_white);
	cLabel Label3(&button3, { 0, 1 }, label[2], labelText[2], 1, Color::bright_white);
	cButton buttonList[] = { button1, button2, button3 };
	cLabel labelList[] = { Label1, Label2, Label3 };
	int x = 0;
	for (int i = 0; i < 3; i++) {
		buttonList[i].show();
		labelList[i].show();
	}

	buttonList[0].onSelect();
	while (true) {
		if (GetAsyncKeyState(0x51) < 0 && 0x8000)
			break;
		if (GetAsyncKeyState(0x0D) < 0 && 0x8000)
		{
			buttonList[x].onDeSelect();
			for (int i = 0; i < 3; i++)
			{
				buttonList[i].unshow();
				labelList[i].unshow();
			}
			saveWindow.unshow();
			buttonList[x].onEnter();
			break;
		}
		if (GetAsyncKeyState(VK_LEFT) && x > 0 && 0x8000)
		{
			buttonList[x].onDeSelect();
			x--;
			buttonList[x].onSelect();

		}
		if (GetAsyncKeyState(VK_RIGHT) && x < 2 && 0x8000)
		{
			buttonList[x].onDeSelect();
			x++;
			buttonList[x].onSelect();
		}
		for (int i = 0; i < 3; i++) {
			labelList[i].show();
		}
		Sleep(100);
	}

}*/



//cGame::cGame (string saveFile) // load game (create cGame object) from save file
//{
//    ifstream ifs;
//    ifs.open(saveFile, ios::binary);
//	Time t;
//	ifs >> t;
//    ifs.read((char *) &gameOrder, sizeof(short));
//    ifs.read((char *) &gameLevel, sizeof(short));
//    ifs.read((char *) &map, sizeof(int));
//    ifs.read((char *) &totalPoint, sizeof(long));
//    ifs.read((char *) &totalTime, sizeof(double));
//    
//    short * peoplePosition = new short [gameOrder * 2];
//    ifs.read((char *) peoplePosition, sizeof(short) * gameOrder * 2);
//    livePeople.resize(gameOrder);
//    for (short i = 0; i < gameOrder; i++)
//    {
//        livePeople[i] = new cPeople({peoplePosition[2 * i], peoplePosition[2 * i + 1]});
//    }
//    delete [] peoplePosition;
//    peoplePosition = nullptr;
//    
//    int obstacleCount;
//    ifs.read((char *) &obstacleCount, sizeof(int));
//    
//    char * obstacleType = new char [obstacleCount];
//    short * obstacleInfo = new short [obstacleCount * 3];
//    ifs.read(obstacleType, obstacleCount);
//    ifs.read((char *) obstacleInfo, obstacleCount * 3);
//    ifs.close();
//    
//    liveObstacles.resize(obstacleCount);
//    for (int i = 0; i < obstacleCount; i++)
//    {
//        COORD pos = {obstacleInfo[3 * i], obstacleInfo[3 * i + 1]};
//       // liveObstacles[i] = cObstacle::constructObject(obstacleType[i], pos, obstacleInfo[3 * i + 2]);
//    }
//    
//    delete [] obstacleType;
//    obstacleType = nullptr;
//    delete [] obstacleInfo;
//    obstacleInfo = nullptr;
//}

void cGame::spawnPeople() {
	for (int i = 0; i < gameOrder; i++) {
		livePeople.push_back(new cPeople());
	}
}

void cGame::spawnObstacle(const string& levelFile) {
	
	ifstream levelIn;
	levelIn.open(LevelPrefix + levelFile);
	int linecount = 0;
	short lineoffset[] = { 19, 55, 91, 127};
	while (!levelIn.eof())
	{
		int objcount;
		levelIn >> objcount;
		int spd;
		levelIn >> spd;
		short cX = 0;
		for (int i = 0; i < objcount; i++)
		{
			char objname;
			levelIn >> objname;

			short offsetF, offsetB, offsetY;
			levelIn >> offsetF >> offsetB >> offsetY;
			cObstacle* pObj = nullptr;
			switch (objname)
			{
			case 'l': pObj = new cLion({ short(cX + offsetF), short(lineoffset[linecount] - offsetY) }, spd); break;
			case 'r': pObj = new cRhino({ short(cX + offsetF), short(lineoffset[linecount] - offsetY) }, spd); break;
			case 'c': pObj = new cCrocodile({ short(cX + offsetF), short(lineoffset[linecount] - offsetY) }, spd); break;
			
			default:
				break;
			}

			if (pObj)
			{
				liveObstacles.push_back(pObj);
				cX += pObj->pMotionFrame->width + offsetF + offsetB;;
				pObj = nullptr;
			}
		}
		linecount++;
	}
	levelIn.close();
}

bool cGame::isFinishLevel() {
	return (livePeople[0]->getPos().Y <= 2);
	
}

double cGame::calculateTime() {
	double time = timeEnd - timeStart + timePauseStart - timePauseEnd;
	return time / 1000.0;
	return 0;
}

void cGame::resetTime() {
	this->timeStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	this->timeEnd = timeStart;
	this->timePauseStart = 0;
	this->timePauseEnd = 0;
}

void cGame::calculatePoint() {
	this->timeEnd = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	int bonus[6] = { 120, 70, 35, 15, 5, 0 };
	int count = min(int(calculateTime() / 5), 5);
	cout << "Time: " << calculateTime() << endl;
	cout << "Bonus: " << bonus[count] << endl;
	cout << "Total point: " << totalPoint << endl;
	totalTime += calculateTime();
	totalPoint += 100 + bonus[count];
	resetTime();
}

void foo()
{}

void cGame::nextLevel() {
	this->gameLevel++;
	//gameMap::nextMap();
	calculatePoint();
	// set position of people
	//for (int i = 0; i < livePeople.size(); i++) {
	//	livePeople[i]->setPos({ 0, 145 });
	//	for (int i = 0; i < livePeople[i]->mBoxes.size(); i++)
	//	{
	//		livePeople[i]->mBoxes[i].set({ short(livePeople[i]->topleft.X), short(livePeople[i]->topleft.Y) }, { short(livePeople[i]->pTexture->getWidth() + livePeople[i]->topleft.X - 1), short(livePeople[i]->pTexture->getHeight() + livePeople[i]->topleft.Y - 1) });
	//	}
	//};
	// respawn obstacle
	clearObjects();
	spawnObstacle(CreatedLevel[currentTheme][(currentPhase + 1) % CreatedLevel[currentTheme].size()]);
}

void cGame::endlessMode() {
	//spawnPeople();
	//spawnObstacle();
	////resetTime();
	//thread drawingThread(&cGameEngine::pizzaDraw, this);
	//Sound::playSoundList();
	//Sound::playIntroSound();
	////Sound::musicThread();
	//while (true) {
	//	if (GetAsyncKeyState(0x50) < 0 && 0x8000) {
	//		pauseGame();
	//	}
	//	if (GetAsyncKeyState(0x53) < 0 && 0x8000) {
	//		resumeGame(&cGameEngine::pGame);
	//	}
	//	if (GetAsyncKeyState(0x51) < 0 && 0x8000) {
	//		// isExit = true;
	//		// save game Menu here
	//		// draw save game menu
	//		// can save or not 
	//		// if can save => save game
	//		// if not => continue game
	//	}
	//	if (GetAsyncKeyState(0x1B) < 0 && 0x8000) {
	//		isExit = true;
	//		// save game Menu here
	//		// draw save game menu
	//		// can save or not 
	//		// if can save => save game => exit game
	//		// if not => exit game
	//		break;
	//	}
	//	if (isImpact())
	//	{
	//		isLose = true;
	//		break;
	//	}
	//	for (int i = 0; i < gameOrder; i++) {
	//		livePeople[i]->move();
	//	}
	//	if (isFinishLevel()) {
	//		this->gameLevel++;
	//		calculatePoint();
	//		resetTime();
	//		srand(NULL);
	//		int random = rand() % 7 + 1;
	//		//gameMap::changeMap(BGIndex(random));
	//		for (int i = 0; i < livePeople.size(); i++) {
	//			livePeople[i]->setPos({ short(200 - 100 * i), 100 });
	//		}
	//		for (int i = 0; i < liveObstacles.size(); i++) {
	//			delete liveObstacles[i];
	//		}
	//		liveObstacles.clear();
	//		string src = "//Level//map_";
	//		string map[3] = { "jungle", "beach", "city" };
	//		srand(NULL);
	//		int rand_map = rand() % 3;
	//		src += map[rand_map] + "//.txt";
	//		spawnObstacle();
	//	}
	//	Sleep(10);
	//}
	//drawingThread.join();

}
void cGame::GameOver() {
	// draw game over animation // has  a box to know game point and time
	// draw game over menu has choices: exit game, start new game with same map, back to main menu

}
void cGame::GameWin() {
	// draw game win animation //
	// draw game win menu has choices: exit game, start new game with next map, back to main menu, save game score and time
}
void cGame::load(string fileName)
{
	
	/*ifstream ifs("Save//" + fileName);
	if (!ifs.is_open())
		return;
	Time time;
	ifs >> time;

	ifs >> cGameEngine::pGame.gameOrder >> cGameEngine::pGame.gameLevel >> cGameEngine::pGame.map >> cGameEngine::pGame.totalPoint >> cGameEngine::pGame.totalTime >> cGameEngine::pGame.timePause;

	cGameEngine::pGame.livePeople.resize(cGameEngine::pGame.gameOrder);
	int dump;
	ifs >> dump;
	for (int i = 0; i < cGameEngine::pGame.gameOrder; i++)
	{
		short x, y;
		ifs >> x >> y;
		cGameEngine::pGame.livePeople[i] = new cPeople({ x, y });
	}

	int obstacleCount;
	ifs >> obstacleCount;

	cGameEngine::pGame.liveObstacles.resize(obstacleCount);
	for (int i = 0; i < obstacleCount; i++)
	{
		char type;
		short x, y, speed;
		ifs >> type >> x >> y >> speed;
		COORD pos = { x, y };
		cGameEngine::pGame.liveObstacles[i] = cGameEngine::createObject(type, pos, speed);
	}

	ifs.close();*/
}
void cGame::ScoreBoard() {
	// draw score board menu // has a box to show score and time of game
	// has choices: back to previous menu
}
void cGame::resetGame() {
	resetTime();
	totalPoint = 0;
	totalTime = 0;
	gameLevel = 1;
	gameOrder = 1;
	clearObjects(true);
	// game type ?
	/*if (gameType == 0) {
		MainGame();
	}
	else {
		endlessMode();
	}*/
	MainGame();
}
