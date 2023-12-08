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

void cGame::pizzaDraw()
{
	for (int i = 0; i < liveObstacles.size(); i++)
	{
		liveObstacles[i]->move();

		//if (!suddenStop)
		//{
		//	liveObstacles[i]->isStop = false;
		//	liveObstacles[i]->move();
		//}
		//else {
		//	liveObstacles[i]->isStop = true;
		//}
		cGameEngine::renderObstacle(liveObstacles[i]);


	}
	for (int i = 0; i < environmentObject.size(); i++)
	{
		cGameEngine::renderEnvironment(environmentObject[i]);
		environmentObject[i]->move();
	}

	//put people onto buffer
	for (int i = 0; i < livePeople.size(); i++)
	{
		livePeople[i]->move();
		cGameEngine::renderPeople(livePeople[i]);
	}


}
void cGame::collisionThread()
{
	while (!isExit)
	{
		if (!isLose && !isPause)
		{
			environmentImpact();

			if (!isLose)
				isImpact();

			if (isLose)
			{
				coinBonus = 0;
				cDWindow dieeffect[5]{
					cDWindow(&window, { 133, 11 }, "rip1.txt", false),
					cDWindow(&window, { 133, 11 }, "rip2.txt", false),
					cDWindow(&window, { 133, 11 }, "rip3.txt", false),
					cDWindow(&window, {133, 11 }, "rip4.txt", false),
					cDWindow(&window, {133, 11 }, "rip5.txt", false)
				};
				for (int i = 0; i < 5; i++)
				{
					dieeffect[i].show();
					Sleep(300);
				}
				Sleep(2000);
				GameDiePanel();
			}
			Sleep(10);
		}
	}
}
void cGame::drawThread()
{
	while (!isExit)
	{
		if (!isLose && !isPause)
		{
			cGameEngine::swapHandle();
			cGameEngine::refreshBackGround(false);
			pizzaDraw();
			updateInfo();
			gameMap::mapChangeTick();
			cGameEngine::fillScreen();
			Sleep(25);
		}
	}
}

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
		if ((GetKeyState(VK_UP) & 0x8000) && current > 0)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].unshow();
			current--;
			panelButton[current].show();
		}

		if ((GetKeyState(VK_DOWN) & 0x8000) && current < 3)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].unshow();
			current++;
			panelButton[current].show();
		}

		if (GetKeyState(0x0D) & 0x8000)
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
		cEnvironment* lily = new cLilyleaf({ 0, 75 }, 1, false);
		environmentObject.push_back(lily);

		environmentObject.push_back(new cRiver(73, lily));
		lily = new cLilyleaf({ 30, 57 }, 1, false);
		environmentObject.push_back(lily);
		environmentObject.push_back(new cRiver(55, lily));

	}
	else if (currentTheme == 1)
	{

	}
	else if (currentTheme == 2)
	{
		// COORD X is pos Y and Y is direction

		for (int i = 0; i < obstacleLanes.size(); i++)
		{
			short posX = obstacleLanes[i].X ? 0 : 486;
			environmentObject.push_back(new cTrafficLight({ posX, obstacleLanes[i].Y }));
		}
		// get Traffic light
		hasSuddenStop = true;
	}
}

