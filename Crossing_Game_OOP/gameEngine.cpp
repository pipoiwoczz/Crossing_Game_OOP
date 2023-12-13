#include "gameEngine.h"
#include "Map.h"
#include "cGame.h"
#include "cObstacle.h"
#include "cPeople.h"
#include "cAsset.h"
#include "cAnimal.h"
#include "cEnvironment.h"

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


	return true;
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
	if (fillNow)
	{
		WriteConsoleOutput(curHandle, mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, { 0,0 }, &PlayBoxRect);
	}
}

void cGameEngine::fillScreen()
{
	WriteConsoleOutput(curHandle, mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, { 0,0 }, &PlayBoxRect);
	SetConsoleActiveScreenBuffer(curHandle);
}

void cGameEngine::fillScreenWithLastFrame(bool fillNow)
{
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
void cGameEngine::replaceBlankPixel(CHAR_INFO*& des, const COORD& desSize, CHAR_INFO*& src, const COORD& srcSize, const COORD& StartCoord)
{
	for (int i = 0; i < desSize.X * desSize.Y; i++)
	{
		if (des[i].Char.UnicodeChar == L' ')
		{
			des[i].Attributes = src[(StartCoord.Y + i / desSize.X) * srcSize.X + StartCoord.X + (i % desSize.X)].Attributes;
		}
	}
}
void cGameEngine::replaceAllPixel(CHAR_INFO*& des, const COORD& desSize, CHAR_INFO*& src, const COORD& srcSize, const COORD& StartCoord)
{
	for (int i = 0; i < desSize.X * desSize.Y; i++)
	{
		des[i].Attributes = src[(StartCoord.Y + i / desSize.X) * srcSize.X + StartCoord.X + i % desSize.X].Attributes;
	}
}
void cGameEngine::paintBucket(CHAR_INFO* des, const COORD& desSize, short color)
{
	for (int i = 0; i < desSize.X * desSize.Y; i++)
	{
		des[i].Attributes = color * 16 + color;
	}
}

void cGameEngine::playFlashEffect(const COORD& topleft)
{
	fillEffectivePixel(mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, cAsset::flashEffect.textureArray, { cAsset::flashEffect.width, cAsset::flashEffect.height }, topleft);
}

void cGameEngine::renderPeople(cPeople* pPeople)
{
	if (!pPeople->mState)
		return;
	fillEffectivePixel(mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, pPeople->pMotionFrame->textureArray, { pPeople->pMotionFrame->width, pPeople->pMotionFrame->height }, pPeople->topleft);
	/*	->currentFrame = (itera->currentFrame + 1) % itera->nFrame;
	itera->pMotionFrame = itera->pLMotionFrames + itera->currentFrame; */
}

void cGameEngine::renderObstacle(cObstacle* pObstacle)
{
	if (pObstacle->pMotionFrame == nullptr)
		return;

	if (pObstacle->timeUntilRender == 0)
	{
		if (!pObstacle->isStop)
		{
			pObstacle->currentFrame = (pObstacle->currentFrame + 1) % pObstacle->numMotionFrame;
			pObstacle->pMotionFrame = pObstacle->pLMotionFrames + pObstacle->currentFrame;
		}
		/*else {
			pObstacle->currentFrame = 0;
			pObstacle->pMotionFrame = pObstacle->pLMotionFrames;
		}*/

		
		pObstacle->timeUntilRender = pObstacle->defaulttimeUntilRender;
	}
	else {
		pObstacle->timeUntilRender--;
	}

	fillEffectivePixel(mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, pObstacle->pMotionFrame->textureArray, { pObstacle->pMotionFrame->width, pObstacle->pMotionFrame->height }, pObstacle->topleft);
}

void cGameEngine::renderEnvironment(cEnvironment* pEnvironmentObject)
{
	if (pEnvironmentObject->pMotionFrame == nullptr)
		return;
	if (pEnvironmentObject->hasFrameMove)
	{
		if (pEnvironmentObject->timeUntilRender == 0)
		{
			if (!pEnvironmentObject->isStop)
			{
				pEnvironmentObject->currentFrame = (pEnvironmentObject->currentFrame + 1) % pEnvironmentObject->numMotionFrame;
				pEnvironmentObject->pMotionFrame = pEnvironmentObject->pLMotionFrames + pEnvironmentObject->currentFrame;
			}
			/*else {
				pObstacle->currentFrame = 0;
				pObstacle->pMotionFrame = pObstacle->pLMotionFrames;
			}*/


			pEnvironmentObject->timeUntilRender = pEnvironmentObject->defaulttimeUntilRender;
		}
		else {
			pEnvironmentObject->timeUntilRender--;
		}
	}

	
	fillEffectivePixel(mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, pEnvironmentObject->pMotionFrame->textureArray, { pEnvironmentObject->pMotionFrame->width, pEnvironmentObject->pMotionFrame->height }, pEnvironmentObject->topleft);
}

void cGameEngine::renderWidget(cWidget* pWidget)
{
if (!pWidget->WidgetFace.textureArray)
		return;
	fillEffectivePixel(mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, pWidget->WidgetFace.textureArray, { pWidget->WidgetFace.width, pWidget->WidgetFace.height }, pWidget->topleft);
}



bool cGameEngine::showWidget(cWidget* pWidget, bool instant)
{
	if (!pWidget->WidgetFace.textureArray || !pWidget->parentWindow->WidgetFace.textureArray)
		return false;
	SMALL_RECT region = { pWidget->topleft.X, pWidget->topleft.Y, pWidget->botright.X, pWidget->botright.Y };
	memcpy(reservedBuffer, pWidget->WidgetFace.textureArray, pWidget->WidgetFace.width * pWidget->WidgetFace.height * sizeof(CHAR_INFO));
	if (pWidget->parentWindow)
		replaceBlankPixel(reservedBuffer, { pWidget->WidgetFace.width, pWidget->WidgetFace.height }, pWidget->parentWindow->WidgetFace.textureArray, { pWidget->parentWindow->WidgetFace.width, pWidget->parentWindow->WidgetFace.height }, pWidget->offset);
	WriteConsoleOutput(Hbuffer1, reservedBuffer, { pWidget->WidgetFace.width, pWidget->WidgetFace.height }, { 0,0 }, &region);
	WriteConsoleOutput(Hbuffer2, reservedBuffer, { pWidget->WidgetFace.width, pWidget->WidgetFace.height}, { 0,0 }, &region);
	if (instant)
		SetConsoleActiveScreenBuffer(curHandle);
	return true;
}

bool cGameEngine::unshowWidget(cWidget* pWidget, bool instant)
{
	if (!pWidget->WidgetFace.textureArray || !pWidget->parentWindow->WidgetFace.textureArray)
		return false;
	SMALL_RECT region = { pWidget->topleft.X, pWidget->topleft.Y, pWidget->botright.X, pWidget->botright.Y };
	replaceAllPixel(reservedBuffer, { pWidget->WidgetFace.width,  pWidget->WidgetFace.height }, pWidget->parentWindow->WidgetFace.textureArray, { pWidget->parentWindow->WidgetFace.width, pWidget->parentWindow->WidgetFace.height }, pWidget->offset);

	WriteConsoleOutput(Hbuffer1, reservedBuffer, { pWidget->WidgetFace.width, pWidget->WidgetFace.height }, { 0, 0 }, &region);
	WriteConsoleOutput(Hbuffer2, reservedBuffer, {pWidget->WidgetFace.width, pWidget->WidgetFace.height }, { 0, 0 }, &region);
	if (instant)
		SetConsoleActiveScreenBuffer(curHandle);
	return true;

}

bool cGameEngine::HighLightButton(cButton* pButton, bool instant)
{
	if (!pButton->WidgetFace.textureArray || !pButton->parentWindow->WidgetFace.textureArray)
		return false;
	short W = pButton->OBotright.X - pButton->OTopleft.X + 1;
	short H = pButton->OBotright.Y - pButton->OTopleft.Y + 1;
	SMALL_RECT outerRect = { pButton->OTopleft.X, pButton->OTopleft.Y, pButton->OBotright.X, pButton->OBotright.Y };

	for (int i = 0; i < W * H; i++)
	{
		cGameEngine::reservedBuffer[i].Attributes = 16 * 4 + 4;
	}

	WriteConsoleOutput(Hbuffer1, reservedBuffer, { W , H }, { 0, 0 }, &outerRect);
	WriteConsoleOutput(Hbuffer2, reservedBuffer, { W , H }, { 0, 0 }, &outerRect);
	pButton->show(instant);
	return true;

}

bool cGameEngine::UnHighLightButton(cButton* pButton, bool instant)
{
	if (!pButton->WidgetFace.textureArray || !pButton->parentWindow->WidgetFace.textureArray)
		return false;
	COORD erasepos = {pButton->offset.X - pButton->bordDensity, pButton->offset.Y - pButton->bordDensity};

	SMALL_RECT outerRect = { pButton->OTopleft.X, pButton->OTopleft.Y, pButton->OBotright.X, pButton->OBotright.Y };
	replaceAllPixel(reservedBuffer, {short(pButton->OBotright.X - pButton->OTopleft.X + 1), short(pButton->OBotright.Y - pButton->OTopleft.Y + 1)}, pButton->parentWindow->WidgetFace.textureArray, { pButton->parentWindow->WidgetFace.width, pButton->parentWindow->WidgetFace.height }, erasepos);

	WriteConsoleOutput(Hbuffer1, reservedBuffer, { short(pButton->OBotright.X - pButton->OTopleft.X + 1), short(pButton->OBotright.Y - pButton->OTopleft.Y + 1) }, { 0, 0 }, &outerRect);
	WriteConsoleOutput(Hbuffer2, reservedBuffer, {short(pButton->OBotright.X - pButton->OTopleft.X + 1), short(pButton->OBotright.Y - pButton->OTopleft.Y + 1)}, { 0, 0 }, &outerRect);
	pButton->show(instant);
	return true;

}

bool cGameEngine::showLabel(cLabel* pLabel, bool instant)
{
	if (pLabel->textLine.size() == 0)
		return false;

	for (int i = 0; i < pLabel->textLine.size(); i++)
	{
		if (pLabel->textLine[i].pos.X > pLabel->botright.X - pLabel->textLine[i].pChar->width)
			break;
		short W = pLabel->textLine[i].pChar->width;
		short H = pLabel->textLine[i].pChar->height;
		SMALL_RECT charBox = {pLabel->textLine[i].pos.X, pLabel->textLine[i].pos.Y, pLabel->textLine[i].pos.X + pLabel->textLine[i].pChar->width - 1, pLabel->textLine[i].pos.Y + pLabel->textLine[i].pChar->height - 1 };
		memcpy(reservedBuffer, pLabel->textLine[i].pChar->textureArray, W * H * sizeof(CHAR_INFO));

		COORD writepos = pLabel->parentWindow->getTL();
		writepos = { short(pLabel->textLine[i].pos.X - writepos.X), short(pLabel->textLine[i].pos.Y - writepos.Y) };
		for (int j = 0; j < W * H; j++)
		{
			if (pLabel->textLine[i].pChar->textureArray[j].Char.UnicodeChar != L' ')
			{
				reservedBuffer[j].Attributes = 16 * pLabel->color + pLabel->color;
			}
			else {
				reservedBuffer[j].Attributes = pLabel->parentWindow->WidgetFace.textureArray[(writepos.Y + j / W) * pLabel->parentWindow->WidgetFace.width + writepos.X + j % W].Attributes;
			}
		}

		WriteConsoleOutput(Hbuffer1, reservedBuffer, { W, H }, { 0,0 }, &charBox);
		WriteConsoleOutput(Hbuffer2, reservedBuffer, { W, H }, { 0,0 }, &charBox);
		if (instant)
			SetConsoleActiveScreenBuffer(curHandle);
	}
	return true;

}

bool cGameEngine::unshowLabel(cLabel* pLabel, bool instant)
{
	if (!pLabel->parentWindow->WidgetFace.textureArray)
		return false;
	SMALL_RECT region = { pLabel->topleft.X, pLabel->topleft.Y, pLabel->botright.X, pLabel->botright.Y };

	replaceAllPixel(reservedBuffer, { short(pLabel->botright.X - pLabel->topleft.X + 1), short(pLabel->botright.Y - pLabel->topleft.Y + 1)}, pLabel->parentWindow->WidgetFace.textureArray, {pLabel->parentWindow->WidgetFace.width, pLabel->parentWindow->WidgetFace.height}, pLabel->offset);

	WriteConsoleOutput(Hbuffer1, reservedBuffer, { short(pLabel->botright.X - pLabel->topleft.X + 1), short(pLabel->botright.Y - pLabel->topleft.Y + 1) }, { 0, 0 }, &region);
	WriteConsoleOutput(Hbuffer2, reservedBuffer, { short(pLabel->botright.X - pLabel->topleft.X + 1), short(pLabel->botright.Y - pLabel->topleft.Y + 1) }, { 0, 0 }, &region);
	if (instant)
		SetConsoleActiveScreenBuffer(curHandle);
	return true;

}

bool cGameEngine::showBar(cBar* pBar, bool instant)
{
	if (pBar->length == 0 || !pBar->parentWindow->WidgetFace.textureArray)
		return false;

	SMALL_RECT region = { pBar->topleft.X,  pBar->topleft.Y,  pBar->botright.X,  pBar->botright.Y };
	COORD writepos = pBar->topleft;

	paintBucket(reservedBuffer, { pBar->length, pBar->width }, pBar->backcolor);
	WriteConsoleOutput(Hbuffer1, reservedBuffer, { pBar->length, pBar->width }, { 0,0 }, &region);
	WriteConsoleOutput(Hbuffer2, reservedBuffer, { pBar->length, pBar->width }, { 0,0 }, &region);

	region.Right = region.Right - (pBar->length - pBar->currentFill);
	paintBucket(reservedBuffer, { pBar->currentFill, pBar->width }, pBar->forecolor);
	WriteConsoleOutput(Hbuffer1, reservedBuffer, { pBar->currentFill, pBar->width }, { 0,0 }, &region);
	WriteConsoleOutput(Hbuffer2, reservedBuffer, { pBar->currentFill, pBar->width }, { 0,0 }, &region);

	if (instant)
		SetConsoleActiveScreenBuffer(curHandle);
	return true;

}

bool cGameEngine::unshowBar(cBar* pBar, bool instant)
{
	if (pBar->length == 0 || !pBar->parentWindow->WidgetFace.textureArray)
		return false;
	SMALL_RECT region = { pBar->topleft.X,  pBar->topleft.Y,  pBar->botright.X,  pBar->botright.Y };
	replaceAllPixel(reservedBuffer, { pBar->length, pBar->width }, pBar->parentWindow->WidgetFace.textureArray, { pBar->parentWindow->WidgetFace.width, pBar->parentWindow->WidgetFace.height }, pBar->offset);
	WriteConsoleOutput(Hbuffer1, reservedBuffer, { pBar->length, pBar->width }, { 0,0 }, &region);
	WriteConsoleOutput(Hbuffer2, reservedBuffer, { pBar->length, pBar->width }, { 0,0 }, &region);
	if (instant)
		SetConsoleActiveScreenBuffer(curHandle);
	return true;

}

void cGameEngine::playEffect(cObstacle* obsta, cPeople* player)
{
	if (!obsta || !player)
		return;
	short w = cAsset::FxFrame.width;
	short h = cAsset::FxFrame.height;
	COORD OuterFrameTopLeft = { 100, 31 };

	replaceBlankPixel(cAsset::FxFrame.textureArray, { w,h }, mainBuffer, { gameMap::currentMap->width, gameMap::currentMap->height }, { 100,31 });

	SMALL_RECT fxframe = { OuterFrameTopLeft.X, OuterFrameTopLeft.Y, OuterFrameTopLeft.X + w - 1, OuterFrameTopLeft.Y + h - 1 };


	player->pMotionFrame = &player->skin[3];
	//replaceBlankPixel(player->pMotionFrame->textureArray, { player->pMotionFrame->width, player->pMotionFrame->height }, cAsset::FxFrame.textureArray, { w, h }, { 120, 25 });

	COORD startpos = { 50, 25 };
	for (int j = 0; j < obsta->numFxFrame; j++)
	{
		memcpy(reservedBuffer, cAsset::FxFrame.textureArray, w * h * sizeof(CHAR_INFO));

		if (j != obsta->numFxFrame-1)
			fillEffectivePixel(reservedBuffer, { w, h }, player->pMotionFrame->textureArray, { player->pMotionFrame->width, player->pMotionFrame->height }, { short(50 + obsta->pLFxFrames->width - player->pMotionFrame->width), short (30 + obsta->pLFxFrames->height - player->pMotionFrame->height)});

		fillEffectivePixel(reservedBuffer, { w, h }, (obsta->pLFxFrames + j)->textureArray, { (obsta->pLFxFrames + j)->width, (obsta->pLFxFrames + j)->height }, {50, 30});

		SMALL_RECT reg = { OuterFrameTopLeft.X + startpos.X , OuterFrameTopLeft.Y + startpos.Y,   OuterFrameTopLeft.X + startpos.X + (obsta->pLFxFrames + j)->width - 1,  OuterFrameTopLeft.X + startpos.X + (obsta->pLFxFrames + j)->height - 1 };
		WriteConsoleOutput(Hbuffer1, reservedBuffer, { w, h }, { 0, 0 }, &fxframe);
		WriteConsoleOutput(Hbuffer2, reservedBuffer, { w, h }, { 0, 0 }, &fxframe);
		if (j == 1)
			Sleep(500);

		Sleep(400);

	}
}