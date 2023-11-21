#include "gameEngine.h"

COORD cGameEngine::buffsize = { 0,0 };
CHAR_INFO* cGameEngine::mainBuffer = nullptr;

HANDLE cGameEngine::Hbuffer1 = 0;
HANDLE cGameEngine::Hbuffer2 = 0;

int cGameEngine::count = 0;
HANDLE cGameEngine::curHandle = 0;
short cGameEngine::w = 0;
short cGameEngine::h = 0;


void cGameEngine::startEngine()
{
	buffsize = {short(My_Windows.Right + 1), short(My_Windows.Bottom + 1)};
	mainBuffer = new CHAR_INFO[cGameEngine::buffsize.X * cGameEngine::buffsize.Y];

	Hbuffer1 = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	Hbuffer2 = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleScreenBufferSize(Hbuffer1, buffsize);
	SetConsoleWindowInfo(Hbuffer1, TRUE, &My_Windows);
	SetConsoleScreenBufferSize(Hbuffer2, buffsize);
	SetConsoleWindowInfo(Hbuffer2, TRUE, &My_Windows);
	SetConsoleActiveScreenBuffer(Hbuffer1);
}

void cGameEngine::drawT(cGame* pGame)
{
	//while (!pGame->isPause)
	//{
		count = 1 - count;
		if (count % 2 == 0) {
			curHandle = Hbuffer1;
		}
		else {
			curHandle = Hbuffer2;
		}


		gameMap* curMap = gameMap::getCurrentMap();

		//clear all entities
		memcpy(mainBuffer, curMap->mapArray, curMap->height * curMap->width * sizeof(CHAR_INFO));


		//put obstacles onto screen buffer
		for (int i = 0; i < pGame->liveObstacles.size(); i++)
		{
			cObstacle* itera = pGame->liveObstacles[i];

			w = itera->pTexture->width;
			h = itera->pTexture->height;
			for (int j = 0; j < w * h; j++)
			{
				if (itera->pTexture->textureArray[j].Char.UnicodeChar != L' ') {
					mainBuffer[(itera->topleft.Y + j / w) * curMap->width + itera->topleft.X + (j % w)].Attributes = itera->pTexture->textureArray[j].Attributes;
				}
			}

			itera->currentFrame = (itera->currentFrame + 1) % itera->nFrame;
			itera->pTexture = itera->pLTexture + itera->currentFrame;
		}

		//put people onto buffer
		for (int i = 0; i < pGame->livePeople.size(); i++)
		{
			cPeople* itera = pGame->livePeople[i];
			w = itera->pTexture->width;
			h = itera->pTexture->height;
			for (int j = 0; j < w * h; j++)
			{
				if (itera->pTexture->textureArray[j].Char.UnicodeChar != L' ') {
					mainBuffer[(itera->topleft.Y + j / w) * curMap->width + itera->topleft.X + (j % w)].Attributes = itera->pTexture->textureArray[j].Attributes;
				}
			}
		/*	itera->currentFrame = (itera->currentFrame + 1) % itera->nFrame;
			itera->pTexture = itera->pLTexture + itera->currentFrame;*/
		}

		WriteConsoleOutput(curHandle, mainBuffer, { curMap->width, curMap->height }, { 0,0 }, &My_Windows);
		SetConsoleActiveScreenBuffer(curHandle);
		
		/*if (!pGame->isPause)
		{
			pGame->updatePosObstacle();

		}*/


		//Sleep(10);
	//}
}