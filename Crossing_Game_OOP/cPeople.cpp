#include "cPeople.h"
#include "cAnimal.h"
#include "cVehicle.h"

void cPeople::draw() {
	/*wstring content[4];
	content[0] = L"    ▀    ";
	content[1] = L"  ▄███▄  ";
	content[2] = L" ▀ ███ ▀ ";
	content[3] = L"  ▄█ █▄  ";
	printCharacter(L"         ", {short (pos.X), short(pos.Y - 1)}, Color::bright_white, Color::bright_white);
	printCharacter(L"         ", { short(pos.X), short(pos.Y + 4) }, Color::bright_white, Color::bright_white);
	printCharacter(L"         ", { short(pos.X+1), short(pos.Y + 2) }, Color::bright_white, Color::bright_white);*/
	/*wstring content[4];
	content[0] = L" ▄████";
	content[1] = L"██▄▄▄▄";
	content[2] = L"██████";
	content[3] = L" ██ ██";
	for (int i = 0; i < 4; i++) {
		if (i == 1) {
			printCharacter2(content[i], { pos.X, short(pos.Y + i) }, Color::red, Color::blue);
		}
		else
			printCharacter2(content[i], { pos.X, short(pos.Y + i) }, Color::red, Color::bright_white);
	}*/

	/*CHAR_INFO *character;
	short height, width;*/
	gameMap* pMap = cAsset::getCurrentMap();
	CHAR_INFO* readyBuffer = new CHAR_INFO[pTexture->width * pTexture->height];
	memcpy(readyBuffer, pTexture->textureArray, pTexture->width * pTexture->height * sizeof(CHAR_INFO));


	for (int i = 0; i < pTexture->width * pTexture->height; i++)
	{
		if (readyBuffer[i].Char.UnicodeChar == L' ') {
			readyBuffer[i].Attributes = pMap->mapArray[(topleft.Y + i / pTexture->width) * pMap->width + topleft.X + (i % pTexture->width)].Attributes;
		}
	}
	SMALL_RECT reg = { topleft.X, topleft.Y, topleft.X + pTexture->width - 1, topleft.Y + pTexture->height - 1 };
	WriteConsoleOutput(mainHandle, readyBuffer, { pTexture->width, pTexture->height }, { 0,0 }, &reg);
	delete[]readyBuffer;

	currentFrame = (currentFrame + 1) % skin.size();
	pTexture = &skin[currentFrame];


}

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
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		dx--;
		//horizon = true;
		ismove = true;
	}

	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		dx++;
		//horizon = true;
		ismove = true;

	}

	if (GetAsyncKeyState(VK_UP) < 0) {
		dy--;
		//horizon = false;
		ismove = true;

	}

	if (GetAsyncKeyState(VK_DOWN) < 0) {
		dy++;
		//horizon = false;
		ismove = true;

	}
	if (ismove) {
		int x = 0, y = 0;
		if (topleft.X + dx >= 0 && topleft.X + dx < My_Windows.Right - width) {
			topleft.X += dx * 4;
			x = dx * 4;
		}
			
		if (topleft.Y + dy >= 0 && topleft.Y + dy < My_Windows.Bottom - height) {
			topleft.Y += dy * 2;
			y = dy * 2;
		}

		for (int i = 0; i < mBoxes.size(); i++)
		{
			mBoxes[i].move({ short(x),short(y) });
		}
		//if (horizon)
		//{
		//	if (topleft.X + dx >= 0 && topleft.X + dx < My_Windows.Right - width)
		//	center.X += dx;
		//}
		//else {
		//	if (topleft.Y + dy >= 0 && topleft.Y + dy < My_Windows.Bottom - height)
		//	center.Y += dy;
		//}
		return ismove;
	}
}
//void cPeople::move(Map &map) {
//	/*if (MOVING == 'S') {
//		down();
//	}
//	else if (MOVING == 'W') {
//		up();
//	}
//	else if (MOVING == 'A') {
//		left();
//	}
//	else if (MOVING == 'D') {
//		right();
//	}*/
//	short* curW = &width;
//	short* curH = &height;
//	
//	while (true)
//	{
//		bool horizon = true;
//		float dx = 0, dy = 0;
//		if (GetAsyncKeyState(0x51) < 0)
//			break;
//		if (GetAsyncKeyState(VK_LEFT) < 0) {
//			dx--;
//			horizon = true;
//			curW = &width;
//			curH = &height;
//		}
//
//		if (GetAsyncKeyState(VK_RIGHT) < 0) {
//			dx++;
//			horizon = true;
//			curW = &width;
//			curH = &height;
//		}
//
//		if (GetAsyncKeyState(VK_UP) < 0) {
//			dy--;
//			horizon = false;
//			curW = &width;
//			curH = &height;
//		}
//
//		if (GetAsyncKeyState(VK_DOWN) < 0) {
//			dy++;
//			horizon = false;
//			curW = &width;
//			curH = &height;
//		}
//		COORD topleftPlayer = { position.X - 0.5 * *(curW), position.Y - 0.5 * *(curH) };
//		if (horizon)
//		{
//			//if (topleftPlayer.X + dx >= 0 && topleftPlayer.X + dx < 478 - width)
//				position.X += dx * 3;
//		}
//		else {
//			//if (topleftPlayer.Y + dy >= 0 && topleftPlayer.Y + dy < 101 - height)
//				position.Y += dy * 2.0;
//		}
//		
//		CHAR_INFO* pP = new CHAR_INFO[*(curH) * *(curW)];
//		memcpy(pP, character, *(curH) * *(curW) * sizeof(CHAR_INFO));
//		for (int i = 0; i < *(curH) * *(curW); i++)
//		{
//			if (pP[i].Char.UnicodeChar == L'b') {
//				pP[i].Char.UnicodeChar = L' ';
//				pP[i].Attributes = map.getBG()[(topleftPlayer.Y + i / *curW) * map.getWidth() + topleftPlayer.X + (i % *curW)].Attributes;
//			}
//
//		}
//
//		map.draw();
//		SMALL_RECT playerRect = { topleftPlayer.X, topleftPlayer.Y, *curW + topleftPlayer.X - 1, *curH + topleftPlayer.Y - 1 };
//		WriteConsoleOutput(h, pP, { *curW, *curH }, { 0,0 }, &playerRect);
//		delete[]pP;
//		
//		Sleep(1.0 / 60 * 1000.0);
//	}
//
//}
//bool cPeople::isImpact(cObstacle obsta) {
//	for (auto box : obsta.boxes) {
//		for (auto mbox : mBoxes)
//		{
//			if(mbox.isOverlap(box)) return true;
//		}
//	}
//	return false;
//}

