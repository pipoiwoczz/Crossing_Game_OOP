#include "cGame.h"
#include "cObstacle.h"
#include "cPeople.h"
#include "Sound.h"
#include "Map.h"
#include "hitbox.h"
#include "cAnimal.h"
#include "cVehicle.h"
#include "cAsset.h"
#include "gameEngine.h"


void cleanGame()
{
	cGameEngine::cleanEngine();
	cObstacle::cleanBootstrap();
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
	liveObstacles.clear();
	livePeople.clear();
	//cleanGame();
}
short cGame::getGameOrder()
{
	return gameOrder;
}

//int cGame::getMenuChoice() {
//	unsigned char MOVING;
//	int choice = 0;
//	while (true) {
//		cout << choice << endl;
//		drawMainMenu(choice);
//		MOVING = _getch();
//		if (MOVING == 224) {
//			MOVING = _getch();
//			if (MOVING == 'P')
//			{
//				choice = (++choice) % 3;
//			}
//			else if (MOVING == 'H') {
//				choice = (--choice + 3) % 3;
//			}
//		}
//		else if (toupper(MOVING) == 'W') {
//			choice = (--choice + 3) % 3;
//		}
//		else if (toupper(MOVING) == 'S') {
//			choice = (++choice) % 3;
//		}
//		
//		if (MOVING == 13) {
//			return choice;
//		}
//		//if (toupper(MOVING) == 'S' || MOVING == 40) {
//		//	if (choice == 5) {
//		//		choice = 1;
//		//	}
//		//	else {
//		//		choice++;
//		//	}
//		//}
//		//else if (toupper(MOVING) || MOVING == 38) {
//		//	if (choice == 1) {
//		//		choice = 5;
//		//	}
//		//	else {
//		//		choice--;
//		//	}
//		//}
//	}
//}

void cGame::drawMap() {
	switch (gameLevel) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		break;
	}
}

void cGame::startGame() {
	// create mainmenu with option
	system("cls");
	//int choice = getMenuChoice();
	//clearConsole();
	//switch (choice) {
	//case 0: 
	//	// Start new game
	//	MainGame();
	//	break;
	//case 1:
	//	// Load game
	//	//LoadGame();
	//	break;
	//case 2:
	//	// Setting
	//	//Setting();
	//	break;
	//case 3:
	//	// Scoreboard
	//	//ScoreBoard();
	//	break;
	//case 4:
	//	/*HANDLE t = GetStdHandle(STD_OUTPUT_HANDLE);
	//	exitGame(t);*/
	//	break;
	//default:
	//	break;
	//}
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
	//resetTime();
	for (int i = 0; i < livePeople.size(); i++)
	{
		cGameEngine::renderPeople(livePeople[i]);
		}
	gameMap::changeMap(BGIndex::Jungle);
	Sound::playSoundList();
	Sound::playBackGroundSound();
	//Sound::musicThread();
	DWORD his;
	cDWindow rr(&cWidget::window, { 504, 0 }, "te", "Sprites//info.txt");
	cLabel t1(&rr, { 10, 5 }, "t1", "SCORES", 1, Color::red);
	
	cLabel t2(&rr, { 10, 15 }, "t2", "999999999", 2, Color::red);

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
		if (isImpact())
		{
			isLose = true;
			Sleep(2000);
			cGameEngine::refreshBackGround(true);
			cDWindow a(&cWidget::window, { 0,0 }, "tr", "Sprites//map_forest.txt");
			cDWindow pa(&a, { 101, 31 }, "ttq", "Sprites//failedbox.txt");
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
					isLose = false;
					isPause = false;
					break;
				}
			}
			pa.unshow();
		}
		
		for (int i = 0; i < gameOrder; i++) {
			livePeople[i]->move();
		}

		if (isFinishLevel()) {
			this->gameLevel++;
			gameMap::nextMap();
			calculatePoint();
			cout << "Total point: " << totalPoint << endl;
			cout << "Total time: " << totalTime << endl;
			isPause = true;
			std::system("pause");
			break;
		}
		Sleep(10);
	}
	drawingThread.join();
	for (int i = 0; i < listWidget.size(); i++)
	{
		listWidget[i]->unshow();
	}
	for (int i = 0; i < listLabel.size(); i++)
	{
		listLabel[i]->unshow();
	}
}

