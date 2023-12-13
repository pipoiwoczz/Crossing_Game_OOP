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

void cGame::teleport(cPeople* pPeople)
{
	if (pPeople->currentFrame == 0)
	{
		pPeople->topleft.Y -= 36;
		pPeople->topleft.Y = min(pPeople->topleft.Y, PlayBoxRect.Bottom - pPeople->pMotionFrame->getHeight() + 1);
	}
	else if (pPeople->currentFrame == 1)
	{
		pPeople->topleft.X += 48;
	}
	else if (pPeople->currentFrame == 2)
	{
		pPeople->topleft.Y += 36;
	}
	else {
		pPeople->topleft.X -= 48;
	}
}

int cGame::handlingSkillExec(cPeople* pPeople, long long &startTime)
{
	long long cur = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	long long pass = cur - startTime;
	int skillValue = pPeople->useSkill();
	if (pPeople->skillCooldown[0] == 0 && skillValue == 0)
	{
		pPeople->oldPos = pPeople->topleft;
		cGameEngine::playFlashEffect(pPeople->oldPos);
		teleport(pPeople);
		cGameEngine::renderPeople(pPeople);
		pPeople->skillCooldown[0] = defaultSkillCooldown[0];
		pPeople->used[0] = true;
		return 1;
	}

	if (pPeople->skillCooldown[0] > 0)
	{
		if (defaultSkillCooldown[0] - pPeople->skillCooldown[0] < 500)
			cGameEngine::playFlashEffect(pPeople->oldPos);

		pPeople->skillCooldown[0] = max(pPeople->skillCooldown[0]-pass, 0);
	}

	if (pPeople->skillCooldown[1] == 0 && skillValue == 1)
	{
		suddenStop = true;
		pPeople->used[1] = true;
		pPeople->skillCooldown[1] = defaultSkillCooldown[1];
		return 0;
	}

	if (pPeople->skillCooldown[1] > 0)
	{
		if (defaultSkillCooldown[1] - pPeople->skillCooldown[1] >= 3000)
			suddenStop = false;
		pPeople->skillCooldown[1] = max(pPeople->skillCooldown[1] - pass, 0);
	}
	startTime = cur;
	return -1;
}

void cGame::updateSkillState()
{

	if (mainPeople->skillCooldown[0] > 0)
	{
		listLabel[8] ->updateText(to_string(mainPeople->skillCooldown[0] / 1000));
	}
	else {
		listWidget[0]->show();
		listLabel[8] ->unshow();
	}

	if (mainPeople->skillCooldown[1] > 0)
	{
		listLabel[9]->updateText(to_string(mainPeople->skillCooldown[1] / 1000));
	}
	else {
		listWidget[2]->show();
		listLabel[9]->unshow();
	}
	


}

void cGame::pizzaDraw(long long &startTime) {
	for (int i = 0; i < liveObstacles.size(); i++)
	{
		if (!hasSuddenStop)
			liveObstacles[i]->isStop = suddenStop;
		else if (suddenStop) 			
			liveObstacles[i]->isStop = true;
		liveObstacles[i]->move();
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
		if (handlingSkillExec(livePeople[i], startTime) == 1)
			continue;
		livePeople[i]->moveHitBox();

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

			Sleep(10);
		}
	}
}

void cGame::drawThread()
{
	long long startTime = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	while (!isExit)
	{
		if (!isLose && !isPause)
		{
			cGameEngine::swapHandle();
			cGameEngine::refreshBackGround(false);
			pizzaDraw(startTime);

			gameMap::mapChangeTick();
			cGameEngine::fillScreen();
			Sleep(25);
		}
		//time = current;
	}
}



bool cGame::InitGame()
{
	window.IsVisible = true;
	window.topleft = { My_Windows.Left, My_Windows.Top };
	window.botright = { My_Windows.Right, My_Windows.Bottom };
	window.parentWindow = nullptr;
	window.WidgetFace = cAsset::assetLoader(UIPrefix + "mainWD");

	mainMenu.IsVisible = true;
		
	mainMenu.topleft = { My_Windows.Left, My_Windows.Top };
	mainMenu.botright = { My_Windows.Right, My_Windows.Bottom };
	mainMenu.parentWindow = &window;
	mainMenu.WidgetFace = cAsset::assetLoader(UIPrefix + "menuBg");
	mainMenu.show();
	return true;
}

