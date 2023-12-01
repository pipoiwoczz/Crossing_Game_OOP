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
	map = 1;
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
	if (!isLoad)
	{
		spawnPeople();
		spawnObstacle();
	}
	isLoad = false;
	cObstacle* lily = new cLilyleaf({ 0, 73 });
	environmentObject.push_back(lily);
	environmentObject.push_back(new cRiver(73, lily));
	lily = new cLilyleaf({ 30, 55 });
	environmentObject.push_back(lily);
	environmentObject.push_back(new cRiver(55, lily));
	lily = nullptr;

	//resetTime();
	gameMap::changeMapTheme(MapTheme::Jungle);

	Sound::playSoundList();
	Sound::playBackGroundSound();
	//Sound::musicThread();	

	cDWindow rr(&cWidget::window, { 504, 0 }, "te", "info.txt");
	cLabel t1(&rr, { 10, 5 }, "t1", "SCORES", 1, Color::red);
	string point = to_string(totalPoint);
	cLabel t2(&rr, { 10, 15 }, "t2", point, 2, Color::red);

	listWidget.push_back(&rr);
	rr.show();
	listLabel.push_back(&t1);
	t1.show();
	listLabel.push_back(&t2);
	t2.unshow();
	int i = 0;
	thread drawingThread(&cGameEngine::maindraw, this);


	while (!isExit) {
		//if (GetAsyncKeyState(0x50) < 0) {d
		//	pauseGame();
		//	break;
		//}
		if (GetAsyncKeyState(0x0D) < 0)
		{
			pauseGame();
		}

		if (GetAsyncKeyState(0x51) < 0) {
			isExit = true;
			break;
		}
		/*if (GetSpecificKeyPress(13)) {
			isPause = true;
			cDWindow pausePanel(&cWidget::window, { 121, 30 }, "pausemenu", "pausemenu.txt");

			pausePanel.show();
			
			cButton menuchoice[4]{
					cButton(&pausePanel, { 42, 25 }, "resumebutton", "resume.txt", 1,doNothing),
					cButton(&pausePanel, { 42, 43 }, "saveload", "saveload.txt", 1, doNothing),
					cButton(&pausePanel, { 42, 61 }, "exitdesktop", "exitdesktop.txt", 1, doNothing),
					cButton(&pausePanel, { 42, 79 }, "exitmain", "exitmain.txt", 1, doNothing)
			};

			pPausePanel = &pausePanel;
			std::function<void()> menufunct[4];
			menufunct[0] = [this] {this->isPause = false; };
			menufunct[1] = [this] {  };
			menufunct[3] = [this] {this->isPause = false; this->isExit = true; };
			menufunct[2] = [this] {
				
				cDWindow confirm(this->pPausePanel, { 55, 30 }, "confirm", "exitpanel.txt", true);
				cDWindow selectarrow(&confirm, { 96, 37 }, "selectarrow", "enterarrow.txt", true);

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
					Sleep(75);
					if (GetSpecificKeyPress(13))
					{
						if (currentarrowpos == 0)
						{
							this->isPause = false;
							this->isExit = true;
							cGame::mainloop = false;
						}
						pPausePanel->show();
						break;
					}
					Sleep(75);
				}
				};
				
			int choice = 0;
			menuchoice[choice].show();
			while (isPause)
			{
				if (GetAsyncKeyState(0x51))
					break;
				if (GetAsyncKeyState(VK_DOWN) < 0 && choice < 3)
				{
					menuchoice[choice].unshow();
					choice++;
					menuchoice[choice].show();
				}
				if (GetAsyncKeyState(VK_UP) < 0 && choice > 0)
				{
					menuchoice[choice].unshow();
					choice--;
					menuchoice[choice].show();
				}
				if (GetSpecificKeyPress(13))
				{
					menufunct[choice]();
					if (choice == 0)
						break;
					menuchoice[choice].show();
				}
				Sleep(150);
			}


		}*/

		for (int j = 0; j < environmentObject.size(); j++)
		{
			if (environmentObject[j]->getType() == 'R')
			{
				
					for (int u = 0; u < livePeople.size(); u++)
				{
					if (environmentObject[j]->Box.isOverlap(livePeople[u]->mBox))
					{
						isLose = true;
						if (environmentObject[j]->pSafe->Box.isOverlap(livePeople[u]->mBox))
						{
							isLose = false;
						}
					}
				}
			}
		}
		if (!isLose)
			isImpact();
		if (isLose)
		{
			Sleep(2000);
			cGameEngine::refreshBackGround(true);
			cDWindow a(&cWidget::window, { 0,0 }, "tr", "map_forest.txt");
			cDWindow pa(&a, { 101, 31 }, "ttq", "failedbox.txt");
			pa.show();
			while (true)
			{
				if (GetAsyncKeyState(0x51) < 0)
				{
					break;
				}

				if (GetAsyncKeyState(0x11) < 0)
				{
					for (int i = 0; i < liveObstacles.size(); i++)
					{
						delete liveObstacles[i];
					}
					for (int i = 0; i < livePeople.size(); i++)
					{
						delete livePeople[i];
					}
					liveObstacles.resize(0);
					livePeople.resize(0);
					spawnObstacle();
					spawnPeople();
					totalPoint = 0;
					resetTime();
					t2.updateText(to_string(totalPoint));
					isLose = false;
					isPause = false;
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

	for (int i = 0; i < listLabel.size(); i++)
	{
		listLabel[i]->unshow();
	}
	for (int i = 0; i < listWidget.size(); i++)
	{
		listWidget[i]->unshow();
	}
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

	string mapSaved[3] = { "emptyLoadIcon.txt", "emptyLoadIcon.txt" , "emptyLoadIcon.txt" };
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
			if (GetAsyncKeyState(0x51) < 0)
				break;
			if (GetAsyncKeyState(0x0D) < 0)
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
			if (GetAsyncKeyState(VK_LEFT) && x > 0)
			{
				buttonList[x].onDeSelect();
				x--;
				buttonList[x].onSelect();

			}
			if (GetAsyncKeyState(VK_RIGHT) && x < 2)
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
		cGameEngine::pGame.MainGame();
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
					isPause = true;
					isLose = true;
					livePeople[i]->isDead();
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



void cGame::despawnThread()
{
    while (!isLose && !isExit)
    {
        if (isPause)
            continue;
        for (int i = 0; i < liveObstacles.size(); i++)
        {
            COORD coord = liveObstacles[i] -> getPos();
            if (coord.X > My_Windows.Right)
            {
                liveObstacles[i] -> setPos({ 0, coord.Y });
            }
            else if (coord.X < 0)
            {
                liveObstacles[i] -> setPos({ My_Windows.Right, coord.Y });
            }
        }
    }
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




void cGame::pauseGame() {
	timePauseStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	isPause = true;

	cDWindow pauseWindow(&cGameEngine::pWindow, { 100, 30 }, "pauseWindow", "mapPanel.txt");
	pauseWindow.show();
	cLabel pauseLabel(&pauseWindow, { 50, 10 }, "pauseLabel", "PAUSE", 1, Color::red);
	pauseLabel.show();
	// change playNButton with correct one
	cButton resumeButton(&pauseWindow, { 78, 15  }, "resumeButton", "continueButton.txt", 3, doNothing);
	cButton saveButton(&pauseWindow, { 60, 40 }, "saveButton", "saveButton.txt", 3, saveGame);
	cButton exitButton(&pauseWindow, { 147, 40 }, "exitButton", "backButton.txt", 3, exit);
	resumeButton.show();
	saveButton.show();
	exitButton.show();
	cButton buttonList[] = { resumeButton, saveButton, exitButton };
	int x = 0;
	buttonList[0].onSelect();
	while (true) {
		if (GetAsyncKeyState(0x51) < 0)
			break;
		if (GetAsyncKeyState(0x0D) < 0)
		{
			buttonList[x].onDeSelect();
			for (int i = 0; i < 3; i++)
			{
				buttonList[i].unshow();
			}
			pauseLabel.unshow();
			pauseWindow.unshow();
			buttonList[x].onEnter();
			break;
		}
		if (GetAsyncKeyState(VK_LEFT) && x > 0)
		{
			buttonList[x].onDeSelect();
			x--;
			buttonList[x].onSelect();
		}
		if (GetAsyncKeyState(VK_RIGHT) && x < 2)
		{
			buttonList[x].onDeSelect();
			x++;
			buttonList[x].onSelect();
		}
		Sleep(100);
	}

	for (int i = 0; i < 3; i++)
	{
		buttonList[i].unshow();
	}
	pauseLabel.unshow();
	pauseWindow.unshow();
	resumeFunction();
}


void cGame::resumeFunction()
{
	cDWindow continueBox(&cGameEngine::pWindow, { 100, 30 }, "continueBox", "mapPanel.txt");
	continueBox.show();
	string countDown[4] = { "Count3.txt", "Count2.txt", "Count1.txt", "GO.txt" };
	for (int i = 0; i < 4; i++) {
		cButton temp(&continueBox, { 110, 15 }, "temp", countDown[i], 0, doNothing);
		temp.show();
		Sleep(1000);
		temp.unshow();
	}
	continueBox.unshow();

	timePauseEnd = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	timePause += (timePauseEnd - timePauseStart) / 1000;
	isPause = false;
	
}

void cGame::resumeGame(cGame *pGame) {
	// draw a box to count down 3 sec 
	// then continue game
	pGame->resumeFunction();
	//continueDrawAnimal();
}


void cGame::save(string fileName) {
	ofstream ofs("Save//" + fileName);
	if (!ofs.is_open())
		return;

	Time time;
	time.getTime();
	ofs << time << endl;

	ofs << gameOrder << " " << gameLevel << " " << map << " " << totalPoint << " " << totalTime << " " << timePause << endl;
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

	/*int environmentCount = (int)environmentObject.size();
	ofs << environmentCount << endl;
	for (int i = 0; i < environmentCount; i++)
	{
		ofs << environmentObject[i]->getType() << " " << environmentObject[i]->getPos().X << " " << environmentObject[i]->getPos().Y << " " << environmentObject[i]->getSpeed() << endl;
	}*/

	ofs.close();


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

void cGame::saveGame(cGame *pGame) {
	Time time[3];
	string savedFile[3] = { "save1.txt", "save2.txt", "save3.txt" };
	for (int i = 0; i < 3; i++) {
		ifstream in("Save//" + savedFile[i], ios::binary);
		if (!in.is_open()) {
			time[i];
			continue;
		}
		Time t;
		in >> t;
		time[i] = t;
		in.close();
	}
	string timeString[3];
	for (int i = 0; i < 3; i++) {
		timeString[i] = time[i].timeString();
	}

	
	// check file is save or not
	// if not icon = empty map
	// if yes icon = map saved

	/*string mapSaved[4] = { "emptyIcon.txt", "emptyIcon.txt" , "emptyIcon.txt" , "emptyIcon.txt" };
	string saved[3] = { "save2.bin" ,"save2.bin" , "save2.bin" };
	ifstream ifs;
	for (int i = 0; i < 3; i++) {
		ifs.open(saved[i]);
		if (ifs.is_open()) {
			mapSaved[i] = "jungleIcon.txt";
		}
		ifs.close();
	}*/

	cDWindow saveWindow(&cGameEngine::pWindow, { 100, 30 }, "saveWindow", "mapPanel.txt");
	saveWindow.show();
	cLabel saveLabel(&saveWindow, { 78, -3 }, "saveLabel", "SAVE GAME", 1, Color::red);
	saveLabel.show();

	cButton button1(&saveWindow, { 90, 10 }, "button1", "jungleIcon.txt", 3, onSave1);
	cButton button2(&saveWindow, { 40, 40 }, "button2", "jungleIcon.txt", 3, onSave2);
	cButton button3(&saveWindow, { 147, 40 }, "button2", "jungleIcon.txt", 3, onSave3);
	string label[3] = { "save1", "save2", "save3" };
	cLabel Label1(&button1, { 0, 1 }, label[0], timeString[0], 1, Color::bright_white);
	cLabel Label2(&button2, { 0, 1 }, label[1], timeString[1], 1, Color::bright_white);
	cLabel Label3(&button3, { 0, 1 }, label[2], timeString[2], 1, Color::bright_white);
	cButton buttonList[] = { button1, button2, button3 };
	cLabel labelList[] = { Label1, Label2, Label3 };
	int x = 0;
	for (int i = 0; i < 3; i++) {
		buttonList[i].show();
		labelList[i].show();
	}

	buttonList[0].onSelect();
	while (true) {
		if (GetAsyncKeyState(0x51) < 0)
			break;
		if (GetAsyncKeyState(0x0D) < 0)
		{
			buttonList[x].onDeSelect();
			for (int i = 0; i < 3; i++)
			{
				buttonList[i].unshow();
				labelList[i].unshow();
			}
			saveLabel.unshow();
			saveWindow.unshow();
			buttonList[x].onEnter();
			break;
		}
		if (GetAsyncKeyState(VK_LEFT) && x > 0)
		{
			buttonList[x].onDeSelect();
			x--;
			buttonList[x].onSelect();
			
		}
		if (GetAsyncKeyState(VK_RIGHT) && x < 2)
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
	resumeGame(&cGameEngine::pGame);
    
	
}



cGame::cGame (string saveFile) // load game (create cGame object) from save file
{
    ifstream ifs;
    ifs.open(saveFile, ios::binary);
	Time t;
	ifs >> t;
    ifs.read((char *) &gameOrder, sizeof(short));
    ifs.read((char *) &gameLevel, sizeof(short));
    ifs.read((char *) &map, sizeof(int));
    ifs.read((char *) &totalPoint, sizeof(long));
    ifs.read((char *) &totalTime, sizeof(double));
    
    short * peoplePosition = new short [gameOrder * 2];
    ifs.read((char *) peoplePosition, sizeof(short) * gameOrder * 2);
    livePeople.resize(gameOrder);
    for (short i = 0; i < gameOrder; i++)
    {
        livePeople[i] = new cPeople({peoplePosition[2 * i], peoplePosition[2 * i + 1]});
    }
    delete [] peoplePosition;
    peoplePosition = nullptr;
    
    int obstacleCount;
    ifs.read((char *) &obstacleCount, sizeof(int));
    
    char * obstacleType = new char [obstacleCount];
    short * obstacleInfo = new short [obstacleCount * 3];
    ifs.read(obstacleType, obstacleCount);
    ifs.read((char *) obstacleInfo, obstacleCount * 3);
    ifs.close();
    
    liveObstacles.resize(obstacleCount);
    for (int i = 0; i < obstacleCount; i++)
    {
        COORD pos = {obstacleInfo[3 * i], obstacleInfo[3 * i + 1]};
       // liveObstacles[i] = cObstacle::constructObject(obstacleType[i], pos, obstacleInfo[3 * i + 2]);
    }
    
    delete [] obstacleType;
    obstacleType = nullptr;
    delete [] obstacleInfo;
    obstacleInfo = nullptr;
}


void cGame::drawBackGround()
{
	gameMap* pMap = gameMap::getCurrentMap();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT reg = { 0,0, My_Windows.Right - 1, My_Windows.Bottom - 1 };
	WriteConsoleOutput(h, pMap->mapArray, { My_Windows.Right, My_Windows.Bottom }, { 0,0 }, &reg);
}

vector<cPeople*> cGame::getPeople() {
	return livePeople;
}

vector<cObstacle*> cGame::getObstacles() {
	return liveObstacles;
}

void cGame::spawnPeople() {
	for (int i = 0; i < gameOrder; i++) {
		livePeople.push_back(new cPeople());
	}
}

void cGame::impactEffect(cObstacle* obsta) {

	

}

void cGame::spawnObstacle() {
	ifstream levelIn;
	levelIn.open("Level//jungle1.txt");
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
	//for (int i = 0; i < 1; i++) {
	//	liveObstacles.push_back(new cLion({short(0 + 100*i), 50}, 3));
	//}
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
	for (int i = 0; i < liveObstacles.size(); i++) {
		delete liveObstacles[i];
	};
	
	liveObstacles.clear();
	spawnObstacle();
	
}

void cGame::endlessMode() {
	spawnPeople();
	spawnObstacle();
	//resetTime();
	thread drawingThread(&cGameEngine::pizzaDraw, this);
	Sound::playSoundList();
	Sound::playIntroSound();
	//Sound::musicThread();
	while (true) {
		if (GetAsyncKeyState(0x50) < 0) {
			pauseGame();
		}
		if (GetAsyncKeyState(0x53) < 0) {
			resumeGame(&cGameEngine::pGame);
		}
		if (GetAsyncKeyState(0x51) < 0) {
			// isExit = true;
			// save game Menu here
			// draw save game menu
			// can save or not 
			// if can save => save game
			// if not => continue game
		}
		if (GetAsyncKeyState(0x1B) < 0) {
			isExit = true;
			// save game Menu here
			// draw save game menu
			// can save or not 
			// if can save => save game => exit game
			// if not => exit game
			break;
		}
		if (isImpact())
		{
			isLose = true;
			break;
		}
		for (int i = 0; i < gameOrder; i++) {
			livePeople[i]->move();
		}
		if (isFinishLevel()) {
			this->gameLevel++;
			calculatePoint();
			resetTime();
			srand(NULL);
			int random = rand() % 7 + 1;
			//gameMap::changeMap(BGIndex(random));
			for (int i = 0; i < livePeople.size(); i++) {
				livePeople[i]->setPos({ short(200 - 100 * i), 100 });
			}
			for (int i = 0; i < liveObstacles.size(); i++) {
				delete liveObstacles[i];
			}
			liveObstacles.clear();
			string src = "//Level//map_";
			string map[3] = { "jungle", "beach", "city" };
			srand(NULL);
			int rand_map = rand() % 3;
			src += map[rand_map] + "//.txt";
			spawnObstacle();
		}
		Sleep(10);
	}
	drawingThread.join();

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
	
	ifstream ifs("Save//" + fileName);
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

	ifs.close();
}
void cGame::Setting() {
	// draw setting menu	// has a tutorial box to know how to play game
	// has choices: change game sound, back to previous menu
	// change gmae sound: on/off or reduce and increase sound 
	// sound: background music, sound effect
}
void cGame::ScoreBoard() {
	// draw score board menu // has a box to show score and time of game
	// has choices: back to previous menu
}
void cGame::exitGame(HANDLE t) {
	// draw exit game menu // has a box to ask user want to save game or not
	// has choices: save game and exit, exit without save game, back to previous menu
	// if user choose save game and exit => save game and exit
	// if user choose exit without save game => exit game
	// if user choose back to previous menu => back to previous menu
}
void cGame::resetGame() {
	resetTime();
	totalPoint = 0;
	totalTime = 0;
	gameLevel = 1;
	gameOrder = 1;
	for (int i = 0; i < livePeople.size(); i++) {
		delete livePeople[i];
	}
	for (int i = 0; i < liveObstacles.size(); i++) {
		delete liveObstacles[i];
	}
	livePeople.clear();
	liveObstacles.clear();
	// game type ?
	/*if (gameType == 0) {
		MainGame();
	}
	else {
		endlessMode();
	}*/
	MainGame();
}
