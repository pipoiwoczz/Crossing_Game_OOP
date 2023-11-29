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


void cleanGame()
{
	cGameEngine::cleanEngine();
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
	//drawBackGround();
	spawnPeople();
	spawnObstacle();
	cObstacle* lily = new cLilyleaf({ 0, 73 });
	environmentObject.push_back(lily);
	environmentObject.push_back(new cRiver(73, lily));
	lily = new cLilyleaf({ 30, 55 });
	environmentObject.push_back(lily);
	environmentObject.push_back(new cRiver(55, lily));
	lily = nullptr;

	//resetTime();
	for (int i = 0; i < livePeople.size(); i++)
	{
		cGameEngine::renderPeople(livePeople[i]);
	}
	gameMap::changeMap(BGIndex::Jungle);
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
	while (true) {
		//if (GetAsyncKeyState(0x50) < 0) {d
		//	pauseGame();
		//	break;
		//}


		if (GetAsyncKeyState(0x51) < 0) {
			isExit = true;
			break;
		}
		if (GetAsyncKeyState(0x10) < 0) {
			t2.updateText(to_string(i++));
		}
		if (GetAsyncKeyState(0x11) < 0) {
		}
		for (int j = 0; j < environmentObject.size(); j++)
		{
			if (environmentObject[j]->getType() == 'R')
			{
				for (int k = 0; k < environmentObject[j]->boxes.size(); k++)
				{
					for (int u = 0; u < livePeople.size(); u++)
					{
						if (environmentObject[j]->boxes[k].isOverlap(livePeople[u]->mBox))
						{
							isLose = true;
							for (int s = 0; s < environmentObject[j]->pSafe->boxes.size(); s++)
							{
								if (environmentObject[j]->pSafe->boxes[s].isOverlap(livePeople[u]->mBox))
								{
									isLose = false;
									break;
								}
							}
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



bool cGame::isImpact()
{
    for (int i = 0; i < livePeople.size(); i++)
    {
		int cnt = -1;
        if (livePeople[i] -> getState())
			for (cObstacle* obstacle : liveObstacles)
			{
				cnt++;
				for (int k = 0; k < obstacle->boxes.size(); k++)
				{
					if (obstacle->boxes[k].isOverlap(livePeople[i]->mBox))
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

void cGame::pauseGame() {
	// draw pause game box
	timePauseStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	isPause = true;
	//stopDrawAnimal();
}

void cGame::resumeGame() {
	// draw a box to count down 3 sec 
	// then continue game
	timePauseEnd = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	timePause += (timePauseEnd - timePauseStart) / 1000;
	isPause = false;
	//continueDrawAnimal();
}

void cGame::save(void) {
	string filename = "test.bin"; // placeholder filename

	ofstream ofs;
	ofs.open(filename, ios::binary);

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
	for (int count = 0; count < obstacleCount; count++)
	{
		obstacleType[count] = liveObstacles[count]->getType();
		obstacleInfo[3 * count] = liveObstacles[count]->getPos().X;
		obstacleInfo[3 * count + 1] = liveObstacles[count]->getPos().Y;
		obstacleInfo[3 * count + 2] = liveObstacles[count]->getSpeed();
	}

	ofs.write(obstacleType, obstacleCount);
	ofs.write((char*)obstacleInfo, sizeof(short) * obstacleCount * 3);

	delete[] obstacleType;
	obstacleType = nullptr;
	delete[] obstacleInfo;
	obstacleInfo = nullptr;

	ofs.close();
	resumeGame();
}

void saveTest() {
	return;
}

void cGame::saveGame() {
    pauseGame();
    
    
    cDWindow saveWindow(&cWidget::window, { 0, 0 }, "saveWindow", "saveWindow.txt");
	saveWindow.show();
	cLabel saveLabel(&saveWindow, { 10, 5 }, "saveLabel", "SAVE GAME", 1, Color::red);
	saveLabel.show();
	void *saveTestPtr = saveTest;
	cButton button1(&saveWindow, { 10, 10 }, "button1", "saveButton.txt", 3, saveTest);
	cButton button2(&saveWindow, { 10, 15 }, "button2", "saveButton.txt", 3, saveTest);
	cButton button3(&saveWindow, { 10, 15 }, "button2", "saveButton.txt", 3, saveTest);

    
    // draw a mini box in center as an input field
    // user input save name <= 20 characters
    // check this save name exist before or not
    // => enter save name again or save successfully
    // press ESC to exit save menu
    
    // suggestion: have limited save slots with their own pre-designated save files. no name-checking needed, easier to manage.
    
    // testing simple version of save file
    // file format (binary)
    // [gameOrder] [gameLevel] [map] [score] [time]
    // [player 1 coord X] [player 1 coord Y] ...
    // [number of obstacles]
    // [obstacle 1 type] [obstacle 2 type] ...
    // [obstacle 1 coord X] [obstacle 1 coord Y] [obstacle 1 speed] ...
    
    // note: stop status not recorded yet
    
	
}

void cGame::LoadGame() {
	// draw load game menu // has a box to show list of save game
	// has choices: choose save game and load, back to previous menu
	// if user choose choose save game and load => load game to play
	// if user choose back to previous menu => back to previous menu

	// show files saved before
	ifstream ifs("saved.txt");
	string line;
	while (getline(ifs, line)) {
		cout << line << endl;
	}
	ifs.close();

	// choose file to load 
	string filename;
	// draw a box for user to choose file to load
	// if name is not exist => ask user to enter again
	// if name is exist => load game

	ifs.open(filename);
	if (ifs.is_open()) {
		// load game and start game
	}
	else {
		// ask user to enter again
	}
	ifs.close();

}

cGame::cGame (string saveFile) // load game (create cGame object) from save file
{
    ifstream ifs;
    ifs.open(saveFile, ios::binary);
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
				cX += pObj->pTexture->width + offsetF + offsetB;;
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
	double time = timeEnd - timeStart - timePauseStart - timePauseEnd;
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
	gameMap::nextMap();
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
			resumeGame();
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
			gameMap::changeMap(BGIndex(random));
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