void cGame::onGameReady()
{
	mainMenu.show();
	cDWindow panel(&mainMenu, { 479, 71 }, "panelmainmenu", true);

	cButton panelButton[4] = {
		cButton(&panel, { 0, 0 }, "buttonplay", 1),
		cButton(&panel, { 0, 22 }, "buttonscoreboard", 1),
		cButton(&panel, { 0, 44 }, "buttonsettingsm", 1),
		cButton(&panel, { 0, 66 }, "buttonexitm", 1)
	};

	function<void()> panelFunction[4]{
		[&]() {game.GamePlayPanel(); },
		[&]() {game.ScoreBoard(); },
		[&]() {game.GameSettingsPanel(); },
		[&]() {game.GameQuitPanel(true); }
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
			Sound::playSoundEffect(SoundEffect::menuMove);
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
		hasSuddenStop = false;

	}
	else if (currentTheme == 1)
	{
		hasSuddenStop = false;
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
	string mapSaved[3] = { "emptymapload", "emptymapload" , "emptymapload" };
	string mapIconSaved[3] = { "iconemptyload", "iconemptyload", "iconemptyload" };
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
				mapSaved[i] = "junglemapload";
				mapIconSaved[i] = "iconmapjungle";
			}
			else if (j == 1) {
				mapSaved[i] = "beachmapload";
				mapIconSaved[i] = "iconmapbeach";
			}
			else if (j == 2) {
				mapSaved[i] = "citymapload";
				mapIconSaved[i] = "iconmapcity";
			}
			ifs.close();
		}
	}
	std::function<void()> panelFunct[1] = {
		[&]() {
			game.GameNewGamePanel();
		},

	};

	tomainMenu = false;
	cDWindow panel(&mainMenu, { 30, 6 }, "panelplay", true);
	cDWindow panelBackground(&panel, { 0, 0 }, "panelbackground", false);

	cDWindow panelButton[4]{
		cDWindow(&panel, { 2, 22 }, "buttonnewgame", true),
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
			Sound::playSoundEffect(SoundEffect::menuMove);
			if (current == 0) {
				GameNewGamePanel();
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

	cDWindow panel(&mainMenu, { 30, 6 }, "panelnewgame", true);
	cButton panelButton[3] = {
		cButton(&panel, { 20, 33 }, "iconmapjungle", 1, true),
		cButton(&panel, { 20, 65 }, "iconmapbeach", 1, true),
		cButton(&panel, { 20, 97 }, "iconmapcity", 1, true)
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
			Sound::playSoundEffect(SoundEffect::menuMove);
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
	timePauseStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	isPause = true;
	cDWindow panel(&window, { 122, 11 }, "panelpause", true);
	cButton panelButton[6]{
		cButton(&panel, { 42, 21 }, "buttonresume", 1),
		cButton(&panel, { 42, 39 }, "buttonsettingsp", 1),
		cButton(&panel, { 42, 57 }, "buttonsave", 1),
		cButton(&panel, { 42, 75 }, "buttonload", 1),
		cButton(&panel, { 42, 93 }, "buttonexitdesktop", 1),
		cButton(&panel, { 42, 111 }, "buttonexitmain", 1)
	};

	std::function<void()> panelFunct[6] = {
		[&]() {
			cGameEngine::fillScreenWithLastFrame(true);
			game.resumeFunction();
			game.isPause = false;
			game.timePauseEnd = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
			game.timePause += (game.timePauseEnd - game.timePauseStart) / 1000  ;
		},
		[&]() {game.GameSettingsPanel(); },
		[&]() {game.GameSavePanel(); },
		[&]() {game.GameLoadPanel(); },
		[&]() {game.GameQuitPanel(true); },
		[&]() {game.GameQuitPanel();	 }
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
			Sound::playSoundEffect(SoundEffect::menuMove);
			//panel.unshow();
			//panelButton[current].unshow();
			panelFunct[current]();
			panel.show();
			panelButton[current].show();
			isPause = false;
		}
		Sleep(50);
	}
}

void cGame::GameSettingsPanel()
{
	cDWindow panel(&window, { 122, 11 }, "panelsettings", true);
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
			cButton(&panel, { 20, 50 }, "rabbitchoose1", 1, true),
			cButton(&panel, { 20, 50 }, "rabbitchoose2", 1, false)
		},
		{
			cButton(&panel, { 140, 50 }, "cubechoose1", 1, true),
			cButton(&panel, { 140, 50 }, "cubechoose2", 1, false) 
		}	
	};

	cDWindow selectarrow(&panel, { 210, 30 }, "arrowL", true);
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
			 else if (currentarrowpos == 1 && !isStart)
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
				Sound::playSoundEffect(SoundEffect::menuMove);
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
				Sound::playSoundEffect(SoundEffect::menuMove);
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
			Sound::playSoundEffect(SoundEffect::menuMove);
			if (currentarrowpos >= 2) {
				bool change = (currentarrowpos == 3) ? false : true;
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
	string mapIconSaved[3] = { "iconemptyload", "iconemptyload" , "iconemptyload" };
	string mapSaved[3] = { "emptymapload", "emptymapload", "emptymapload" };
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
				mapIconSaved[i] = "iconmapjungle";
				mapSaved[i] = "junglemapload";
			}
			else if (j == 1) {
				mapIconSaved[i] = "iconmapbeach";
				mapSaved[i] = "beachmapload";
			}
			else if (j == 2) {
				mapIconSaved[i] = "iconmapcity";
				mapSaved[i] = "citymapload";
			}
			ifs.close();
		}
	}

	cDWindow panel(&window, { 122, 11 }, "panelsave", true);
	
	cDWindow panelBackground(&panel, { 0, 0 }, "panelbackground", false);

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
			Sound::playSoundEffect(SoundEffect::menuMove);
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
	string mapIconSaved[3] = { "iconemptyload", "iconemptyload" , "iconemptyload" };
	string mapSaved[3] = { "emptymapload", "emptymapload", "emptymapload" };
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
				mapIconSaved[i] = "iconmapjungle";
				mapSaved[i] = "junglemapload";
			}
			else if (j == 1) {
				mapIconSaved[i] = "iconmapbeach";
				mapSaved[i] = "beachmapload";
			}
			else if (j == 2) {
				mapIconSaved[i] = "iconmapcity";
				mapSaved[i] = "citymapload";
			}
			ifs.close();
		}
	}

	cDWindow panel(&window, { 122, 11 }, "panelload2", true);

	cDWindow panelBackground(&panel, { 0, 0 }, "panelbackground", false);

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
			Sound::playSoundEffect(SoundEffect::menuMove);
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
	cDWindow confirm(&window, { 177, 30 }, "panelconfirmexit", true);
	cDWindow selectarrow(&confirm, { 96, 37 }, "arrowenter", true);

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
			Sound::playSoundEffect(SoundEffect::menuMove);
			if (currentarrowpos == 0)
			{
				tomainMenu = true;
				isPause = false;
				isExit = true;
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
						timePauseStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
						livePeople[u]->mState = true;
						isCook = false;
					}
					if (isCook)
					{
						nemesis = environmentObject[j];
						victim = livePeople[u];
						break;
					}
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
	cDWindow panel(&window, { 133, 11 }, "paneldie", true);
	cButton panelButton[3]{
		cButton(&panel, { 3, 28 }, "buttondieretry", 1),
		cButton(&panel, { 3, 59 }, "buttondieload", 1),
		cButton(&panel, { 3, 90 }, "buttondieback", 1)
	};

	std::function<void()> panelFunct[3] = {
	[&]() {
		game.isPause = false;
		game.isLose = false;
		game.isExit = false;
		for (int i = 0; i < game.livePeople.size(); i++)
		{
			game.livePeople[i]->setPos({ short(234 + 40 * i), 145 });
			game.livePeople[i]->setState(true);
			game.livePeople[i]->resetCooldown();

		};
		game.nemesis = nullptr;
		game.victim = nullptr;
		game.clearObjects();
		game.currentPhase = 0;
		game.spawnObstacle(CreatedLevel[currentTheme][currentPhase]);

		Sound::resumeCurrentTrack();
		game.timePauseEnd = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
		game.timePause += (game.timePauseEnd - game.timePauseStart) / 1000;
	},
	[&]() {
		game.GameLoadPanel();
	},
	[&]() {
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
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelFunct[current]();
			if (current < 2)
				break;
			panel.show();
			panelButton[current].show();
		}
	}
}