void cGame::prepareGame()
{
	clearObjects();
	spawnObstacle(CreatedLevel[currentTheme][currentPhase]);
	spawnEnvironment();
	spawnCoin();
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

	cDWindow panelButton[4]{
		cDWindow(&panel, { 2, 22 }, "buttonnewgame.txt", true),
		cDWindow(&panel, { 2, 50 }, mapSaved[0]),
		cDWindow(&panel, { 2, 79 }, mapSaved[1]),
		cDWindow(&panel, { 2, 108 }, mapSaved[2])
	};

	cButton panelIcon[3] = {
	cButton(&panel, { 2, 50 }, mapIconSaved[0], 1, true),
	cButton(&panel, { 2, 79 }, mapIconSaved[1], 1, true),
	cButton(&panel, { 2, 108 }, mapIconSaved[2], 1, true)
	};

	cLabel LabelDate[3][2]{
		{cLabel(&panel, { 117, 60 }, labelText[0], 1, Color::black, true), cLabel(&panelButton[1], {115, 10}, labelText[0], 1, Color::black)},
		{cLabel(&panel, { 117, 89}, labelText[1], 1, Color::black, true), cLabel(&panelButton[2], {115, 10}, labelText[1], 1, Color::black)},
		{cLabel(&panel, { 117, 118 }, labelText[2], 1, Color::black, true), cLabel(&panelButton[3], {115, 10}, labelText[2], 1, Color::black)}
	};
	cLabel LabelLoad[3][2]{
		{cLabel(&panel, { 117, 50 }, "LOAD 1", 1, Color::black, true), cLabel(&panelButton[1], { 115, 1 }, "LOAD 1", 1, Color::black)},
		{cLabel(&panel, { 117, 79 }, "LOAD 2", 1, Color::black, true), cLabel(&panelButton[2], { 115, 1 }, "LOAD 2", 1, Color::black)},
		{cLabel(&panel, { 117, 108 }, "LOAD 3", 1, Color::black, true), cLabel(&panelButton[3], { 115, 1 }, "LOAD 3", 1, Color::black)}
	};


	int current = 0;
	panelButton[current].show();

	while (!tomainMenu)
	{
		if ((GetKeyState(VK_UP) & 0x8000) && current > 0)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].unshow();
			if (current != 0)
			{
				LabelLoad[current-1][0].show();
				LabelDate[current-1][0].show();
				panelIcon[current - 1].show();
			}

			current--;

			panelButton[current].show();
			if (current != 0)
			{
				LabelLoad[current-1][1].show();
				LabelDate[current-1][1].show();
				
			}
		}
		if ((GetKeyState(VK_DOWN) & 0x8000) && current < 3)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
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
		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
		Sleep(50);
		if (GetKeyState(0x0D) & 0x8000)
		{
			if (current == 0) {
				game.GameNewGamePanel();
				for (int i = 0; i < 3; i++)
				{
					LabelLoad[i][0].show();
					LabelDate[i][0].show();
					panelIcon[i].show();
				}
			}
			else {
				load(saved[current - 1]);
			}
			mainMenu.show();
			panel.show();
			panelButton[current].show();
		}
		Sleep(50);
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
		if ((GetKeyState(VK_UP) & 0x8000) && current > 0)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].onDeSelect();
			current--;
			panelButton[current].onSelect();
		}
		if ((GetKeyState(VK_DOWN) & 0x8000) && current < 2)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].onDeSelect();
			current++;
			panelButton[current].onSelect();
		}
		Sleep(75);
		if (GetKeyState(0x51) & 0x8000)
			break;
		if (GetKeyState(0x0D) & 0x8000)
		{
			gameMap::changeMapTheme(current);
			currentTheme = current;
			currentPhase = 0;
			prepareGame();
			MainGame();
			break;
		}
		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
		Sleep(50);
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
		if ((GetKeyState(VK_DOWN) & 0x8000) && current < 5)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].unshow();
			current++;
			panelButton[current].show();
		}
		if ((GetKeyState(VK_UP) & 0x8000) && current > 0)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].unshow();
			current--;
			panelButton[current].show();
		}
		Sleep(50);
		if (GetKeyState(0x0D) & 0x8000)
		{
			//panel.unshow();
			//panelButton[current].unshow();
			panelFunct[current]();
			panel.show();
			panelButton[current].show();
		}
		Sleep(50);
	}
}

