#include "cAnimal.h"
#include "cVehicle.h"
#include "cPeople.h"
#include "cGame.h"
#include "Graphics.h"

char MOVING;
cGame cg = cGame();
bool isRunningDrawGame = true;


int main() {
	system("cls");
	clearConsole();
//	test();
	Graphic graphic = Graphic();
	//drawGameTitle();
	//cg.startGame();

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	//system("color 30");

	DWORD his;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(h, &csbi);

	//cout << csbi.dwSize.X << " - " << csbi.dwSize.Y << endl;
	//cout << csbi.dwMaximumWindowSize.X << " - " << csbi.dwMaximumWindowSize.Y << endl;
	//cout << csbi.srWindow.Right << " - " << csbi.srWindow.Bottom << endl;

	//ifstream ifs;
	//ifs.open("te.txt");
	//vector < vector<unsigned char>> bg;
	//bg.resize(csbi.srWindow.Bottom);
	//for (int i = 0; i < bg.size(); i++)
	//{
	//	bg[i].resize(csbi.srWindow.Right);
	//	for (int j = 0; j < bg[i].size(); j++)
	//	{
	//		ifs >> bg[i][j];
	//	}
	//}

	//for (short i = 0; i < bg.size(); i++)
	//{
	//	for (short j = 0; j < bg[i].size(); j++)
	//	{
	//		FillConsoleOutputAttribute(h, bg[i][j] * 16, 1, { j,i }, &his);
	//	}
	//}
	////playzone
	//COORD playTL = { 0, 0 };
	//COORD playBR = { ((My_Windows.Right+1)*3)/4, My_Windows.Bottom};

	//vector<COORD> roadspawn;
	//

	//for (int i = playTL.Y; i <= playBR.Y; i++)
	//{
	//	FillConsoleOutputAttribute(h, int(Color::green) * 16 + int(Color::bright_white), playBR.X, { 0, short(playTL.Y + i) }, &his);
	//}
	//COORD p = { 0, 5 };
	//for (int j = 0; j < 5; j++)
	//{
	//	
	//	for (int i = 0; i < 11; i++)
	//	{
	//		FillConsoleOutputAttribute(h, int(Color::gray) * 16 + int(Color::bright_white), playBR.X, p, &his);
	//		p.Y += 1;
	//	}
	//	roadspawn.push_back(p);
	//	p.Y+= 7;
	//}
	//
	/*cLion myLion(roadspawn[0].X, roadspawn[0].Y-7);
	myLion.move(myLion.getPos());*/


	system("pause");
	return 1;
}