cGame::cGame()
{
	gameOrder = 1;
	gameLevel = 1;
	isPause = false;
	isExit = false;
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

void cGame::prepareUI()
{
	cDWindow* rr = new cDWindow(&window, { 504, 0 }, "panelinfo", true);
	//cDWindow howtoplay(&rr, { 0,110 }, "howtoplay", true);
	cLabel* t11 = new cLabel(rr, { 10, 5 }, "LEVEL: " + to_string(gameLevel), 1, Color::red, true);
	cLabel* t1 = new cLabel(rr, { 10, 15 }, "SCORES:", 1, Color::red, true);
	string point = to_string(totalPoint);
	cLabel* t2 = new cLabel(rr, { 20, 25 }, point, 2, Color::red, true);
	cLabel* t3 = new cLabel(rr, { 10, 35 }, "TIME:", 1, Color::red, true);
	time = int(calculateTime());
	cLabel* t4 = new cLabel(rr, { 60, 35 }, to_string(time), 2, Color::red, true);

	cLabel* t6 = new cLabel(rr, { 10, 45 }, "COINS:", 1, Color::red, true);
	cLabel* t7 = new cLabel(rr, { 60, 45 }, "30 x 0", 2, Color::red, true);
	cLabel* t8 = new cLabel(rr, { 10, 55 }, "SKILLS", 1, Color::red, true);


	cLabel* t5 = new cLabel(rr, { 10, 150 }, "ESC: PAUSE", 1, Color::red, true);


	cButton* skill1R = new cButton(rr, { 10, 80 }, "iconflashR", 1, true);
	cButton* skill1U = new cButton(rr, { 10, 80 }, "iconflashU", 1);
	cButton* skill2R = new cButton(rr, { 60, 80 }, "iconfreezeR", 1, true);
	cButton* skill2U = new cButton(rr, { 60, 80 }, "iconfreezeU", 1);
	cLabel* t9 = new cLabel(rr, { 10, 100 }, to_string(mainPeople->skillCooldown[0]), 1, Color::red);
	cLabel* t10 = new cLabel(rr, { 60, 100 }, to_string(mainPeople->skillCooldown[1]), 1, Color::red);

	cLabel* t12 = new cLabel(rr, { 10, 120 }, "HELP: TAB", 1, Color::red, true);

	listWidget.push_back(skill1R);
	listWidget.push_back(skill1U);
	listWidget.push_back(skill2R);
	listWidget.push_back(skill2U);
	listWidget.push_back(rr);

	listLabel.push_back(t1);
	listLabel.push_back(t2);
	listLabel.push_back(t3);
	listLabel.push_back(t4);
	listLabel.push_back(t5);
	listLabel.push_back(t6);
	listLabel.push_back(t7);
	listLabel.push_back(t8);
	listLabel.push_back(t9);
	listLabel.push_back(t10);
	listLabel.push_back(t11);
	listLabel.push_back(t12);
}

void cGame::handlingSkillFx()
{
	updateSkillState();
	if (mainPeople->used[0])
	{
		listWidget[1]->show();
		Sound::playSoundEffect(SoundEffect::flashFx);
		mainPeople->used[0] = false;
	}
	if (mainPeople->used[1])
	{
		listWidget[3]->show();
		Sound::playSoundEffect(SoundEffect::freezeFx);
		mainPeople->used[1] = false;
	}
}

void cGame::GameWinPanel()
{
	int bonus[6] = { 120, 70, 35, 15, 5, 0 };
	int count = min(int(calculateTime() / 5), 5);
	int roundScore = bonus[count] + coinBonus + 100;
	listLabel[1]->updateText(to_string(totalPoint) + " + " + to_string(roundScore));
	listLabel[2]->updateText("TIME BONUS");
	listLabel[3]->updateText(to_string(bonus[count]));
	totalPoint+= roundScore;

	int n[3] = { 0, 0, 0 };
	int k = 0;
	int temp = 0;
	ifstream ifs("Save//leaderboard");
	if (ifs.is_open()) {
		while (ifs >> temp) {
			if (ifs.eof())
				break;
			n[k] = temp;
			k++;
		}
	}
	ifs.close();

	for (int ind = 0; ind < 3; ind++) {
		if (totalPoint > n[ind]) {
			n[ind] = totalPoint;
			break;
		}
	}
	ofstream ofs("Save//leaderboard");
	for (int id = 0; id < 3; id++) {
		ofs << n[id] << endl;
	}
	ofs.close();

	isPause = true;
	mainPeople->passLevel = false;
	Sound::pauseCurrentTrack();
	string list[3] = { "jungle1", "beach1", "city1" };
	cDWindow theme(&window, { 0,0 }, list[currentTheme]);
	cDWindow firework[5]{
		cDWindow(&theme, { 0, 0 }, "firework1"),
		cDWindow(&theme, { 0, 0 }, "firework2"),
		cDWindow(&theme, { 0, 0 }, "firework3"),
		cDWindow(&theme, { 0, 0 }, "firework4"),
		cDWindow(&theme, { 0, 0 }, "firework5")
	};

	cDWindow statue(&theme, { 0, 0 }, "statue");
	cLabel prompt(&theme, { 150, 150 }, "Press Enter To Continue", 1, Color::black);

	cDWindow panel(&theme, { 107, 50 }, "panelwinoption");
	cButton panelButton[2] = {
		cButton(&panel, {15, 16}, "buttonplayagain", 1),
		cButton(&panel, {171, 16}, "buttontomainmenu", 1)
	};

	theme.show();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++) {
			firework[j].show();
			Sleep(200);
		}
	}
	theme.show();

	Sleep(1000);
	statue.show();
	prompt.show();

	while (true)
	{
		if (GetKeyState(0x0D) & 0x8000)
			break;
		Sleep(50);
	}
	Sleep(500);
	theme.show();
	panel.show();
	int current = 0;
	panelButton[current].show();
	while (true) {

		if ((GetKeyState(VK_LEFT) & 0x8000) && current > 0)
		{
			panelButton[current].unshow();
			current--;
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].show();
		}
		if ((GetKeyState(VK_RIGHT) & 0x8000) && current < 1)
		{
			panelButton[current].unshow();
			current++;
			Sound::playSoundEffect(SoundEffect::menuMove);
			panelButton[current].show();
		}

		if (GetKeyState(0x0D) & 0x8000)
		{
			if (current == 0)
			{
				currentPhase = 0;
				resetTime();
				clearObjects(true, true);
				spawnObstacle(CreatedLevel[currentTheme][currentPhase]);
				spawnEnvironment();
				spawnCoin();
				spawnPeople();
				Sound::resumeCurrentTrack();
				isPause = false;
			}
			else {
				tomainMenu = true;
				isExit = true;
			}
			break;
		}
		Sleep(50);
	}
}

