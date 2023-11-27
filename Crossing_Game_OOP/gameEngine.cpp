#include "gameEngine.h"
#include "Map.h"
#include "cGame.h"
#include "cObstacle.h"
#include "cPeople.h"
#include "cAsset.h"

SMALL_RECT My_Windows = { 0, 0, 0, 0 };
SMALL_RECT PlayBoxRect = { 0, 0, 0, 0 };
COORD cGameEngine::buffsize = { 0,0 };
CHAR_INFO* cGameEngine::mainBuffer = nullptr;
CHAR_INFO* cGameEngine::reservedBuffer = nullptr;
HANDLE cGameEngine::Hbuffer1 = 0;
HANDLE cGameEngine::Hbuffer2 = 0;

int cGameEngine::count = 0;
HANDLE cGameEngine::curHandle = 0;

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

	csbie.dwSize = { 618 , 163 };
	csbie.dwCursorPosition = { -1, -1 };
	csbie.dwMaximumWindowSize = csbie.dwSize;
	csbie.srWindow = { 0, 0, 618, 163 };

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

bool cGameEngine::startEngine()
{
	My_Windows = { 0, 0, 617, 162 };
	PlayBoxRect = { 0, 0, 503, 162 };

	system("color f0");
	HideScrollBar();
	DisableCtrButton(false, true, true);
	disableUserSelection();
	disableCtrlHandler();

	FixConsoleBuffer(mainHandle);
	FixConsoleFont(mainHandle);
	HideCursor(mainHandle);

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
	return true;
}

void cGameEngine::cleanEngine()
{
	delete[]mainBuffer;
	delete[]reservedBuffer;
	CloseHandle(Hbuffer1);
	CloseHandle(Hbuffer2);
}

void cGameEngine::refreshBackGround(bool fillNow)
{
	memcpy(mainBuffer, gameMap::currentMap->mapArray, gameMap::currentMap->height * gameMap::currentMap->width * sizeof(CHAR_INFO));
	if (fillNow)
	{
		WriteConsoleOutput(curHandle, mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, { 0,0 }, &PlayBoxRect);
	}
}

void cGameEngine::fillEffectivePixel(CHAR_INFO*& des, const COORD& desSize, CHAR_INFO*& src, const COORD& srcSize, const COORD& StartCoord)
{
	for (int i = 0; i < srcSize.X * srcSize.Y; i++)
	{
		if (src[i].Char.UnicodeChar != L' ')
		{
			des[(StartCoord.Y + i / srcSize.X) * desSize.X + (StartCoord.X + (i % srcSize.X)) % desSize.X] = src[i];
		}
	}
}

void cGameEngine::renderPeople(cPeople* pPeople)
{
	fillEffectivePixel(mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, pPeople->pTexture->textureArray, { pPeople->pTexture->width, pPeople->pTexture->height }, pPeople->topleft);
	/*	->currentFrame = (itera->currentFrame + 1) % itera->nFrame;
	itera->pTexture = itera->pLTexture + itera->currentFrame; */
}

void cGameEngine::renderObstacle(cObstacle* pObstacle)
{
	fillEffectivePixel(mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, pObstacle->pTexture->textureArray, { pObstacle->pTexture->width, pObstacle->pTexture->height }, pObstacle->topleft);
	pObstacle->currentFrame = (pObstacle->currentFrame + 1) % pObstacle->nFrame;
	pObstacle->pTexture = pObstacle->pLTexture + pObstacle->currentFrame;
}

void cGameEngine::updateInfo(cGame* pGame)
{
	for (int i = 0; i < pGame->listWidget.size(); i++)
	{
		pGame->listWidget[i]->show(false);
	}
	for (int i = 0; i < pGame->listLabel.size(); i++)
	{
		pGame->listLabel[i]->show(false);
	}
}

void cGameEngine::pizzaDraw(cGame* pGame)
{
	//clear all entities

	memcpy(mainBuffer, gameMap::currentMap->mapArray, gameMap::currentMap->height * gameMap::currentMap->width * sizeof(CHAR_INFO));

	//put obstacles onto screen buffer
	for (int i = 0; i < pGame->liveObstacles.size(); i++)
	{
		renderObstacle(pGame->liveObstacles[i]);
		pGame->liveObstacles[i]->move();
	}

	//put people onto buffer
	for (int i = 0; i < pGame->livePeople.size(); i++)
	{
		renderPeople(pGame->livePeople[i]);
	}
}

void cGameEngine::maindraw(cGame* pGame)
{
	while (!pGame->isExit)
	{
		if (!pGame->isLose && !pGame->isPause)
		{
			count = 1 - count;
			if (count % 2 == 0) {
				curHandle = Hbuffer1;
			}
			else {
				curHandle = Hbuffer2;
			}

			pizzaDraw(pGame);
			updateInfo(pGame);

			//thread g1(&cGameEngine::pizzaDraw, pGame);
			//thread g2(&cGameEngine::updateInfo, pGame);

			//g1.join();
			//g2.join();

			WriteConsoleOutput(curHandle, mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, { 0,0 }, &PlayBoxRect);
			SetConsoleActiveScreenBuffer(curHandle);
			Sleep(25);
		}		
	}
}

void cGameEngine::showWidget(cWidget* pWidget, bool instant)
{
	SMALL_RECT region = { pWidget->topleft.X, pWidget->topleft.Y, pWidget->botright.X, pWidget->botright.Y };
	WriteConsoleOutput(curHandle, pWidget->WidgetFace.textureArray, { pWidget->WidgetFace.width, pWidget->WidgetFace.height}, { 0,0 }, &region);
	if (instant)
		SetConsoleActiveScreenBuffer(curHandle);
}

