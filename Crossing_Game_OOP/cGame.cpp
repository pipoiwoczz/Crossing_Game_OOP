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
		Sleep(100);
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
		// COORD X is pos Y and Y is direction
		vector<COORD> lanesPosition = getPositionLane();
		for (int i = 0; i < lanesPosition.size(); i++)
		{
			short posX = lanesPosition[i].Y ? 0 : 486;
			environmentObject.push_back(new cTrafficLight({ posX, lanesPosition[i].X }));
		}
		// get Traffic light
		hasSuddenStop = true;
		suddenStop = false;
	}
}

void cGame::prepareGame()
{
	clearObjects();
	spawnObstacle(CreatedLevel[currentTheme][currentPhase]);
	spawnEnvironment();
	spawnPeople();
}

void cGame::GamePlayPanel()
{	
	Time time[3];
	string mapSaved[3] = { "emptymapload.txt", "emptymapload.txt" , "emptymapload.txt" };
	string mapIconSaved[3] = { "iconemptyload.txt", "iconemptyload.txt", "iconemptyload.txt" };
	string saved[3] = { "Save//save1.txt" ,"Save//save2.txt" , "Save//save3.txt" };
	string labelText[3] = { "Empty", "Empty", "Empty" };
	ifstream ifs;
	for (int i = 0; i < 3; i++) {
		ifs.open(saved[i]);
		if (ifs.is_open()) {
			Time t;
			ifs >> t;
			labelText[i] = t.dateString();
			int j;
			for (int k = 0; k < 3; k++) {
				ifs >> j;
			}
			if (j == 0) {
				mapSaved[i] = "junglemapload.txt";
				mapIconSaved[i] = "iconmapjungle.txt";
			}
			else if (j == 1) {
				mapSaved[i] = "beachmapload.txt";
				mapIconSaved[i] = "iconmapbeach.txt";
			}
			else if (j == 2) {
				mapSaved[i] = "citymapload.txt";
				mapIconSaved[i] = "iconmapcity.txt";
			}
			ifs.close();
		}
	}
	std::function<void()> panelFunct[1] = {
		[]() {
			game.GameNewGamePanel();
		},

	};

	tomainMenu = false;
	cDWindow panel(&mainMenu, { 30, 6 }, "panelplay.txt", true);
	cDWindow panelBackground(&panel, { 0, 0 }, "panelbackground.txt", false);

	cDWindow panelButton[4] = {
		cDWindow(&panel, {2, 22}, "buttonnewgame.txt", true),
		cDWindow(&panel, {2, 50}, mapSaved[0]),
		cDWindow(&panel, {2, 79}, mapSaved[1]),
		cDWindow(&panel, {2, 108}, mapSaved[2])
	};


	cButton panelIcon[3] = {
		cButton(&panel, { 2, 50 }, mapIconSaved[0], 1, true),
		cButton(&panel, { 2, 79 }, mapIconSaved[1], 1, true),
		cButton(&panel, { 2, 108 }, mapIconSaved[2], 1, true)
	};

	cLabel LabelDate[3][2]{
		{cLabel(&panel, { 117, 62 }, labelText[0], 1, Color::black, true),cLabel(&panelBackground, {117, 62}, labelText[0], 1, Color::black)},
		{cLabel(&panel, { 117, 91 }, labelText[0], 1, Color::black, true),cLabel(&panelBackground, {117, 91}, labelText[1], 1, Color::black)},
		{cLabel(&panel, { 117, 120 }, labelText[0], 1, Color::black, true),cLabel(&panelBackground, {117, 120}, labelText[2], 1, Color::black)}
	};


	cLabel LabelLoad[3][2]{
		{cLabel(&panel, { 117, 52 }, "LOAD 1", 1, Color::black, true),cLabel(&panelBackground,{117, 52}, "LOAD 1", 1, Color::black)},
		{cLabel(&panel, { 117, 81 }, "LOAD 2", 1, Color::black, true),cLabel(&panelBackground, {117, 81}, "LOAD 2", 1, Color::black)},
		{cLabel(&panel, { 117, 110 }, "LOAD 3", 1, Color::black, true),cLabel(&panelBackground, {117, 110}, "LOAD 3", 1, Color::black)}
	};

	int current = 0;
	panelButton[current].show();

	while (!tomainMenu)
	{
		if ((GetAsyncKeyState(VK_UP) & 0x8000) && current > 0)
		{
			panelButton[current].unshow();
			if (current != 0)
			{
				LabelLoad[current-1][0].show();
				LabelDate[current-1][0].show();
				panelIcon[current - 1].show();
			}
			panelIcon[current - 1].unshow();

			current--;

			panelButton[current].show();

			if (current != 0)
			{
				LabelLoad[current-1][1].show();
				LabelDate[current-1][1].show();
			}
		}
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && current < 3)
		{
			panelButton[current].unshow();
			if (current != 0)
			{
				LabelLoad[current - 1][0].show();
				LabelDate[current - 1][0].show();
				panelIcon[current - 1].show();
			}
			current++;

			panelButton[current].show();
			if (current != 0)
			{
				LabelLoad[current - 1][1].show();
				LabelDate[current - 1][1].show();
			}
			
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}

		if (GetAsyncKeyState(0x0D) & 0x8000)
		{
			if (current == 0) {
				panelFunct[current]();
			}
			else {
				load(saved[current - 1]);
			}
			mainMenu.show();
			panel.show();
			panelButton[current].show();
		}
		for (int i = 0; i < 3; i++) {
			LabelDate[i][0].show();
			LabelLoad[i][0].show();
			if (current == i + 1) {
				LabelDate[i][1].show();
				LabelLoad[i][1].show();
			}
		}
		Sleep(100);
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

	cLabel panelLabel[3] = {
		cLabel(&panel, { 140, 40 }, "JUNGLE", 1, Color::black, true),
		cLabel(&panel, { 140, 72 }, "BEACH", 1, Color::black, true),
		cLabel(&panel, { 140, 104 }, "CITY", 1, Color::black, true)
	};

	int current = 0;
	panelButton[current].onSelect();
	
	for (int i = 0; i < 3; i++) {
		panelButton[i].show();
		panelLabel[i].show();
	}
	
	while (true)
	{
		if (GetAsyncKeyState(VK_UP)  && current > 0)
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
		Sleep(100);
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
		Sleep(100);
		if (GetAsyncKeyState(0x0D) & 0x8000)
		{
			//panel.unshow();
			//panelButton[current].unshow();
			panelFunct[current]();
			if (current >= 3)
				break;
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
	Time time[3];
	string mapIconSaved[3] = { "iconemptyload.txt", "iconemptyload.txt" , "iconemptyload.txt" };
	string mapSaved[3] = { "emptymapload.txt", "emptymapload.txt", "emptymapload.txt" };
	string saved[3] = { "save1.txt" ,"save2.txt" , "save3.txt" };
	string labelText[3] = { "EMPTY", "EMPTY", "EMPTY" };
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
			if (j == 0) {
				mapIconSaved[i] = "iconmapjungle.txt";
				mapSaved[i] = "junglemapload.txt";
			}
			else if (j == 1) {
				mapIconSaved[i] = "iconmapbeach.txt";
				mapSaved[i] = "beachmapload.txt";
			}
			else if (j == 2) {
				mapIconSaved[i] = "iconmapcity.txt";
				mapSaved[i] = "citymapload.txt";
			}
			ifs.close();
		}
	}

	cDWindow panel(&window, { 133, 11 }, "panelsave.txt", true);
	
	cDWindow panelBackground(&panel, { 0, 0 }, "panelbackground.txt", false);

	cButton mapIcons[3]{
		cButton(&panel, {2, 42}, mapIconSaved[0], 1),
		cButton(&panel, {2, 72}, mapIconSaved[1], 1),
		cButton(&panel, {2, 102}, mapIconSaved[2], 1),
	};
	cButton slots[3]{
		cButton(&panel, {2, 42}, mapSaved[0], 1),
		cButton(&panel, {2, 72}, mapSaved[1], 1),
		cButton(&panel, {2, 102}, mapSaved[2], 1),
	};

	cLabel LabelDate[3][2]{
		{cLabel(&panel, { 117, 54 }, labelText[0], 1, Color::black, true),cLabel(&panelBackground, {117, 54}, labelText[0], 1, Color::black)},
		{cLabel(&panel, { 117, 83 }, labelText[0], 1, Color::black, true),cLabel(&panelBackground, {117, 83}, labelText[1], 1, Color::black)},
		{cLabel(&panel, { 117, 112 }, labelText[0], 1, Color::black, true),cLabel(&panelBackground, {117, 112}, labelText[2], 1, Color::black)}
	};


	cLabel LabelSave[3][2]{
		{cLabel(&panel, { 117, 44 }, "LOAD 1", 1, Color::black, true),cLabel(&panelBackground,{117, 44}, "LOAD 1", 1, Color::black)},
		{cLabel(&panel, { 117, 73 }, "LOAD 2", 1, Color::black, true),cLabel(&panelBackground, {117, 73}, "LOAD 2", 1, Color::black)},
		{cLabel(&panel, { 117, 102 }, "LOAD 3", 1, Color::black, true),cLabel(&panelBackground, {117, 102}, "LOAD 3", 1, Color::black)}
	};

	panel.show();
	for (int i = 0; i < 3; i++) {
		mapIcons[i].show();
	}


	int x = 0;
	int current = 0;
	slots[current].show();
	while (true)
	{
		if (GetAsyncKeyState(VK_DOWN) < 0 && current < 2)
		{
			slots[current].unshow();
			mapIcons[current].show();
			current++;
			slots[current].show();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && current > 0)
		{
			slots[current].unshow();
			mapIcons[current].show();
			current--;
			slots[current].show();
		}
		for (int i = 0; i < 3; i++) {
			if (current == i) {
				LabelDate[i][1].show();
				LabelSave[i][1].show();
				continue;
			}
			LabelDate[i][0].show();
			LabelSave[i][0].show();
		}
		Sleep(100);
		if (GetAsyncKeyState(0x0D) & 0x8000)
		{
			slots[current].unshow();
			panel.unshow();
			save("Save//" + saved[current]);
			break;
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}
	}
}