void cGame::processLose()
{
	int n[3] = { 0, 0, 0 };
	int k = 0;
	int temp = 0;
	ifstream ifs("Save//leaderboard");
	if (ifs.is_open()) {
		while (ifs >> temp) {
			if (ifs.eof())
				break;
			n[k] = temp;
			k++;
		}
	}
	ifs.close();

	for (int ind = 0; ind < 3; ind++) {
		if (totalPoint > n[ind]) {
			n[ind] = totalPoint;
			break;
		}
	}
	ofstream ofs("Save//leaderboard");
	for (int id = 0; id < 3; id++) {
		ofs << n[id] << endl;
	}
	ofs.close();

	timePauseStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();

	Sound::pauseCurrentTrack();
	if (nemesis && victim)
	{
		nemesis->hitSound();
		nemesis->hitEffect(victim);
		nemesis->hitSound();
		coinBonus = 0;
	}

	Sleep(1000);
	cGameEngine::fillScreenWithLastFrame(true);
	cDWindow dieeffect[5]{
		cDWindow(&window, { 133, 11 }, "rip1", false),
		cDWindow(&window, { 133, 11 }, "rip2", false),
		cDWindow(&window, { 133, 11 }, "rip3", false),
		cDWindow(&window, {133, 11 }, "rip4", false),
		cDWindow(&window, {133, 11 }, "rip5", false)
	};
	for (int i = 0; i < 5; i++)
	{
		dieeffect[i].show();
		Sleep(300);
	}
	Sleep(2000);
}

