#include "setup.h"
#include "Graphics.h"
int main()
{
	system("cls");
	Graphic gr;

	ifstream ifs;
	ifs.open("te.txt");

	short height, width;
	ifs >> height >> width;

	CHAR_INFO* bg1, * buffer1, * buffer2;
	bg1 = new CHAR_INFO[height * width];
	buffer1 = new CHAR_INFO[height * width];
	buffer2 = new CHAR_INFO[height * width];

	for (int i = 0; i < height * width; i++)
	{
		int x;
		ifs >> x;
		CHAR_INFO t = { L' ', x * 16 };
		bg1[i] = t;
	}
	ifs.close();
	ifs.open("c.txt");
	short charH, charW;
	ifs >> charH >> charW;
	CHAR_INFO* player = new CHAR_INFO[charH * charW];

	for (int i = 0; i < charH * charW; i++)
	{
		int x;
		ifs >> x;
		CHAR_INFO t = { L' ', x * 16 };
		player[i] = t;
	}
	ifs.close();

	


	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD topleftPlayer = { 20, 20 };
	
	SMALL_RECT bgRect = { 0, 0, width - 1, height - 1 };

	//memcpy(buffer1, bg1, height * width * sizeof(CHAR_INFO));
	

	while (true)
	{
		float dx = 0, dy = 0;
		WriteConsoleOutput(h, bg1, { width, height }, { 0,0 }, &bgRect);
		SMALL_RECT playerRect = { topleftPlayer.X, topleftPlayer.Y, charW + topleftPlayer.X - 1, charH + topleftPlayer.Y - 1 };
		WriteConsoleOutput(h, player, { charW, charH }, { 0,0 }, &playerRect);
		
		if (GetAsyncKeyState(0x51) < 0)
			break;
		if (GetAsyncKeyState(VK_LEFT) < 0) {
			dx--;
		}

		if (GetAsyncKeyState(VK_RIGHT) < 0) {
			dx++;
		}

		if (GetAsyncKeyState(VK_UP) < 0) {
			dy--;
		}

		if (GetAsyncKeyState(VK_DOWN) < 0) {
			dy++;
		}
		if (topleftPlayer.X + dx >= 0 && topleftPlayer.X + dx < 478 - charW)
			topleftPlayer.X += dx*3;
		if (topleftPlayer.Y + dy >= 0 && topleftPlayer.Y + dy < 101 - charH)
			topleftPlayer.Y += dy*1.5;
	
		Sleep(1.0 / 60 * 1000.0);
	}
	
	
	
	delete []player;
	delete []bg1;
	delete []buffer1;
	delete []buffer2;
}