void cGame::GameLoadPanel()
{
	Time time[3];
	string mapIconSaved[3] = { "iconemptyload.txt", "iconemptyload.txt" , "iconemptyload.txt" };
	string mapSaved[3] = { "emptymapload.txt", "emptymapload.txt", "emptymapload.txt" };
	string saved[3] = { "save1.txt" ,"save2.txt" , "save3.txt" };
	string labelText[3] = { "EMPTY", "EMPTY", "EMPTY" };
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
			if (j == 0) {
				mapIconSaved[i] = "iconmapjungle.txt";
				mapSaved[i] = "junglemapload.txt";
			}
			else if (j == 1) {
				mapIconSaved[i] = "iconmapbeach.txt";
				mapSaved[i] = "beachmapload.txt";
			}
			else if (j == 2) {
				mapIconSaved[i] = "iconmapcity.txt";
				mapSaved[i] = "citymapload.txt";
			}
			ifs.close();
		}
	}

	cDWindow panel(&window, { 133, 11 }, "panelload2.txt", true);

	cDWindow panelBackground(&panel, { 0, 0 }, "panelbackground.txt", false);

	cButton mapIcons[3]{
		cButton(&panel, {2, 42}, mapIconSaved[0], 1),
		cButton(&panel, {2, 72}, mapIconSaved[1], 1),
		cButton(&panel, {2, 102}, mapIconSaved[2], 1),
	};
	cButton slots[3]{
		cButton(&panel, {2, 42}, mapSaved[0], 1),
		cButton(&panel, {2, 72}, mapSaved[1], 1),
		cButton(&panel, {2, 102}, mapSaved[2], 1),
	};

	cLabel LabelDate[3][2]{
		{cLabel(&panel, { 117, 54 }, labelText[0], 1, Color::black, true),cLabel(&panelBackground, {117, 54}, labelText[0], 1, Color::black)},
		{cLabel(&panel, { 117, 83 }, labelText[0], 1, Color::black, true),cLabel(&panelBackground, {117, 83}, labelText[1], 1, Color::black)},
		{cLabel(&panel, { 117, 112 }, labelText[0], 1, Color::black, true),cLabel(&panelBackground, {117, 112}, labelText[2], 1, Color::black)}
	};


	cLabel LabelLoad[3][2]{
		{cLabel(&panel, { 117, 44 }, "LOAD 1", 1, Color::black, true),cLabel(&panelBackground,{117, 44}, "LOAD 1", 1, Color::black)},
		{cLabel(&panel, { 117, 73 }, "LOAD 2", 1, Color::black, true),cLabel(&panelBackground, {117, 73}, "LOAD 2", 1, Color::black)},
		{cLabel(&panel, { 117, 102 }, "LOAD 3", 1, Color::black, true),cLabel(&panelBackground, {117, 102}, "LOAD 3", 1, Color::black)}
	};

	panel.show();
	for (int i = 0; i < 3; i++) {
		mapIcons[i].show();
	}


	int x = 0;
	int current = 0;
	slots[current].show();
	while (true)
	{
		if (GetAsyncKeyState(VK_DOWN) < 0 && current < 2)
		{
			slots[current].unshow();
			mapIcons[current].show();
			current++;
			slots[current].show();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && current > 0)
		{
			slots[current].unshow();
			mapIcons[current].show();
			current--;
			slots[current].show();
		}
		for (int i = 0; i < 3; i++) {
			if (current == i) {
				LabelDate[i][1].show();
				LabelLoad[i][1].show();
				continue;
			}
			LabelDate[i][0].show();
			LabelLoad[i][0].show();			
		}
		Sleep(100);
		if (GetAsyncKeyState(0x0D) & 0x8000)
		{
			slots[current].unshow();
			panel.unshow();
			load("Save//" + saved[current]);
			break;
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
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
	isPause = false;
	isExit = false;
	isLoad = false;
	hasSuddenStop = false;
	suddenStop = false;
	
	//resetTime();

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





bool cGame::isImpact()
{
    for (int i = 0; i < livePeople.size(); i++)
    {
		int cnt = -1;
        if (livePeople[i] -> getState()) // check only for alive players
			for (cObstacle* obstacle : liveObstacles)
			{
				cnt++;
				if (obstacle->Box.isOverlap(livePeople[i]->mBox)) // check overlap with each obstacles on screen
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
    //setup clocks
    long long lastTime = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
    long long stopDuration = 0;
    long long stopCooldown = 0;
    short stopped = -1; //indicate which line is stopped, if any
    
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
                    //stopped = -1;
                }
            }
            stopCooldown -= timePassed;
            // (sleep until cooldown is over)
            //Sleep(stopCooldown);
        }
        else
        {
            int roll = rand() % 30000 + 1; // randomly determines if something will stop - chance is (1/30000) * [ms passed] --- can also be changed to always stop after a set interval
            if (roll > timePassed)
            {
                // (sleep until next frame)
                //Sleep(16);
                continue;
            }
            roll = rand() % size; // randomly determines which line will be stopped
            for (cObstacle * element : liveObstacles)
            {
                if (element -> getPos().Y == linePos[roll])
                    element -> stop();
            }
            
            roll = rand() % 10000; // randomly determines stop duration (from 5 - 15s)
            stopDuration = roll + 5000;
            stopCooldown = stopDuration + 10000;
            // (sleep until next frame)
            //Sleep(16);
        }
    }
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

	
}