void cGame::GameHelpPanel()
{

}

void cGame::MainGame() {
	isStart = true;
	isLose = false;
	isPause = false;
	isExit = false;
	
	timeStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	prepareUI();

	if (cGameEngine::startDrawThread) {
		drawThreadHandle = thread(&cGame::drawThread, this);
		collisionThreadHandle = thread(&cGame::collisionThread, this);
		if (hasSuddenStop)
		{
			randomStopThreadHandle = thread(&cGame::randomStopThread, this);
		}
		cGameEngine::startDrawThread = false;
	}
	
	Sound::playTrack(SoundTrack::background, true);
	
	while (!isExit) {
		handlingSkillFx();
		updateInfo();

		if ((GetKeyState(VK_ESCAPE) & 0x8000) && !isLose)
		{
			GamePausePanel();
		}
	
		if ((GetKeyState(VK_TAB) & 0x8000) && !isLose)
		{
			GameHelpPanel();
		}

		if (!livePeople.empty() && mainPeople->passLevel) {
			if (isComplete())
			{
				GameWinPanel();
			}
			else {
				nextLevel();
			}
		}
		if (isLose)
		{
			processLose();
			GameDiePanel();
		}
		Sleep(10);
	}
	Sound::pauseCurrentTrack();

	if (drawThreadHandle.joinable())
		drawThreadHandle.join();
	if (collisionThreadHandle.joinable())
		collisionThreadHandle.join();
	cGameEngine::startDrawThread = true;
	if (randomStopThreadHandle.joinable()) {
		randomStopThreadHandle.join();
	}

	clearObjects(true, true);
	clearUI();
	isStart = false;
}

