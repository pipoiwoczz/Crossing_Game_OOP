#include "gameEngine.h"
#include "Map.h"
#include "cGame.h"
#include "cObstacle.h"
#include "cPeople.h"
#include "cAsset.h"

SMALL_RECT My_Windows = { 0, 0, 0, 0 };
COORD cGameEngine::buffsize = { 0,0 };
CHAR_INFO* cGameEngine::mainBuffer = nullptr;
CHAR_INFO* cGameEngine::reservedBuffer = nullptr;
HANDLE cGameEngine::Hbuffer1 = 0;
HANDLE cGameEngine::Hbuffer2 = 0;

int cGameEngine::count = 0;
HANDLE cGameEngine::curHandle = 0;
short cGameEngine::w = 0;
short cGameEngine::h = 0;

COORD cGameEngine::GetMonitorDimension()
{
	HDC hdc = GetDC(0);

	int dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
	int dpiY = GetDeviceCaps(hdc, LOGPIXELSY);

	int screenWidth = GetDeviceCaps(hdc, HORZRES);
	int screenHeight = GetDeviceCaps(hdc, VERTRES);

	int scaledWidth = MulDiv(screenWidth, 96, dpiX);
	int scaledHeight = MulDiv(screenHeight, 96, dpiY);

	ReleaseDC(0, hdc);

	return { short(scaledWidth), short(scaledHeight)};
}

void cGameEngine::FixConsoleBuffer(HANDLE H)
{
	CONSOLE_SCREEN_BUFFER_INFOEX csbie;
	csbie.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	GetConsoleScreenBufferInfoEx(mainHandle, &csbie);

	csbie.dwSize = { 504 , 163 };
	csbie.dwCursorPosition = { -1, -1 };
	csbie.dwMaximumWindowSize = csbie.dwSize;
	csbie.srWindow = { 0, 0, 504, 163 };

	SetConsoleScreenBufferSize(H, csbie.dwSize);
	SetConsoleScreenBufferInfoEx(H, &csbie);
}

void cGameEngine::FixConsoleFont(HANDLE H)
{
	CONSOLE_SCREEN_BUFFER_INFOEX csbie;
	csbie.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);

	GetConsoleScreenBufferInfoEx(mainHandle, &csbie);
	COORD screenDimension = GetMonitorDimension();

	GetCurrentConsoleFontEx(mainHandle, 0, &cfi);
	cfi.dwFontSize.Y = screenDimension.Y / csbie.dwSize.Y;
	cfi.dwFontSize.X = screenDimension.X / csbie.dwSize.X;
	SetCurrentConsoleFontEx(H, 0, &cfi);
}

void cGameEngine::HideCursor(HANDLE H)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(H, &info);
}

void cGameEngine::HideScrollBar()
{
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, false);
}
void cGameEngine::DisableCtrButton(bool Close, bool Min, bool Max) {
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	if (Close == 1)
	{
		DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	if (Min == 1)
	{
		DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	}
	if (Max == 1)
	{
		DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	}
}

void cGameEngine::disableUserSelection()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_QUICK_EDIT_MODE));
}

void cGameEngine::disableCtrlHandler()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_MOUSE_INPUT);
}

void cGameEngine::startEngine()
{
	system("color f0");
	HideScrollBar();
	DisableCtrButton(false, true, true);
	disableUserSelection();
	disableCtrlHandler();

	FixConsoleBuffer(mainHandle);
	FixConsoleFont(mainHandle);
	HideCursor(mainHandle);

	My_Windows = { 0, 0, 503, 162 };
	buffsize = { short(My_Windows.Right + 1), short(My_Windows.Bottom + 1) };

	Hbuffer1 = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	FixConsoleBuffer(Hbuffer1);
	FixConsoleFont(Hbuffer1);
	HideCursor(mainHandle);
	bool a = SetConsoleScreenBufferSize(Hbuffer1, buffsize);
	bool b = SetConsoleWindowInfo(Hbuffer1, TRUE, &My_Windows);

	Hbuffer2 = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	FixConsoleBuffer(Hbuffer2);
	FixConsoleFont(Hbuffer2);
	HideCursor(mainHandle);
	a = SetConsoleScreenBufferSize(Hbuffer2, buffsize);
	b = SetConsoleWindowInfo(Hbuffer2, TRUE, &My_Windows);

	mainBuffer = new CHAR_INFO[cGameEngine::buffsize.X * cGameEngine::buffsize.Y];
	reservedBuffer = new CHAR_INFO[cGameEngine::buffsize.X * cGameEngine::buffsize.Y];

	curHandle = Hbuffer1;
	SetConsoleActiveScreenBuffer(Hbuffer1);

	cAsset::alphabetLoader();
	cAsset::numberLoader();
}