void cGameEngine::unshowWidget(cWidget* pWidget, bool instant)
{
	if (!pWidget->parentWindow->WidgetFace.textureArray)
		return;
	SMALL_RECT region = { pWidget->topleft.X, pWidget->topleft.Y, pWidget->botright.X, pWidget->botright.Y };
	short W = pWidget->WidgetFace.getWidth();
	short H = pWidget->WidgetFace.getHeight();

	for (int i = 0; i < W * H; i++)
	{
		cGameEngine::reservedBuffer[i].Attributes = pWidget->parentWindow->WidgetFace.textureArray[(pWidget->offset.Y + i / W) * pWidget->parentWindow->WidgetFace.width + pWidget->offset.X - pWidget->parentWindow->topleft.X + i % W].Attributes;
	}
	WriteConsoleOutput(cGameEngine::curHandle, cGameEngine::reservedBuffer, { W, H }, { 0, 0 }, &region);
	if (instant)
		SetConsoleActiveScreenBuffer(curHandle);
}

void cGameEngine::HighLightButton(cButton* pButton, bool instant)
{
	short W = pButton->OBotright.X - pButton->OTopleft.X + 1;
	short H = pButton->OBotright.Y - pButton->OTopleft.Y + 1;
	SMALL_RECT outerRect = { pButton->OTopleft.X, pButton->OTopleft.Y, pButton->OBotright.X, pButton->OBotright.Y };

	for (int i = 0; i < W * H; i++)
	{
		cGameEngine::reservedBuffer[i].Attributes = 16 * 4 + 4;
	}

	WriteConsoleOutput(curHandle, cGameEngine::reservedBuffer, { W , H }, { 0, 0 }, &outerRect);
	pButton->show(instant);
}

void cGameEngine::UnHighLightButton(cButton* pButton, bool instant)
{
	COORD erasepos = {pButton->offset.X - pButton->bordDensity, pButton->offset.Y - pButton->bordDensity};

	short W = pButton->OBotright.X - pButton->OTopleft.X + 1;
	short H = pButton->OBotright.Y - pButton->OTopleft.Y + 1;
	SMALL_RECT outerRect = { pButton->OTopleft.X, pButton->OTopleft.Y, pButton->OBotright.X, pButton->OBotright.Y };

	for (int i = 0; i < W * H; i++)
	{
		cGameEngine::reservedBuffer[i].Attributes = pButton->parentWindow->WidgetFace.textureArray[(erasepos.Y + i / W) * pButton->parentWindow->WidgetFace.width + erasepos.X + i % W].Attributes;
	}

	WriteConsoleOutput(curHandle, cGameEngine::reservedBuffer, { W , H }, { 0, 0 }, &outerRect);
	pButton->show(instant);
}

void cGameEngine::showLabel(cLabel* pLabel, bool instant)
{
	for (int i = 0; i < pLabel->textLine.size(); i++)
	{
		if (pLabel->textLine[i].pos.X > pLabel->botright.X - pLabel->textLine[i].pChar->width)
			break;
		short W = pLabel->textLine[i].pChar->width;
		short H = pLabel->textLine[i].pChar->height;
		SMALL_RECT charBox = { pLabel->parentWindow->topleft.X + pLabel->textLine[i].pos.X, pLabel->parentWindow->topleft.Y + pLabel->textLine[i].pos.Y, pLabel->parentWindow->topleft.X + pLabel->textLine[i].pos.X + W - 1, pLabel->parentWindow->topleft.X + pLabel->textLine[i].pos.Y + H - 1 };
		memcpy(cGameEngine::reservedBuffer, pLabel->textLine[i].pChar->textureArray, W * H * sizeof(CHAR_INFO));
		for (int j = 0; j < W * H; j++)
		{
			if (pLabel->textLine[i].pChar->textureArray[j].Char.UnicodeChar != L' ')
			{
				cGameEngine::reservedBuffer[j].Attributes = 16 * pLabel->color + pLabel->color;
			}
			else {
				cGameEngine::reservedBuffer[j].Attributes = pLabel->parentWindow->WidgetFace.textureArray[(pLabel->textLine[i].pos.Y + j / W) * pLabel->parentWindow->WidgetFace.width + pLabel->textLine[i].pos.X + j % W].Attributes;
			}
		}

		WriteConsoleOutput(cGameEngine::curHandle, cGameEngine::reservedBuffer, { W, H }, { 0,0 }, &charBox);
		if (instant)
			SetConsoleActiveScreenBuffer(cGameEngine::curHandle);
	}
}

void cGameEngine::unshowLabel(cLabel* pLabel, bool instant)
{
	SMALL_RECT region = { pLabel->topleft.X, pLabel->topleft.Y, pLabel->botright.X, pLabel->botright.Y };
	short W = pLabel->botright.X - pLabel->topleft.X + 1;
	short H = pLabel->botright.Y - pLabel->topleft.Y + 1;

	for (int i = 0; i < W * H; i++)
	{
		cGameEngine::reservedBuffer[i].Attributes = pLabel->parentWindow->WidgetFace.textureArray[(pLabel->offset.Y + i / W) * pLabel->parentWindow->WidgetFace.getWidth() + pLabel->offset.X + i % W].Attributes;
	}
	WriteConsoleOutput(cGameEngine::curHandle, cGameEngine::reservedBuffer, { W, H }, { 0, 0 }, &region);
	if (instant)
		SetConsoleActiveScreenBuffer(curHandle);
}