void cGame::clearUI()
{
	for (int i = 0; i < listWidget.size(); i++)
	{
		delete listWidget[i];
	}
	listWidget.clear();
	for (int i = 0; i < listLabel.size(); i++)
	{
		delete listLabel[i];
	}
	listLabel.clear();
}

bool cGame::isComplete()
{
	if (currentPhase + 1 == CreatedLevel[currentTheme].size())
	{
		return true;
	}
	return false;
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
					isPause = true;
					isLose = true;
					nemesis = obstacle;
					victim = livePeople[i];
					return true;
				}
			}
    }
	return false;
    //return livePeople.empty();
}

void cGame::updateInfo()
{
	if (calculateTime() - time >= 1 || calculateTime() < time) {
		time = int(calculateTime());
		listLabel[3]->updateText(to_string(time));
	}
	if (coinBonus != coinNow) {
		listLabel[6]->updateText("30 x " + to_string(coinBonus / 30));
		Sound::playSoundEffect(SoundEffect::coinEarn);
		coinNow = coinBonus;
	}
}

void cGame::randomStopThread()
{
	long long now = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	int lane = obstacleLanes.size();
	vector<long long> stopDuration;
	vector<short> laneStopped;
	vector<cTrafficLight*> traffic;
	for (int i = 0; i < lane; i++) {
		int x = rand() % 1000 + 500;
		stopDuration.push_back(-x);
		laneStopped.push_back(obstacleLanes[i].Y);
	}
	for (int i = 0; i < environmentObject.size(); i++) {
		if (environmentObject[i]->getType() == 'f') {
			traffic.push_back(static_cast<cTrafficLight*>(environmentObject[i]));
		}
	}
	while (hasSuddenStop && !isExit) {
		long long currentTime = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
		long long timePassed = currentTime - now;
		if (timePassed <= 0)
			continue;
		for (int i = 0; i < lane; i++) {
			
			stopDuration[i] -= timePassed;
			if (stopDuration[i] <= 0) {
				long long timeRandom = (rand() % 5000 + 5000) * (-1); // control from > 0 -> stop , < 0  &  > timeRandom -> resume
				if (stopDuration[i] < timeRandom) {
					traffic[i]->changeLight(false);
					stopDuration[i] = rand() % 5000 + 2500;
				}
				else {
					traffic[i]->changeLight(true);
				}
				for (cObstacle* ele : liveObstacles) {
					if (ele->getPos().Y == laneStopped[i]) {
						ele->resume();
					}
				}				
			}
			else {
				
				for (cObstacle* ele : liveObstacles) {
					if (ele->getPos().Y == laneStopped[i]) {
						ele->stop();
					}
				}
			}

		}
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
		now = currentTime;
	}

	
}

