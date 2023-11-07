#include "setup.h"
#include "Graphics.h"

CHAR_INFO* loader(string filename, short& height, short &width)
{
	ifstream ifs;
	ifs.open(filename);
	ifs >> height >> width;
	CHAR_INFO* res = new CHAR_INFO[height * width];
	for (int i = 0; i < height * width; i++)
	{
		int x;
		ifs >> x;
		if (x == 16)
		{
			CHAR_INFO t = { L'b', 15 * 16 };
			res[i] = t;
		}
		else {
			CHAR_INFO t = { L' ', x * 16 };
			res[i] = t;
		}

	}
	ifs.close();
	return res;
}
int main()
{
	system("cls");
	Graphic gr;

	ifstream ifs;
	ifs.open("te.txt");
	short height, width;
	ifs >> height >> width;

	CHAR_INFO* bg1;
	bg1 = new CHAR_INFO[height * width];

	for (int i = 0; i < height * width; i++)
	{
		int x;
		ifs >> x;
		CHAR_INFO t = { L' ', x * 16 };
		bg1[i] = t;
	}
	ifs.close();
	short charHH, charWH, charHV, charWV;
	
	CHAR_INFO* tankU = loader("tankU.txt", charHV, charWV);
	CHAR_INFO* tankD = loader("tankD.txt", charHV, charWV);
	CHAR_INFO* tankL = loader("tankL.txt", charHH, charWH);
	CHAR_INFO* tankR = loader("tankR.txt", charHH, charWH);



	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 60, 20 };

	SMALL_RECT bgRect = { 0, 0, width - 1, height - 1 };

	//memcpy(buffer1, bg1, height * width * sizeof(CHAR_INFO));
	CHAR_INFO* curTexture = tankR;
	short* curW = &charWH;
	short* curH = &charHH;

	while (true)
	{
		
		bool horizon = true;
		float dx = 0, dy = 0;
		if (GetAsyncKeyState(0x51) < 0)
			break;
		if (GetAsyncKeyState(VK_LEFT) < 0) {
			dx--;
			curTexture = tankL;
			horizon = true;
			curW = &charWH;
			curH = &charHH;
		}

		if (GetAsyncKeyState(VK_RIGHT) < 0) {
			dx++;
			curTexture = tankR;
			horizon = true;
			curW = &charWH;
			curH = &charHH;
		}

		if (GetAsyncKeyState(VK_UP) < 0) {
			dy--;
			curTexture = tankU;
			horizon = false;
			curW = &charWV;
			curH = &charHV;
		}

		if (GetAsyncKeyState(VK_DOWN) < 0) {
			dy++;
			curTexture = tankD;
			horizon = false;
			curW = &charWV;
			curH = &charHV;
		}
		COORD topleftPlayer = { pos.X - 0.5 * *(curW), pos.Y - 0.5 * *(curH) };
		if (horizon)
		{
			if (topleftPlayer.X + dx >= 0 && topleftPlayer.X + dx < 478 - charWH)
				pos.X += dx * 3;
		}
		else {
			if (topleftPlayer.Y + dy >= 0 && topleftPlayer.Y + dy < 101 - charHV)
				pos.Y += dy * 1.5;
		}
		
		CHAR_INFO* pP = new CHAR_INFO[*(curH) * *(curW)];
		memcpy(pP, curTexture, *(curH) * *(curW) * sizeof(CHAR_INFO));
		for (int i = 0; i < *(curH) * *(curW); i++)
		{
			

			if (pP[i].Char.UnicodeChar == L'b') {
				pP[i].Char.UnicodeChar = L' ';
				pP[i].Attributes = bg1[(topleftPlayer.Y + i / *curW) * width + topleftPlayer.X + (i % *curW)].Attributes;
			}

		}

		
		WriteConsoleOutput(h, bg1, { width, height }, { 0,0 }, &bgRect);
		SMALL_RECT playerRect = { topleftPlayer.X, topleftPlayer.Y, *curW + topleftPlayer.X - 1, *curH + topleftPlayer.Y - 1 };
		WriteConsoleOutput(h, pP, { *curW, *curH }, { 0,0 }, &playerRect);
		delete[]pP;
		
		
		
		Sleep(1.0 / 60 * 1000.0);
	}
	
	
	delete []tankL;
	delete []tankR;
	delete []tankU;
	delete []tankD;
	delete []bg1;

}