void cGame::GameSettingsPanel()
{
	cDWindow panel(&window, { 122, 11 }, "panelsettings.txt", true);
	void (*panelFunct[2][2])() = {
		{Sound::reduceSoundBackground, Sound::increaseSoundBackground},
		{Sound::reduceEffectSound, Sound::increaseEffectSound},
	};
	int (*getVolume[2])() = { Sound::getCurrentMusicVolume, Sound::getCurrentEffectVolume };

	cLabel panelInfo[2][2] = {
		{cLabel(&panel, { 30, 30 }, "Music Volume", 1, Color::black, true), cLabel(&panel, { 177, 30 }, to_string(getVolume[0]() / 10), 1, Color::black,true)},
		{cLabel(&panel, { 30 , 40 }, "Effect Volume", 1, Color::black, true), cLabel(&panel, { 177, 40 }, to_string(getVolume[1]() / 10), 1, Color::black, true)}
	};

	cButton buttonPanel[2][2]{
		{
			cButton(&panel, { 20, 50 }, "rabbitchoose1.txt", 1, true),
			cButton(&panel, { 20, 50 }, "rabbitchoose2.txt", 1, false)
		},
		{
			cButton(&panel, { 140, 50 }, "cubechoose1.txt", 1, true),
			cButton(&panel, { 140, 50 }, "cubechoose2.txt", 1, false) 
		}	
	};

	cDWindow selectarrow(&panel, { 210, 30 }, "arrowL.txt", true);
	short arrowPos[2] = { 30, 40 };
	int currentarrowpos = 0;

	while (true)
	{

		if ((GetKeyState(VK_DOWN) & 0x8000) && currentarrowpos < 2)
		{
			if (currentarrowpos < 1) 
			{
				Sound::playSoundEffect(SoundEffect::menuMove);
				currentarrowpos++;
				selectarrow.unshow();
				selectarrow.setOffset({ selectarrow.getOffset().X, arrowPos[currentarrowpos] });
				selectarrow.show();
			}
			 else if (currentarrowpos == 1)
			{
				Sound::playSoundEffect(SoundEffect::menuMove);
				currentarrowpos++;
				selectarrow.unshow();
				buttonPanel[0][0].show();
				buttonPanel[1][0].show();
				buttonPanel[currentarrowpos - 2][1].show();
				buttonPanel[currentarrowpos - 2][1].onSelect();
			}
		}
		if ((GetKeyState(VK_UP) & 0x8000) && currentarrowpos > 0)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			if (currentarrowpos < 2) {
				currentarrowpos--;
				selectarrow.unshow();
				selectarrow.setOffset({ selectarrow.getOffset().X, arrowPos[currentarrowpos] });
				selectarrow.show();
			}
			else if (currentarrowpos >= 2) {
				Sound::playSoundEffect(SoundEffect::menuMove);
				currentarrowpos = 1;
				selectarrow.setOffset({ selectarrow.getOffset().X, arrowPos[currentarrowpos] });
				selectarrow.show();		
				//buttonPanel[currentarrowpos - 2][1].show();
				buttonPanel[0][1].onDeSelect();
				buttonPanel[1][1].onDeSelect();
				buttonPanel[0][0].show();
				buttonPanel[1][0].show();
			}
		}
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (currentarrowpos < 2)
			{
				panelFunct[currentarrowpos][0]();
				panelInfo[currentarrowpos][1].updateText(to_string(getVolume[currentarrowpos]() / 10));
				Sleep(250);
			}
			else if (currentarrowpos == 3)  {
				Sound::playSoundEffect(SoundEffect::menuMove);
				buttonPanel[currentarrowpos - 2][1].onDeSelect();
				currentarrowpos--;
				selectarrow.unshow();
				buttonPanel[0][0].show();
				buttonPanel[1][0].show();
				buttonPanel[currentarrowpos - 2][1].show();
				buttonPanel[currentarrowpos - 2][1].onSelect();
			}
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (currentarrowpos < 2)
			{
				panelFunct[currentarrowpos][1]();
				panelInfo[currentarrowpos][1].updateText(to_string(getVolume[currentarrowpos]() / 10));
				Sleep(250);
			}
			else {
				if (currentarrowpos == 2) {
					Sound::playSoundEffect(SoundEffect::menuMove);
					buttonPanel[currentarrowpos - 2][1].onDeSelect();
					currentarrowpos++;
					selectarrow.unshow();
					buttonPanel[0][0].show();
					buttonPanel[1][0].show();
					buttonPanel[currentarrowpos - 2][1].show();
					buttonPanel[currentarrowpos - 2][1].onSelect();
				}
			}
		}
		Sleep(50);
		if ((GetKeyState(0x0D) & 0x8000)) {
			if (currentarrowpos >= 2) {
				bool change = (currentarrowpos == 3) ? false : false;
				cPeople::changeskin(change);
				break;
			}
		}
		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
		Sleep(50);
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

	cDWindow panel(&window, { 122, 11 }, "panelsave.txt", true);
	
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
		if ((GetKeyState(VK_DOWN) & 0x8000) && current < 2)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			slots[current].unshow();
			mapIcons[current].show();
			current++;
			slots[current].show();
		}
		if ((GetKeyState(VK_UP) & 0x8000) && current > 0)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
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
		Sleep(50);
		if (GetKeyState(0x0D) & 0x8000)
		{
			slots[current].unshow();
			panel.unshow();
			save("Save//" + saved[current]);
			break;
		}
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}
		Sleep(50);
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

	cDWindow panel(&window, { 122, 11 }, "panelload2.txt", true);

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
		if ((GetKeyState(VK_DOWN) & 0x8000) && current < 2)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			slots[current].unshow();
			mapIcons[current].show();
			current++;
			slots[current].show();
		}
		if ((GetKeyState(VK_UP) & 0x8000) && current > 0)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
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
		Sleep(50);
		if (GetKeyState(0x0D) & 0x8000)
		{
			slots[current].unshow();
			panel.unshow();
			load("Save//" + saved[current]);
			break;
		}
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}
		Sleep(50);
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
		if ((GetKeyState(VK_DOWN) & 0x8000) && currentarrowpos < 1)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			currentarrowpos++;
			selectarrow.unshow();
			selectarrow.setOffset({ selectarrow.getOffset().X, arrowPos[currentarrowpos] });
			selectarrow.show();
		}
		if ((GetKeyState(VK_UP) & 0x8000) && currentarrowpos > 0)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			currentarrowpos--;
			selectarrow.unshow();
			selectarrow.setOffset({ selectarrow.getOffset().X, arrowPos[currentarrowpos] });
			selectarrow.show();
		}
		Sleep(100);
		if (GetKeyState(0x0D) & 0x8000)
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
		else {
			if (environmentObject[j]->getType() == 'L')
			{
				for (int u = 0; u < livePeople.size(); u++)
				{
					if (environmentObject[j]->Box.isOverlap(livePeople[u]->mBox))
					{
						livePeople[u]->carryOffset = { short(environmentObject[j]->speed), 0};
					}
						
				}
			} 
			else {
				if (environmentObject[j]->getType() == '1') {
					for (int u = 0; u < livePeople.size(); u++)
					{
						if (environmentObject[j]->Box.isOverlap(livePeople[u]->mBox))
						{
							environmentObject[j]->hitSound();
							coinBonus += 30;
							delete environmentObject[j];
							environmentObject.erase(environmentObject.begin() + j);
						}
					}
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

void cGame::GameDiePanel() {
	cDWindow panel(&window, { 133, 11 }, "paneldie.txt", true);
	cButton panelButton[3]{
		cButton(&panel, { 3, 28 }, "buttondieretry.txt", 1),
		cButton(&panel, { 3, 59 }, "buttondieload.txt", 1),
		cButton(&panel, { 3, 90 }, "buttondieback.txt", 1)
	};

		std::function<void()> panelFunct[3] = {
		[]() {
			cGame::game.isPause = false;
			cGame::game.isLose = false;
			cGame::game.isExit = false;
			for (int i = 0; i < cGame::game.livePeople.size(); i++)
			{
				cGame::game.livePeople[i]->setPos({ short(0 + 100 * i), 145 });
				cGame::game.livePeople[i]->setState(true);
			}
		},
		[]() {
			game.GameLoadPanel();
		},
		[]() {
			game.currentPhase = 0;
			game.GameQuitPanel(); 
		}
	};

	int current = 0;
	panelButton[current].show();
	while (!tomainMenu)
	{
		if ((GetKeyState(VK_DOWN) & 0x8000) && current < 2)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].unshow();
			current++;
			panelButton[current].show();
		}
		if ((GetKeyState(VK_UP) & 0x8000) && current > 0)
		{
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].unshow();
			current--;
			panelButton[current].show();
		}
		Sleep(100);
		if (GetKeyState(0x0D) & 0x8000)
		{
			panelFunct[current]();
			if (current < 2)
				break;
			panel.show();
			panelButton[current].show();
		}
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
	coinBonus = 0;
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
	isLose = false;
	isPause = false;
	isExit = false;
	
	timeStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	
	//resetTime();

	//Sound::musicThread();	

	cDWindow rr(&window, { 504, 0 }, "panelinfo.txt", true);
	cDWindow howtoplay(&rr, { 0,110 }, "coin.txt", true);
	cLabel t1(&rr, { 10, 5 }, "SCORES", 1, Color::red, true);
	string point = to_string(totalPoint);
	cLabel t2(&rr, { 10, 15 }, point, 2, Color::red, true);
	cLabel t3(&rr, { 10, 25 }, "TIME", 1, Color::red, true);
	int time = int(calculateTime());
	string timeString = to_string(time);
	cLabel t4(&rr, { 10, 35 }, timeString, 2, Color::red, true);
	cLabel t5(&rr, { 10, 150 }, "ESC: PAUSE", 1, Color::red, true);

	cLabel t6(&rr, { 10, 45 }, "COINS", 1, Color::red, true);
	cLabel t7(&rr, { 10, 55 }, "30 x 0", 2, Color::red, true);
	int coinNow = 0;

	listWidget.push_back(&rr);
	rr.show();
	listWidget.push_back(&howtoplay);
	howtoplay.show();
	listLabel.push_back(&t1);
	t1.show();
	listLabel.push_back(&t2);
	t2.show();
	listLabel.push_back(&t3);
	t3.show();
	listLabel.push_back(&t4);
	t4.show();
	listLabel.push_back(&t5);
	t5.show();
	listLabel.push_back(&t6);
	t6.show();
	listLabel.push_back(&t7);
	t7.show();

	int i = 0;
	thread randomEventThread;
	if (hasSuddenStop)
	{
		randomEventThread = thread(&cGame::randomStopThread, this);
	}
	thread drawingThread;// = thread(&cGame::drawThread, this);
	thread collisionCheckingThread = thread(&cGame::collisionThread, this);
	if (cGameEngine::startDrawThread) {
		drawingThread = thread(&cGame::drawThread, this);
		cGameEngine::startDrawThread = false;
	}
	
	Sound::playTrack(SoundTrack::background);

	while (!isExit) {
		if (calculateTime() - time >= 1) {
			time = int(calculateTime());
			timeString = to_string(time);
			t4.updateText(timeString);
		}
		if (coinBonus != coinNow) {
			t7.updateText("30 x " + to_string(coinBonus / 30));
			coinNow = coinBonus;
		}
		
		if ((GetKeyState(VK_ESCAPE) & 0x8000) && !isLose)
		{
			Sound::pauseCurrentTrack();
			GamePausePanel();
			Sound::resumeCurrentTrack();
		}
	
		if (livePeople[0]->passLevel) {
			nextLevel();
			t2.updateText(to_string(totalPoint));
			livePeople[0]->passLevel = false;
			time = 0;
			coinNow = 0;
			t7.updateText("30 x " + to_string(coinBonus / 30));
			t4.updateText(to_string(time));
		}
		Sleep(10);
	}
	Sound::pauseCurrentTrack();
	drawingThread.join();
	collisionCheckingThread.join();
	cGameEngine::startDrawThread = true;
	if (hasSuddenStop)
	{
		randomEventThread.join();
	}
	clearObjects(true, true);
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
					Sound::pauseCurrentTrack();
					//Sound::playHitSound();
					cGameEngine::playEffect(obstacle, livePeople[i]);
					return true;
				}
			}
    }
	return false;
    //return livePeople.empty();
}