void cGame::resumeFunction()
{	
	cDWindow panel(&window, { 204, 50 }, "panelcountdown", true);
	cDWindow countdown[3] = {
		cDWindow(&panel, {28, 6}, "Count3", false),
		cDWindow(&panel, {28, 6}, "Count2", false),
		cDWindow(&panel, {20, 6}, "Count1", false),
	};
	for (int i = 0; i < 3; i++)
	{
		countdown[i].show();
		Sleep(750);
		countdown[i].unshow();
	}
}

void cGame::save(string fileName) {
	ofstream ofs(fileName);
	if (!ofs.is_open())
		return;

	Time time;
	time.getTime();
	ofs << time << endl;

	ofs << gameOrder << " " << gameLevel << " " << currentTheme << " " << currentPhase << " " << totalTime << " " << timePause << endl;
	// people and their position
	ofs << livePeople.size() << endl;
	for (cPeople* element : livePeople)
	{
		ofs << element->getPos().X << " " << element->getPos().Y << " " << totalPoint << " " << coinBonus << endl;
	}

	// obstacles and their position
	int obstacleCount = (int)liveObstacles.size();

	ofs << obstacleCount << endl;

	for (int i = 0; i < obstacleCount; i++)
	{
		ofs << liveObstacles[i]->getType() << " " << liveObstacles[i]->getPos().X << " " << liveObstacles[i]->getPos().Y << " " << liveObstacles[i]->getSpeed() << " " << liveObstacles[i]->getDirection() << endl;
	}

	for (int i = 0; i < environmentObject.size(); i++) {
		if (environmentObject[i]->getType() == '1') {
			ofs << environmentObject [i]->getType() << " " << environmentObject[i]->getPos().X << " " << environmentObject[i]->getPos().Y << endl;
		}
	}

	ofs.close();
	
}