//bool cPeople::isImpactOneLion(cLion *lion) {
//	for (auto box: lion->)

	//COORD pos = (*lion).getPos();
	//short** lionShapeTemp = (*lion).getHitBoxX();
	//short lionShape[5][2];
	//for (int i = 0; i < 5; i++) {
	//	lionShape[i][0] = lionShapeTemp[i][0];
	//	lionShape[i][1] = lionShapeTemp[i][1];
	//}
	//for (int i = 0; i < 5; i++) {
	//	delete[] lionShapeTemp[i];
	//}
	//delete[] lionShapeTemp;
	//for (int i = 0; i < 5; i++) {
	//	if (mX >= lionShape[i][0] && mX < lionShape[i][1] && mY >= pos.Y && mY < pos.Y + 6)

	//		return true;
	//}
	//for (int i = 0; i < 5; i++) {
	//	if (mX + 4 >= lionShape[i][0] && mX < lionShape[i][1] && mY >= pos.Y && mY < pos.Y + 6)
	//		return true;
	//}
	//for (int i = 0; i < 5; i++) {
	//	if (mX >= lionShape[i][0] && mX < lionShape[i][1] && mY + 2 >= pos.Y && mY < pos.Y + 6)
	//		return true;
	//}
	//for (int i = 0; i < 5; i++) {
	//	if (mX + 4 >= lionShape[i][0] && mX < lionShape[i][1] && mY + 2 >= pos.Y && mY < pos.Y + 6)
	//		return true;
	//}
	//return false;
//}

//bool cPeople::isImpactLion(cLion* lion) {
//	for (int i = 0; i < 7; i++) {
//		if (isImpactOneLion(&lion[i])) {
//			isDead();
//			drawLosingTitle();
//			return true;
//		}
//	}
//	return false;
//}
