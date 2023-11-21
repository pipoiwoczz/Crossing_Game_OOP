#include "cPeople.h"

//void cPeople::draw() {
//	/*wstring content[4];
//	content[0] = L"    ▀    ";
//	content[1] = L"  ▄███▄  ";
//	content[2] = L" ▀ ███ ▀ ";
//	content[3] = L"  ▄█ █▄  ";
//	printCharacter(L"         ", {short (pos.X), short(pos.Y - 1)}, Color::bright_white, Color::bright_white);
//	printCharacter(L"         ", { short(pos.X), short(pos.Y + 4) }, Color::bright_white, Color::bright_white);
//	printCharacter(L"         ", { short(pos.X+1), short(pos.Y + 2) }, Color::bright_white, Color::bright_white);*/
//	/*wstring content[4];
//	content[0] = L" ▄████";
//	content[1] = L"██▄▄▄▄";
//	content[2] = L"██████";
//	content[3] = L" ██ ██";
//	for (int i = 0; i < 4; i++) {
//		if (i == 1) {
//			printCharacter2(content[i], { pos.X, short(pos.Y + i) }, Color::red, Color::blue);
//		}
//		else
//			printCharacter2(content[i], { pos.X, short(pos.Y + i) }, Color::red, Color::bright_white);
//	}*/
//
//	/*CHAR_INFO *character;
//	short height, width;*/
//	gameMap* pMap = gameMap::getCurrentMap();
//	CHAR_INFO* readyBuffer = new CHAR_INFO[pTexture->getWidth() * pTexture->getHeight()];
//	memcpy(readyBuffer, pTexture->textureArray, pTexture->getWidth() * pTexture->getHeight() * sizeof(CHAR_INFO));
//
//
//	for (int i = 0; i < pTexture->getWidth() * pTexture->getHeight(); i++)
//	{
//		if (readyBuffer[i].Char.UnicodeChar == L' ') {
//			readyBuffer[i].Attributes = pMap->mapArray[(topleft.Y + i / pTexture->getWidth()) * pMap->width + topleft.X + (i % pTexture->getWidth())].Attributes;
//		}
//	}
//	SMALL_RECT reg = { topleft.X, topleft.Y, topleft.X + pTexture->getWidth() - 1, topleft.Y + pTexture->getHeight() - 1 };
//	WriteConsoleOutput(mainHandle, readyBuffer, { pTexture->getWidth(), pTexture->getHeight() }, { 0,0 }, &reg);
//	delete[]readyBuffer;
//
//	currentFrame = (currentFrame + 1) % skin.size();
//	pTexture = &skin[currentFrame];
//
//
//}

void cPeople::up(){
	topleft.Y--;
}
//
void cPeople::down() {
	topleft.Y++;
}
//
//void delPeople(COORD pos) {
//	int y = pos.Y;
//	for (int i = y; i < y + 4; i++) {
//		printCharacter2(L" ", { pos.X, short(i) }, Color::bright_white, Color::bright_white);
//	}
//}
//
void cPeople::left() {
	topleft.X--;
}
//
//
void cPeople::right() {
	topleft.X++;
}

bool cPeople::move() {
	bool ismove = false;
	//bool horizon = true;
	float dx = 0, dy = 0;
	if (GetAsyncKeyState(VK_LEFT) < 0 && topleft.X > 0) {
		dx--;
		//horizon = true;
		ismove = true;
	}

	if (GetAsyncKeyState(VK_RIGHT) < 0 && topleft.X < 479 - pTexture->getWidth() + 1) {
		dx++;	
		//horizon = true;
		ismove = true;

	}

	if (GetAsyncKeyState(VK_UP) < 0 && topleft.Y > 0) {
		dy--;
		//horizon = false;
		ismove = true;

	}

	if (GetAsyncKeyState(VK_DOWN) < 0 && topleft.Y < My_Windows.Bottom - pTexture->getHeight() + 1) {
		dy++;
		//horizon = false;
		ismove = true;

	}
	if (ismove) {
		topleft.X += dx;
		topleft.Y += dy;
		for (int i = 0; i < mBoxes.size(); i++)
		{
			mBoxes[i].set({ short(topleft.X + 4), short(2 + topleft.Y) }, { short(pTexture->getWidth() - 4 + topleft.X), short(pTexture->getHeight() - 2 + topleft.Y) });
		}
		return ismove;
	}
}