void cGame::spawnPeople() {
	for (int i = 0; i < gameOrder; i++) {
		livePeople.push_back(new cPeople());
	}
	mainPeople = livePeople[0];
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

double cGame::calculateTime() {
	if (!isLose && !isPause)
	{
		timeEnd = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
		double time = (timeEnd - timeStart) / 1000 - timePause;
		return time;
	}

	return 0;
}

void cGame::resetTime() {
	this->timeStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	this->timeEnd = timeStart;
	this->timePauseStart = 0;
	this->timePauseEnd = 0;
	timePause = 0;
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
	int bonus[6] = { 120, 70, 35, 15, 5, 0 };
	int count = min(int(calculateTime() / 5), 5);
	int roundScore = bonus[count] + coinBonus + 100;
	listLabel[1]->updateText(to_string(totalPoint) + " + " + to_string(roundScore));
	listLabel[2]->updateText("TIME BONUS");
	listLabel[3]->updateText(to_string(bonus[count]));

	this->gameLevel++;
	//gameMap::nextMap();
	calculatePoint();
	if (currentPhase == 4) currentPhase--;
	clearObjects();
	spawnObstacle(CreatedLevel[currentTheme][(++currentPhase) % CreatedLevel[currentTheme].size()]);
	spawnCoin();
	coinBonus = 0;
	timePause = 0;
	timeStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	timeEnd = timeStart;
	timePauseStart = 0;
	timePauseEnd = 0;
	isPause = true;
	mainPeople->setForceStop();
	suddenStop = true;
	string src[3] = { "jungle1", "beach1", "city1" };
	string themeString = src[currentTheme];
	cDWindow theme(&window, { 0,0 }, themeString);
	cDWindow levelUp(&theme, { 0, 0 }, "levelUp", 1);
	levelUp.show();
	Sound::playSoundEffect(SoundEffect::levelup);
	Sleep(2000);
	suddenStop = false;
	mainPeople->setForceStop();
	isPause = false;

	listLabel[2]->updateText("TIME");
	listLabel[1]->updateText(to_string(totalPoint));
	mainPeople->passLevel = false;
	time = 0;
	coinNow = 0;
	listLabel[6]->updateText("30 x " + to_string(coinBonus / 30));
	listLabel[3]->updateText(to_string(time));
	listLabel[10]->updateText("LEVEL: " + to_string(gameLevel));
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
	//		src += map[rand_map] + "//";
	//		spawnObstacle();
	//	}
	//	Sleep(10);
	//}
	//drawingThread.join();

}

void cGame::load(string fileName)
{
	resetTime();
	if (hasSuddenStop)
	{
		hasSuddenStop = false;
		randomStopThreadHandle.join();
	}
	clearObjects(true, true);

	ifstream ifs(fileName);
	if (!ifs.is_open())
		return;
	Time time;
	ifs >> time;

	ifs >> gameOrder >> gameLevel >> currentTheme >> currentPhase >> totalTime >> timePause;

	livePeople.resize(gameOrder);
	int dump;
	ifs >> dump;
	for (int i = 0; i < gameOrder; i++)
	{
		short x, y;
		ifs >> x >> y;
		livePeople[i] = new cPeople({ x, y });
		ifs >> totalPoint >> coinBonus;
	}
	mainPeople = livePeople[0];
	int obstacleCount;
	ifs >> obstacleCount;

	liveObstacles.resize(obstacleCount);
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
			liveObstacles[i] = new cLion(pos, speed, direction);
			break;
		case 'r':
			liveObstacles[i] = new cRhino(pos, speed, direction);
			break;
		case 'c':
			liveObstacles[i] = new cCrocodile(pos, speed, direction);
			break;

		case 's':
			liveObstacles[i] = new cShark(pos, speed, direction);
			break;
		case 'S':
			liveObstacles[i] = new cSurfer(pos, speed, direction);
			break;

		case 'T': 
			liveObstacles[i] = new cTruck(pos, speed, direction);
			break;
		case 'M': 
			liveObstacles[i] = new cMotorbike(pos, speed, direction);
			break;
		case 'C': 
			liveObstacles[i] = new cCar(pos, speed, direction);
			break;
		default:
			break;
		}
	}
	
	while (!ifs.eof()) {
		char type;
		short x, y;
		ifs >> type >> x >> y;
		if (ifs.eof())
			break;
		COORD pos = { x, y };
		switch (type)
		{
		case '1':
			environmentObject.push_back(new cCoin(pos));
			break;
		default:
			break;
		}
	}

	ifs.close();
	timePauseStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	timePauseEnd = timePauseStart;
	timeStart -= totalTime * 1000;

	gameMap::changeMapTheme(game.currentTheme);
	gameMap::currentMap = &gameMap::listMap[game.currentTheme][game.currentPhase];
	game.spawnEnvironment();	
	mainPeople = game.livePeople[0];
	nemesis = nullptr;
	victim = nullptr;
	if (isStart)
	{
		
		isPause = false;
	}
	else {
		MainGame();

	}
	
}

void cGame::ScoreBoard() {
	cDWindow screen(&window, { 0, 0 }, "leaderboard", true);
	screen.show();

	ifstream ifs("Save//leaderboard");
	if (!ifs.is_open())
		return;
	int i = 0;
	short x[3] = { 295, 187, 405};
	short y[3] = { 131, 142, 142 };
	int score;
	string scoreString[3] = { "", "", "" };
	while (ifs >> score) {
		
		
		scoreString[i] = to_string(score);
		int n = scoreString[i].length();
		x[i] -= n * 5;
		i++;
	}
	
	ifs.close();

	cLabel p[3]{
		cLabel(&screen, { x[0], y[0] }, scoreString[0], 2, Color::yellow, true),
		cLabel(&screen, { x[1], y[1] }, scoreString[1], 2, Color::green, true),
		cLabel(&screen, { x[2], y[2] }, scoreString[2], 2, Color::blue, true)
	};

	while (true) {
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}
	}

	ifs.close();
}
