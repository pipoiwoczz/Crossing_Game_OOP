//#include "cAnimal.h"
//#include "cVehicle.h"
//#include "cPeople.h"
//#include "cGame.h"
//#include "Graphics.h"
//
//char MOVING;
//cGame cg = cGame();
//bool isRunningDrawGame = true;
//
//void t1(vector<vector<unsigned char>> &bg)
//{
//	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//	DWORD his;
//	chrono::time_point<chrono::high_resolution_clock> start, end;
//	start = chrono::high_resolution_clock::now();
//
//	
//
//
//
//	end = chrono::high_resolution_clock::now();
//	chrono::duration<double> cost = end - start;
//	cout << cost.count() << endl;
//}
//
//void t2(vector<vector<unsigned char>>& bg)
//{
//	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//	DWORD his;
//	chrono::time_point<chrono::high_resolution_clock> start, end;
//	start = chrono::high_resolution_clock::now();
//
//	for (short i = 0; i < bg.size(); i++)
//	{
//		auto result = std::async(
//			[](HANDLE& h, vector<unsigned char>& l, short& i, DWORD& his) {
//			return t2c(h, l, i, his);
//			}, ref(h), ref(bg[i]), ref(i), ref(his));
//	}
//
//	end = chrono::high_resolution_clock::now();
//	chrono::duration<double> cost = end - start;
//	cout << cost.count() << endl;
//}
//
//void dr(vector <vector<unsigned char>>& bg, COORD& pos)
//{
//	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//	DWORD his;
//	chrono::time_point<chrono::high_resolution_clock> start, end;
//	start = chrono::high_resolution_clock::now();
//	for (short i = 0; i < bg.size(); i++)
//	{
//		for (short j = 0; j < bg[i].size(); j++)
//		{
//			if (bg[i][j] != 16)
//				FillConsoleOutputAttribute(h, bg[i][j] * 16, 1, { short(pos.X + j), short(pos.Y + i) }, &his);
//		}
//	}
//		end = chrono::high_resolution_clock::now();
//		chrono::duration<double> cost = end - start;
//		cout << cost.count() << endl;
//
//
//}
//
//
//void dr2(vector<vector<unsigned char>> &bg, COORD &pos)
//{
//	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//
//	int i = 0;
//	int n = bg.size() * bg[0].size();
//	CHAR_INFO* bg2 = new CHAR_INFO[n];
//	CHAR_INFO* bg3 = new CHAR_INFO[n];
//	CHAR_INFO buffer[80 * 25]; // Assuming a buffer size of 80x25 characters
//
//	 Fill the buffer with different character and color attribute data
//	for (int i = 0; i <n; i++) {
//		bg2[i].Char.UnicodeChar = ' '; // Different characters ('A' to 'Z')
//		bg2[i].Attributes = 0 + bg[i / bg[0].size()][i % bg[0].size()] * 16;
//		bg3[i].Char.UnicodeChar = ' '; // Different characters ('A' to 'Z')
//		bg3[i].Attributes = 15 * 16;
//	}
//
//
//	COORD bufferSize = { bg[0].size(), bg.size()};
//	COORD bufferCoord = { 0, 0 };
//	
//
//
//	chrono::time_point<chrono::high_resolution_clock> start, end;
//
//
//	const int desiredFPS = 60;
//	const std::chrono::duration<double> frameTime(1.0 / desiredFPS);
//	auto previousTime = std::chrono::high_resolution_clock::now();
//	auto currentTime = previousTime;
//	const chrono::duration<double> wait(0.01);
//	while (pos.X < 380) {	
//		currentTime = std::chrono::high_resolution_clock::now();
//		std::chrono::duration<double> deltaTime = currentTime - previousTime;
//
//		if (deltaTime >= frameTime) {
//			 Update game logic and handle input here.
//			SMALL_RECT writeRegion = { pos.X, pos.Y,pos.X + bg[0].size() - 1, pos.Y + bg.size() - 1 };
//			 Render the game.
//			WriteConsoleOutputA(h, bg2, bufferSize, { 0,0 }, &writeRegion);
//			
//			std::this_thread::sleep_for(wait);
//			WriteConsoleOutputA(h, bg3, bufferSize, { 0,0 }, &writeRegion);
//			system("cls");
//			pos.X++;
//			 Reset the previous time for the next frame.
//			previousTime = currentTime;
//		}
//
//		 Sleep to control the frame rate.
//		std::this_thread::sleep_for(frameTime - deltaTime);
//	}
//
//
//	start = chrono::high_resolution_clock::now();
//
//
//	
//	end = chrono::high_resolution_clock::now();
//	chrono::duration<double> cost = end - start;
//	cout << cost.count() << endl;
//	delete[]bg2;
//	delete[]bg3;
//}
//
//
//int main() {
//	system("cls");
//	clearConsole();	
//	test();
//	Graphic graphic = Graphic();
//	drawMainMenu(1);
//	cg.startGame();
//	
//	drawSettingMenu(2,false);
//	drawLoadMenu(1);
//	drawScoreboardMenu();
//
//	
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	 Initialize your game state and resources here.
//
//	 The main game loop.
//	
//
//
//	cout << csbi.dwSize.X << " - " << csbi.dwSize.Y << endl;
//	cout << csbi.dwMaximumWindowSize.X << " - " << csbi.dwMaximumWindowSize.Y << endl;
//	cout << csbi.srWindow.Right << " - " << csbi.srWindow.Bottom << endl;
//
//	ifstream ifs;
//	ifs.open("te.txt");
//	vector < vector<unsigned char>> bg;
//	short t;
//	ifs >> t;
//	bg.resize(t);
//	ifs >> t;
//	for (int i = 0; i < bg.size(); i++)
//	{
//		bg[i].resize(t);
//		for (int j = 0; j < bg[i].size(); j++)
//		{
//			int x;
//			ifs >> x;
//			bg[i][j] = x;
//		}
//	}
//	ifs.close();
//	COORD pos = { 0,0 };
//
//	dr2(bg, pos);
//	Sleep(500);
//	system("cls");
//
//	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//	delete[]bg2;
//	dr(bg, pos);
//	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//
//	cout << sizeof(CHAR_INFO);
//
//	
//
//	dr(bg, pos);
//	int mx = bg[0].size();
//	int my = bg.size();
//
//	const int desiredFPS = 45;
//	const std::chrono::duration<double> frameTime(1.0 / desiredFPS);
//	auto previousTime = std::chrono::high_resolution_clock::now();
//	auto currentTime = previousTime;
//	const chrono::duration<double> wait(0.05);
//	while (true) {
//		currentTime = std::chrono::high_resolution_clock::now();
//		std::chrono::duration<double> deltaTime = currentTime - previousTime;
//
//		if (deltaTime >= frameTime) {
//			// Update game logic and handle input here.
//
//			// Render the game.
//
//			dr(bg, pos);
//			
//			std::this_thread::sleep_for(frameTime);
//			era(pos, mx, my);
//
//			pos.X += 1;
//			// Reset the previous time for the next frame.
//			previousTime = currentTime;
//		}
//
//		// Sleep to control the frame rate.
//		std::this_thread::sleep_for(frameTime - deltaTime);
//	}
//
//	t1(bg);
//	//playzone
//	COORD playTL = { 0, 0 };
//	COORD playBR = { ((My_Windows.Right+1)*3)/4, My_Windows.Bottom};
//
//	vector<COORD> roadspawn;
//	
//
//	for (int i = playTL.Y; i <= playBR.Y; i++)
//	{
//		FillConsoleOutputAttribute(h, int(Color::green) * 16 + int(Color::bright_white), playBR.X, { 0, short(playTL.Y + i) }, &his);
//	}
//	COORD p = { 0, 5 };
//	for (int j = 0; j < 5; j++)
//	{
//		
//		for (int i = 0; i < 11; i++)
//		{
//			FillConsoleOutputAttribute(h, int(Color::gray) * 16 + int(Color::bright_white), playBR.X, p, &his);
//			p.Y += 1;
//		}
//		roadspawn.push_back(p);
//		p.Y+= 7;
//	}
//	
//	/*cLion myLion(roadspawn[0].X, roadspawn[0].Y-7);
//	myLion.move(myLion.getPos());*/
//
//
//	system("pause");
//	return 1;
//}