void cGame::updateInfo()
{
	for (int i = 0; i < listWidget.size(); i++)
	{
		listWidget[i]->show(false);
	}
	for (int i = 0; i < listLabel.size(); i++)
	{
		listLabel[i]->show(false);
	}
}

void cGame::randomStopThread()
{
	//setup clocks
	long long lastTime = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	long long stopDuration = 0;
	long long stopCooldown = 0;
	short stopped = -1; //indicate which line is stopped, if any
	//while (!isExit)
	//{
	//	if (isPause || isLose)
	//		continue;
	//	long long timePassed = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count() - lastTime;
	//	if (timePassed <= 0)
	//		continue;

	//	if (stopCooldown > 0)
	//	{
	//		if (stopDuration > 0)
	//		{
	//			stopDuration -= timePassed;
	//			if (stopDuration <= 0)
	//			{
	//				for (cObstacle* element : liveObstacles)
	//				{
	//					if (element->getPos().Y == stopped)
	//						element->resume();
	//				}
	//				//stopped = -1;
	//			}
	//		}
	//		stopCooldown -= timePassed;
	//		// (sleep until cooldown is over)
	//		//Sleep(stopCooldown);
	//	}
	//	else
	//	{
	//		int roll = rand() % 30000 + 1; // randomly determines if something will stop - chance is (1/30000) * [ms passed] --- can also be changed to always stop after a set interval
	//		if (roll > timePassed)
	//		{
	//			// (sleep until next frame)
	//			//Sleep(16);
	//			continue;
	//		}
	//		roll = rand() % obstacleLanes.size(); // randomly determines which line will be stopped
	//		for (cObstacle* element : liveObstacles)
	//		{
	//			if (element->getPos().Y == obstacleLanes[roll].Y)
	//				element->stop();
	//		}

	//		roll = rand() % 10000; // randomly determines stop duration (from 5 - 15s)
	//		stopDuration = roll + 5000;
	//		stopCooldown = stopDuration + 10000;
	//		// (sleep until next frame)
	//		//Sleep(16);
	//	}
	//}
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
		ofs << liveObstacles[i]->getType() << " " << liveObstacles[i]->getPos().X << " " << liveObstacles[i]->getPos().Y << " " << liveObstacles[i]->getSpeed() << " " << liveObstacles[i]->getDirection() << endl;
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

	int linecount;
	levelIn >> linecount;
	obstacleLanes.clear();
	obstacleLanes.resize(linecount);
	for (int i = 0; i < linecount; i++)
	{
		levelIn >> obstacleLanes[i].Y >> obstacleLanes[i].X;
	}

	int objcount;
	int spd;

	while (!levelIn.eof())
	{
		levelIn >> linecount;
		levelIn >> objcount;
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
			case 'l': pObj = new cLion({ short(cX + offsetF), obstacleLanes[linecount].Y }, spd, obstacleLanes[linecount].X); break;
			case 'r': pObj = new cRhino({ short(cX + offsetF), obstacleLanes[linecount].Y }, spd, obstacleLanes[linecount].X); break;
			case 'c': pObj = new cCrocodile({ short(cX + offsetF), obstacleLanes[linecount].Y }, spd, obstacleLanes[linecount].X); break;
			case 's': pObj = new cShark({ short(cX + offsetF), obstacleLanes[linecount].Y }, spd, obstacleLanes[linecount].X); break;
			case 'S': pObj = new cSurfer({ short(cX + offsetF), obstacleLanes[linecount].Y }, spd, obstacleLanes[linecount].X); break;

			case 'T': pObj = new cTruck({ short(cX + offsetF), obstacleLanes[linecount].Y }, spd, obstacleLanes[linecount].X); break;
			case 'M': pObj = new cMotorbike({ short(cX + offsetF), obstacleLanes[linecount].Y }, spd, obstacleLanes[linecount].X); break;
			case 'C': pObj = new cCar({ short(cX + offsetF), obstacleLanes[linecount].Y }, spd, obstacleLanes[linecount].X); break;
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
	timeEnd = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
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
	totalTime += calculateTime();
	totalPoint += 100 + bonus[count];
	totalPoint += coinBonus;
	resetTime();
}

void cGame::nextLevel() {
	this->gameLevel++;
	//gameMap::nextMap();
	calculatePoint();
	coinBonus = 0;
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
	//	if (GetKeyState(0x50) < 0 && 0x8000) {
	//		pauseGame();
	//	}
	//	if (GetKeyState(0x53) < 0 && 0x8000) {
	//		resumeGame(&cGameEngine::pGame);
	//	}
	//	if (GetKeyState(0x51) < 0 && 0x8000) {
	//		// isExit = true;
	//		// save game Menu here
	//		// draw save game menu
	//		// can save or not 
	//		// if can save => save game
	//		// if not => continue game
	//	}
	//	if (GetKeyState(0x1B) < 0 && 0x8000) {
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
		bool direction;
		ifs >> type >> x >> y >> speed >> direction;
		COORD pos = { x, y };
		switch (type)
		{
		case 'l':
			game.liveObstacles[i] = new cLion(pos, speed, direction);
			break;
		case 'r':
			game.liveObstacles[i] = new cRhino(pos, speed, direction);
			break;
		case 'c':
			game.liveObstacles[i] = new cCrocodile(pos, speed, direction);
			break;

		case 's':
			game.liveObstacles[i] = new cShark(pos, speed, direction);
			break;
		case 'S':
			game.liveObstacles[i] = new cSurfer(pos, speed, direction);
			break;

		case 'T': 
			game.liveObstacles[i] = new cTruck(pos, speed, direction);
			break;
		case 'M': 
			game.liveObstacles[i] = new cMotorbike(pos, speed, direction);
			break;
		case 'C': 
			game.liveObstacles[i] = new cCar(pos, speed, direction);
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

	vector < cDWindow*> listWindow;

	vector<COORD> winnerPosition = { {289, 94}, {206, 108}, {369, 112} };

	ifstream ifs("Save//leaderboard.txt");
	if (!ifs.is_open())
		return;
	int i = 0;
	while (!ifs.eof()) {
		int point;
		bool isRabbit;
		ifs >> point >> isRabbit;
		if (isRabbit)
			listWindow.push_back(new cDWindow(&screen, winnerPosition[i], "rabbit.txt", true));
		else
			listWindow.push_back(new cDWindow(&screen, winnerPosition[i], "cube.txt", true));
		i++;
	}

	ifs.close();

	while (true) {
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}
	}

	ifs.close();
}
void cGame::resetGame() {
	//resetTime();
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

//short cGame::getNumberOfLane() {
//	int count = 0;
//	for (int i = 0; i < liveObstacles.size(); i++) {
//		if (count == 0) {
//			count++;
//		}
//		for (int j = 0; j < i; j++) {
//			if (j == i - 1) {
//				count++;
//			}
//			if (liveObstacles[i]->getPos().Y == liveObstacles[j]->getPos().Y) {
//				break;
//			}
//		}
//	}
//	return count;
//}


//vector<COORD> cGame::getPositionLane() {
//	short n = getNumberOfLane();
//	vector<COORD> position;
//	position.resize(n);
//	for (int i = 0; i < n; i++) {
//		position[i].X = 0;
//	}
//	for (int i = 0; i < liveObstacles.size(); i++) {
//		for (int j = 0; j < n; j++) {
//			if (liveObstacles[i]->getPos().Y == position[j].X) {
//				break;
//			}
//			if (j == n - 1 || position[j].X == 0) {
//				position[j].X = liveObstacles[i]->getPos().Y;
//				position[j].Y = liveObstacles[i]->getDirection();
//			}
//		}
//	}
//	return position;
//}

void cGame::spawnCoin() {
	int random = rand() % 6 + 1; // number of coins from 1 to 6
	for (int i = 0; i < random; i++) {
		short y = 4 + (rand() % 9) * 18;
		short x = rand() % 475 + 1;
		for (int j = 0; j < environmentObject.size(); j++) {
			if (environmentObject[j]->getType() == '1') {
				while (environmentObject[j]->getPos().Y == y && abs(environmentObject[j]->getPos().X - x) <= 24) {
					y = 4 + (rand() % 9) * 18;
					x = rand() % 475 + 1;
				}
			}
		}
		environmentObject.push_back(new cCoin({ x, y }));
	}
}