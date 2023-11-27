#include "cPeople.h"
#include "cAsset.h"
#include "hitbox.h"
#include "gameEngine.h"

cPeople::cPeople() : cPeople({0, 145}) {}
cPeople::cPeople(COORD In_pos) {
	topleft = In_pos;
	mState = true;
	moveCooldown = 0;
	skin = cAsset::assetLoaders(peopleFile);
	pTexture = &skin[2];
	currentFrame = 0;
	Hitbox a({ short(topleft.X + 4), short(2 + topleft.Y) }, { short(skin[0].getWidth() - 4 + topleft.X), short(skin[0].getHeight() - 2 + topleft.Y) });
	mBoxes.push_back(a); 

}
cPeople::~cPeople() {


}

COORD cPeople::getPos() {
	return topleft;
}
void cPeople::setPos(COORD pos) {
	topleft = pos;
}
bool cPeople::getState()
{
	return mState;
}

bool cPeople::isDead() {
	mState = false;
	return true; // why?
}
bool cPeople::isFinish() {
	return true;
}


bool cPeople::move() {
	if (isMoving)
		return false;
	if (moveFuncCooldown > 0)
		return false;
	bool ismove = false;
	bool horizon;
	float dx = 0, dy = 0;
	if (GetAsyncKeyState(VK_LEFT) < 0 && topleft.X > 0) {
		dx--;
		horizon = true;
		ismove = true;
		pTexture = &skin[3];
	}

	if (GetAsyncKeyState(VK_RIGHT) < 0 && topleft.X < PlayBoxRect.Right - pTexture->getWidth()) {
		dx++;	
		horizon = true;
		ismove = true;
		pTexture = &skin[1];

	}

	if (GetAsyncKeyState(VK_UP) < 0) {
		if (topleft.Y == 1)
		{
			topleft.Y = 163;
			passLevel = true;
		}

		if (topleft.Y >= 1) 
		{
			dy--;
			horizon = false;
			ismove = true;
			pTexture = &skin[0];
		}


	} 

	if (GetAsyncKeyState(VK_DOWN) < 0 && topleft.Y < PlayBoxRect.Bottom - pTexture->getHeight() + 1) {
		dy++;
		horizon = false;
		ismove = true;
		pTexture = &skin[2];
	}
	if (ismove )
	{
		moveFuncCooldown = 12;
		moveCooldown = 2;
		isMoving = true;
		if (horizon)
		{
			moveVector = { short(dx * pTexture->getWidth()), 0 };
		}
		else
		{
			moveVector = { 0, short(dy * pTexture->getHeight())};
		}

		return ismove;
	}
}
