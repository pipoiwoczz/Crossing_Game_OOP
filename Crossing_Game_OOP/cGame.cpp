#include "cGame.h"
#include "Map.h"
#include "Sound.h"

//void cGame::getPeople() {
//	short numOfPlayer = getGameOrder();
//	if (numOfPlayer == 1) {
//		people = new cPeople;
//	} else {
//		people = new cPeople[2];
//		people[2].setPos({ 70, 50 });
//	}
//}
//
//void cGame::getLion() {
//	lion = new cLion[7];
//	for (int i = 0; i < 7; i++) {
//		lion[i].setPos({ short(-20 - i * 40), 40 });
//	}
//}
//
void cGame::drawGame() {
	//drawGameTitle();
	//if (!isPause);
	//	//lion->move();
}


int cGame::getMenuChoice() {
	unsigned char MOVING;
	int choice = 0;
	while (true) {
		cout << choice << endl;
		drawMainMenu(choice);
		MOVING = _getch();
		if (MOVING == 224) {
			MOVING = _getch();
			if (MOVING == 'P')
			{
				choice = (++choice) % 3;
			}
			else if (MOVING == 'H') {
				choice = (--choice + 3) % 3;
			}
		}
		else if (toupper(MOVING) == 'W') {
			choice = (--choice + 3) % 3;
		}
		else if (toupper(MOVING) == 'S') {
			choice = (++choice) % 3;
		}
		
		if (MOVING == 13) {
			return choice;
		}
		//if (toupper(MOVING) == 'S' || MOVING == 40) {
		//	if (choice == 5) {
		//		choice = 1;
		//	}
		//	else {
		//		choice++;
		//	}
		//}
		//else if (toupper(MOVING) || MOVING == 38) {
		//	if (choice == 1) {
		//		choice = 5;
		//	}
		//	else {
		//		choice--;
		//	}
		//}
	}
}

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
	int choice = getMenuChoice();
	clearConsole();
	switch (choice) {
	case 0: 
		// Start new game
		MainGame();
		break;
	case 1:
		// Load game
		//LoadGame();
		break;
	case 2:
		// Setting
		//Setting();
		break;
	case 3:
		// Scoreboard
		//ScoreBoard();
		break;
	case 4:
		/*HANDLE t = GetStdHandle(STD_OUTPUT_HANDLE);
		exitGame(t);*/
		break;
	default:
		break;
	}
}

void cGame::MainGame() {
	drawBackGround();
	spawnPeople();
	spawnObstacle();
	resetTime();
	for (int i = 0; i < gameOrder; i++) {
		livePeople[i]->draw();
	}
	
	Sound::playSoundList();
	Sound::playIntroSound();
	//Sound::musicThread();
	while (!isPause) {
		
		
			

		if (GetAsyncKeyState(0x50) < 0) {
			pauseGame();
			break;
		}
		if (GetAsyncKeyState(0x51) < 0)
			break;
		
		for (int i = 0; i < gameOrder; i++) {
			livePeople[i] -> move();
		}
		
		for (int i = 0; i < liveObstacles.size(); i++) {
			liveObstacles[i]->move();
		}

		if (isFinishLevel()) {
			this->gameLevel++;
			cAsset::nextMap();
			calculatePoint();
			cout << "Total point: " << totalPoint << endl;
			cout << "Total time: " << totalTime << endl;
			isPause = true;
			std::system("pause");
			break;
		}

		if (isImpact()) {
			

			break;
		}
		

		Sleep(30);
		//drawBackGround();
		for (int i = 0; i < gameOrder; i++) {
			livePeople[i]->draw();
		}
		for (int i = 0; i < liveObstacles.size(); i++) {
			liveObstacles[i]->draw();
		}

	}
	
}

void cGame::gameThread() {
	/*thread t1(&cGame::threadFunction1, this);
	thread t2(&cGame::threadFunction2, this);*/
	auto future1 = async(launch::async, &cGame::checkImpactThread, this);
	auto future2 = async(launch::async, &cGame::drawThread, this);
	auto future3 = async(launch::async, &cGame::movingThread, this);
	movingThread();
}