void cGameEngine::cleanEngine()
{
	delete[]mainBuffer;
	delete[]reservedBuffer;
	CloseHandle(Hbuffer1);
	CloseHandle(Hbuffer2);
}

void cGameEngine::swapHandle()
{
	count = 1 - count;
	if (count % 2 == 0) {
		curHandle = Hbuffer1;
	}
	else {
		curHandle = Hbuffer2;
	}
}

void cGameEngine::refreshBackGround(bool fillNow)
{
	memcpy(mainBuffer, gameMap::currentMap->mapArray, gameMap::currentMap->height * gameMap::currentMap->width * sizeof(CHAR_INFO));
	WriteConsoleOutput(curHandle, mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, { 0,0 }, &My_Windows);
	if (fillNow)
	{
		SetConsoleActiveScreenBuffer(curHandle);
	}
}

void cGameEngine::renderPeople(cPeople* pPeople)
{
	w = pPeople->pTexture->width;
	h = pPeople->pTexture->height;
	for (int j = 0; j < w * h; j++)
	{
		if (pPeople->pTexture->textureArray[j].Char.UnicodeChar != L' ') {
			/*CHAR_INFO* t1 = &mainBuffer[pPeople->topleft.Y * gameMap::currentMap->width + (pPeople->topleft.X + (j % w)) % (gameMap::currentMap->width) + (j / w) * gameMap::currentMap->width];
			CHAR_INFO* t2 = &pPeople->pTexture->textureArray[j];
			*t1 = *t2;*/
			mainBuffer[(pPeople->topleft.Y + j / w) * gameMap::currentMap->width + pPeople->topleft.X + j % w] = pPeople->pTexture->textureArray[j];
		}
	}
}

void cGameEngine::renderObstacle(cObstacle* pObstacle)
{
	w = pObstacle->pTexture->width;
	h = pObstacle->pTexture->height;
	for (int j = 0; j < w * h; j++)
	{
		if (pObstacle->pTexture->textureArray[j].Char.UnicodeChar != L' ') {
			mainBuffer[pObstacle->topleft.Y * gameMap::currentMap->width + (pObstacle->topleft.X + (j % w)) % (gameMap::currentMap->width) + (j / w) * gameMap::currentMap->width].Attributes = pObstacle->pTexture->textureArray[j].Attributes;
		}
	}

	pObstacle->currentFrame = (pObstacle->currentFrame + 1) % pObstacle->nFrame;
	pObstacle->pTexture = pObstacle->pLTexture + pObstacle->currentFrame;
	pObstacle->move();
}

void cGameEngine::pizzaDraw(cGame* pGame)
{
	while (!pGame->isExit)
	{
		if (pGame->isPause || pGame->isLose)
			continue;
		WriteConsoleOutput(curHandle, mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, { 0,0 }, &My_Windows);
		SetConsoleActiveScreenBuffer(curHandle);
		count = 1 - count;
		if (count % 2 == 0) {
			curHandle = Hbuffer1;
		}
		else {
			curHandle = Hbuffer2;
		}
		//clear all entities
		
		memcpy(mainBuffer, gameMap::currentMap->mapArray, gameMap::currentMap->height * gameMap::currentMap->width * sizeof(CHAR_INFO));

		//put obstacles onto screen buffer
		for (int i = 0; i < pGame->liveObstacles.size(); i++)
		{
			cObstacle* itera = pGame->liveObstacles[i];
			renderObstacle(itera);
		}

		//put people onto buffer
		for (int i = 0; i < pGame->livePeople.size(); i++)
		{
			cPeople* itera = pGame->livePeople[i];
			renderPeople(itera);
			
		/*	itera->currentFrame = (itera->currentFrame + 1) % itera->nFrame;
			itera->pTexture = itera->pLTexture + itera->currentFrame; */
		}
		
		
		Sleep(25);
	}
}