void cGame::gameThread() {
	/*thread t1(&cGame::threadFunction1, this);
	thread t2(&cGame::threadFunction2, this);*/
	//auto future1 = async(launch::async, &cGame::checkImpactThread, this);
	//auto future2 = async(launch::async, &cGame::drawThread, this);
	//auto future3 = async(launch::async, &cGame::movingThread, this);
	//movingThread();
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
				for (int j = 0; j < (livePeople[i])->mBoxes.size(); j++)
				{
					for (int k = 0; k < obstacle->boxes.size(); k++)
					{
						if (obstacle->boxes[k].isOverlap(livePeople[i]->mBoxes[j]))
						{
							isPause = true;
							livePeople[i]->isDead();
							Sound::playHitSound();
							impactEffect(cnt);
							return true;
						}
					}
				}
			}
    }
	return false;
    //return livePeople.empty();
}
//
//void cGame::checkImpactThread() {
//	while (true) {
//		if (isImpact()) {
//			break;
//		}
//	}
//	//stopDrawAnimal();
//	drawLosingTitle();
//}

void cGame::drawThread() {

}

void cGame::movingThread() {
	char MOVING;
	while (true) {
		MOVING = toupper(_getch());
		if (MOVING == 'P') {
			pauseGame();
		}
		else if (MOVING == 'R') {
			resumeGame();
		}
		else if (MOVING == 'L') {
			//loadGame();
		}
		else if (MOVING == 'O') {
			//saveGame();
		}
		else if (MOVING == 27) {
			//exitGame(t);
		}
		else {
			//updatePosPeople(MOVING);
		}
	}
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



void cGame::saveGame() {
    pauseGame();
    
    string filename = "test.bin"; // placeholder filename
    
    ofstream ofs;
    ofs.open(filename, ios::binary);
    
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
    
    ofs.write((char *) &gameOrder, sizeof(short));
    ofs.write((char *) &gameLevel, sizeof(short));
    ofs.write((char *) &map, sizeof(int));
    ofs.write((char *) &totalPoint, sizeof(long));
    ofs.write((char *) &totalTime, sizeof(double));
    
    short * peoplePosition = new short [gameOrder * 2];
    int count = 0;
    for (cPeople* element : livePeople)
    {
        peoplePosition[count] = element->getPos().X;
        count++;
        peoplePosition[count] = element->getPos().Y;
        count++;
    }
    ofs.write((char *) peoplePosition, sizeof(short) * gameOrder * 2);
    delete [] peoplePosition;
    peoplePosition = nullptr;
    
    int obstacleCount = (int) liveObstacles.size();
    ofs.write((char *) &obstacleCount, sizeof(int));
    
    char * obstacleType = new char [obstacleCount];
    
    short * obstacleInfo = new short [obstacleCount * 3];
    for (int count = 0; count < obstacleCount; count++)
    {
        obstacleType[count] = liveObstacles[count] -> getType();
        obstacleInfo[3 * count] = liveObstacles[count] -> getPos().X;
        obstacleInfo[3 * count + 1] = liveObstacles[count] -> getPos().Y;
        obstacleInfo[3 * count + 2] = liveObstacles[count] -> getSpeed();
    }
    
    ofs.write(obstacleType, obstacleCount);
    ofs.write((char *) obstacleInfo, sizeof(short) * obstacleCount * 3);
    
    delete [] obstacleType;
    obstacleType = nullptr;
    delete [] obstacleInfo;
    obstacleInfo = nullptr;

	ofs.close();
	resumeGame();
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
        liveObstacles[i] = cObstacle::constructObject(obstacleType[i], pos, obstacleInfo[3 * i + 2]);
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

void cGame::impactEffect(int i) {
	string effectList[]{ "fxframe.txt", "base.txt", "purple.txt", "blast.txt", "explosion1.txt","explosion2.txt", "explosion3.txt","fade1.txt", "fade2.txt", "fade3.txt", "dissappear.txt" };
	vector<Texture> f;
	ifstream test;
	for (auto name : effectList)
	{
		test.open(name);
		if (test.is_open())
		{
			Texture a;
			test >> a.height >> a.width;
			a.textureArray = new CHAR_INFO[a.height * a.width];

			for (int i = 0; i < a.height; i++)
			{
				//  BlankSegment bla;
				//  bool encounter = false;

				for (int j = 0; j < a.width; j++)
				{
					int x;
					test >> x;
					if (x != 16 && x != 17)
					{
						/*   if (encounter) {
							   encounter = false;
							   loaded.blankTexture[i].push_back(bla);
						   }*/
						CHAR_INFO t = { L'█', WORD( x * 16 + x)};
						a.textureArray[i * a.width + j] = t;

					}
					else {
						/* if (!encounter) {
							 encounter = true;
							 bla.start = j;
							 bla.end = bla.start - 1;
						 }
						 bla.end++;*/
						CHAR_INFO t = { L' ', WORD(0)};
						a.textureArray[i * a.width + j] = t;
					}
				}
			}
			f.push_back(a);
		}
		test.close();
	}
	short w = f[0].width;
	short h = f[0].height;
	COORD writepos = { 100, 31 };
	CHAR_INFO* fxBG = new CHAR_INFO[w*h];
	memcpy(fxBG, f[0].textureArray, w * h * sizeof(CHAR_INFO));
	for (int i = 0; i < w * h; i++)
	{
		if (fxBG[i].Char.UnicodeChar == L' ')
		{
			fxBG[i].Attributes = cGameEngine::mainBuffer[(writepos.Y + i / w) * gameMap::getCurrentMap()->width + writepos.X + (i % w)].Attributes;
		}
	}
	SMALL_RECT fxframe = { writepos.X, writepos.Y, writepos.X + w - 1, writepos.Y + h - 1 };
	WriteConsoleOutput(cGameEngine::curHandle, fxBG, { w, h }, { 0,0 }, &fxframe);

	COORD p{ writepos.X + 120, writepos.Y + 40 };
	for (int i = 0; i < livePeople.size(); i++)
	{
		short pw = livePeople[i]->pTexture->width;
		short ph = livePeople[i]->pTexture->height;

		CHAR_INFO* framePlayer = new CHAR_INFO[pw * ph];
		memcpy(framePlayer, livePeople[i]->pTexture->textureArray, pw * ph * sizeof(CHAR_INFO));
		for (int j = 0; j < pw * ph; j++)
		{
			if (framePlayer[j].Char.UnicodeChar == L' ')
			{
				framePlayer[i].Attributes = fxBG[(p.Y - writepos.Y + j / pw) * w + p.X - writepos.X + (j % pw)].Attributes;
			}
		}
		SMALL_RECT playerRect = { p.X, p.Y, p.X + pw - 1, p.Y + ph - 1 };
		WriteConsoleOutput(cGameEngine::curHandle, framePlayer, { pw, ph }, { 0, 0 }, &playerRect);
		delete[]framePlayer;
	}
	Sleep(200);
	for (int j = 1; j < f.size(); j++)
	{
		COORD topleft = {writepos.X + 50, writepos.Y + 25};
		CHAR_INFO* readyBuffer = new CHAR_INFO[f[j].width * f[j].height];
		memcpy(readyBuffer, f[j].textureArray, f[j].width * f[j].height * sizeof(CHAR_INFO));

		for (int i = 0; i < f[j].width * f[j].height; i++)
		{
			if (readyBuffer[i].Char.UnicodeChar == L' ') {
				readyBuffer[i].Attributes = fxBG[((topleft.Y - writepos.Y) + i / f[j].width) * w + topleft.X - writepos.X + (i % f[j].width)].Attributes;
			}
		}

		SMALL_RECT reg = { topleft.X , topleft.Y,  topleft.X + f[j].width - 1, topleft.Y + f[j].height - 1 };
		WriteConsoleOutput(cGameEngine::curHandle, fxBG, { w, h }, { 0,0 }, &fxframe);
		WriteConsoleOutput(cGameEngine::curHandle, readyBuffer, { f[j].width , f[j].height }, { 0,0 }, &reg);
		delete[]readyBuffer;
		//system("pause");
		Sleep(100);
	}
	delete[]fxBG;

}

void cGame::spawnObstacle() {
	ifstream levelIn;
	levelIn.open("Level//jungle1.txt");
	int linecount = 0;
	short lineoffset[] = { 0, 50 };
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

			short offsetY;
			levelIn >> offsetY;
			cObstacle* pObj = cObstacle::constructObject(objname, { cX, lineoffset[linecount]}, spd);
			/*switch (objname)
			{
			case 'l': pObj = new cLion({ cX, lineoffset[linecount] }, spd); break;
			case 'r': pObj = new cRhino({ cX, lineoffset[linecount] }, spd); break;
			case 'c': pObj = new cCrocodile({ cX, lineoffset[linecount] }, spd); break;
			
			default:
				break;
			}*/

			if (pObj)
			{
				liveObstacles.push_back(pObj);
				cX += pObj->pTexture->width + offsetY;
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
	return (livePeople[0]->getPos().Y == 0);
	
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
	for (int i = 0; i < livePeople.size(); i++) {
		livePeople[i]->setPos({ 200, 100 });
	};
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
void cGame::LoadGame() {
	// draw load game menu // has a box to show list of save game
	// has choices: choose save game and load, back to previous menu
	// if user choose choose save game and load => load game to play
	// if user choose back to previous menu => back to previous menu
}