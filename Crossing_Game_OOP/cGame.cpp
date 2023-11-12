#include "cGame.h"

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
	drawGameTitle();
	if (!isPause);
		//lion->move();
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
	drawMap();
	
	//getPeople();
	//getLion();
	
	gameThread();
	
}

void cGame::gameThread() {
	/*thread t1(&cGame::threadFunction1, this);
	thread t2(&cGame::threadFunction2, this);*/
	auto future1 = async(launch::async, &cGame::checkImpactThread, this);
	auto future2 = async(launch::async, &cGame::drawThread, this);
	auto future3 = async(launch::async, &cGame::movingThread, this);
	movingThread();
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

void cGame::pauseGame() {
	// draw pause game box
	isPause = true;
	stopDrawAnimal();
}

void cGame::resumeGame() {
	// draw a box to count down 3 sec 
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
    // [obstacle 1 type] [obstacle 1 coord X] [obstacle 1 coord Y] [obstacle 1 speed] ...
    
    ofs.write((char *) &gameOrder, sizeof(short));
    ofs.write((char *) &gameLevel, sizeof(short));
    ofs.write((char *) &map, sizeof(int));
    
    short * peoplePosition = new short [gameOrder * 2];
    int count = 0;
    for (cPeople element : livePeople)
    {
        peoplePosition[count] = element.getPos().X;
        count++;
        peoplePosition[count] = element.getPos().Y;
        count++;
    }
    ofs.write((char *) peoplePosition, sizeof(short) * gameOrder * 2);
    delete [] peoplePosition;
    peoplePosition = nullptr;
    
    int obstacleCount = (int) liveObstacles.size();
    ofs.write((char *) &obstacleCount, sizeof(int));
    short * obstacleList = new short [obstacleCount * 4];
    count = 0;
    for (cObstacle element : liveObstacles)
    {
        obstacleList[count] = 0; // placeholder for obstacle type (rhino/truck/...)
        count++;
        obstacleList[count] = element.getPos().X;
        count++;
        obstacleList[count] = element.getPos().Y;
        count++;
        obstacleList[count] = element.getSpeed();
    }
    ofs.write((char *) obstacleList, sizeof(short) * obstacleCount * 4);
    delete [] obstacleList;
    obstacleList = nullptr;

	ofs.close();

	resumeGame();
}

cGame::cGame (string saveFile) // load game (create cgame object) from save file
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
    short * obstacleList = new short [obstacleCount * 4];
    ifs.read((char *) obstacleList, sizeof(short) * obstacleCount * 4);
    ifs.close();
    liveObstacles.resize(obstacleCount);
    for (int i = 0; i < obstacleCount; i++)
    {
        // create object from type at obstaclePosition[4 * i],
            // set pos to {obstaclePosition[4 * i + 1], obstaclePosition[4 * i + 2]}
            // set speed to obstaclePosition[4 * i + 3]
        liveObstacles[i] = createObject(obstacleList[4 * i], {obstacleList[4 * i + 1], obstacleList[4 * i + 2]}, obstacleList[4 * i + 3]);
    }
    delete [] obstacleList;
    obstacleList = nullptr;
}

// object from type - prototype
cObstacle * createObject (short type, COORD position, int speed)
{
    switch (type)
    {
        case 0: //placeholder
            return dynamic_cast<cObstacle *>(new cRhino(position, speed));
            
        default:
            return dynamic_cast<cObstacle *>(new cRhino());
    }
}