void cGame::save(string fileName) {
	ofstream ofs(fileName);
	if (!ofs.is_open())
		return;

	Time time;
	time.getTime();
	ofs << time << endl;

	ofs << gameOrder << " " << gameLevel << " " << currentTheme << " " << currentPhase << " " << totalPoint << " " << totalTime << " " << timePause << endl;
	// people and their position
	ofs << livePeople.size() << endl;
	for (cPeople* element : livePeople)
	{
		ofs << element->getPos().X << " " << element->getPos().Y << endl;
	}

	// obstacles and their position
	int obstacleCount = (int)liveObstacles.size();

	ofs << obstacleCount << endl;

	for (int i = 0; i < obstacleCount; i++)
	{
		ofs << liveObstacles[i]->getType() << " " << liveObstacles[i]->getPos().X << " " << liveObstacles[i]->getPos().Y << " " << liveObstacles[i]->getSpeed() << endl;
	}

	ofs.close();


	
}

void saveTest() {
	return;
}


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

			short offsetF, offsetB;
			levelIn >> offsetF >> offsetB;
			cObstacle* pObj = nullptr;
			switch (objname)
			{
			case 'l': pObj = new cLion({ short(cX + offsetF), short(lineoffset[linecount]) }, spd); break;
			case 'r': pObj = new cRhino({ short(cX + offsetF), short(lineoffset[linecount]) }, spd); break;
			case 'c': pObj = new cCrocodile({ short(cX + offsetF), short(lineoffset[linecount]) }, spd); break;
			
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
	game.clearObjects(true, true);

	isLoad = true;
	ifstream ifs(fileName);
	if (!ifs.is_open())
		return;
	Time time;
	ifs >> time;

	ifs >> game.gameOrder >> game.gameLevel >> game.currentTheme >> game.currentPhase >> game.totalPoint >> game.totalTime >> game.timePause;

	game.livePeople.resize(game.gameOrder);
	int dump;
	ifs >> dump;
	for (int i = 0; i < game.gameOrder; i++)
	{
		short x, y;
		ifs >> x >> y;
		game.livePeople[i] = new cPeople({ x, y });
	}

	int obstacleCount;
	ifs >> obstacleCount;

	game.liveObstacles.resize(obstacleCount);
	for (int i = 0; i < obstacleCount; i++)
	{
		char type;
		short x, y, speed;
		ifs >> type >> x >> y >> speed;
		COORD pos = { x, y };
		switch (type)
		{
		case 'l':
			game.liveObstacles[i] = new cLion(pos, speed);
			break;
		case 'r':
			game.liveObstacles[i] = new cRhino(pos, speed);
			break;
		case 'c':
			game.liveObstacles[i] = new cCrocodile(pos, speed);
			break;
		default:
			break;
		}
	}

	ifs.close();
	gameMap::changeMapTheme(game.currentTheme);
	gameMap::currentMap = &gameMap::listMap[game.currentTheme][game.currentPhase];
	game.spawnEnvironment();	
	game.MainGame();
}
void cGame::ScoreBoard() {
	cDWindow screen(&window, { 0, 0 }, "leaderboard.txt", true);
	screen.show();
	Sleep(3000);
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

short cGame::getNumberOfLane() {
	int count = 0;
	for (int i = 0; i < liveObstacles.size(); i++) {
		if (count == 0) {
			count++;
		}
		for (int j = 0; j < i; j++) {
			if (j == i - 1) {
				count++;
			}
			if (liveObstacles[i]->getPos().Y == liveObstacles[j]->getPos().Y) {
				break;
			}
		}
	}
	return count;
}


vector<COORD> cGame::getPositionLane() {
	short n = getNumberOfLane();
	vector<COORD> position;
	position.resize(n);
	for (int i = 0; i < n; i++) {
		position[i].X = 0;
	}
	for (int i = 0; i < liveObstacles.size(); i++) {
		for (int j = 0; j < n; j++) {
			if (liveObstacles[i]->getPos().Y == position[j].X) {
				break;
			}
			if (j == n - 1 || position[j].X == 0) {
				position[j].X = liveObstacles[i]->getPos().Y;
				position[j].Y = liveObstacles[i]->getDirection();
			}
		}
	}
	return position;
}