bool cGame::isImpact()
{
    for (int i = 0; i < livePeople.size(); i++)
    {
		int cnt = -1;
        if (livePeople[i] -> getState())
			for (cObstacle * obstacle : liveObstacles)
			{
				cnt++;
				if (livePeople[i] -> isImpact(*obstacle))
				{
					livePeople[i] -> isDead();
					impactEffect(cnt);
					return true;
					//delete livePeople[i];
					//livePeople.erase(livePeople.begin() + i);
				}
			}
    }
	return false;
    //return livePeople.empty();
}

void cGame::checkImpactThread() {
	while (true) {
		if (isImpact()) {
			break;
		}
	}
	stopDrawAnimal();
	drawLosingTitle();
}

void cGame::drawThread() {
	while (!isLose) {
		drawGame();
	}
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
			updatePosPeople(MOVING);
		}
	}
}

void cGame::despawnThread()
{
    for (int i = 0; i < liveObstacles.size(); i++)
    {
        COORD coord = liveObstacles[i] -> getPos();
        if (coord.X > My_Windows.Right) 
        {
			liveObstacles[i]->setPos({ 0, coord.Y });
        }
    }
}

void cGame::pauseGame() {
	// draw pause game box
	timePauseStart = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	isPause = true;
	stopDrawAnimal();
}

void cGame::resumeGame() {
	// draw a box to count down 3 sec 
	// then continue game
	timePauseEnd = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	timePause += (timePauseEnd - timePauseStart) / 1000;
	isPause = false;
	continueDrawAnimal();
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
    // [gameOrder] [gameLevel] [map]
    // [player 1 coord X] [player 1 coord Y] ...
    // [number of obstacles]
    // [obstacle 1 type] [obstacle 2 type] ...
    // [obstacle 1 coord X] [obstacle 1 coord Y] [obstacle 1 speed] ...
    
    // note: stop status not recorded yet
    
    ofs.write((char *) &gameOrder, sizeof(short));
    ofs.write((char *) &gameLevel, sizeof(short));
    ofs.write((char *) &map, sizeof(int));
    
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
	gameMap* pMap = cAsset::getCurrentMap();
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
	string effectList[]{ "base.txt", "purple.txt", "blast.txt", "explosion1.txt","explosion2.txt", "explosion3.txt","fade1.txt", "fade2.txt", "fade3.txt", "dissappear.txt" };
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
						CHAR_INFO t = { L'█', x * 16 + x };
						a.textureArray[i * a.width + j] = t;

					}
					else {
						/* if (!encounter) {
							 encounter = true;
							 bla.start = j;
							 bla.end = bla.start - 1;
						 }
						 bla.end++;*/
						CHAR_INFO t = { L' ', 11 * 16 + 11 };
						a.textureArray[i * a.width + j] = t;
					}
				}
			}
			f.push_back(a);
		}
		test.close();
	}


	for (auto e : f)
	{
		COORD topleft = this->liveObstacles[i]->getPos();
		topleft = {short(max(topleft.X, 0)), short(max(topleft.Y, 0))};
		CHAR_INFO* readyBuffer = new CHAR_INFO[e.width * e.height];
		memcpy(readyBuffer, e.textureArray, e.width * e.height * sizeof(CHAR_INFO));

		for (int i = 0; i < e.width * e.height; i++)
		{
			if (readyBuffer[i].Char.UnicodeChar == L' ') {
				readyBuffer[i].Attributes = cAsset::getCurrentMap()->mapArray[(topleft.Y + i / e.width) * cAsset::getCurrentMap()->width + topleft.X + (i % e.width)].Attributes;
			}
		}

		SMALL_RECT reg = { topleft.X , topleft.Y,  topleft.X + e.width - 1, topleft.Y + e.height - 1 };

		WriteConsoleOutput(mainHandle, readyBuffer, { e.width , e.height }, { 0,0 }, &reg);
		delete[]readyBuffer;
		//system("pause");
		Sleep(120);
	}

}

void cGame::spawnObstacle() {
	for (int i = 0; i < 4; i++) {
		liveObstacles.push_back(new cLion({short(-300 +100*i), 50}, 3));
	}
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
