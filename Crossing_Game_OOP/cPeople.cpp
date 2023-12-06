#include "cPeople.h"
#include "cAsset.h"
#include "gameEngine.h"

cPeople::cPeople() : cPeople({0, 145}) {}
cPeople::cPeople(COORD In_pos) {
	topleft = In_pos;
	mState = true;
	moveCooldown = 0;
	if (isRabbit)
		skin = cAsset::assetLoaders(peopleFile, RabbitPrefix);
	else
		skin = cAsset::assetLoaders(peopleFile, CubePrefix);


	pMotionFrame = &skin[2];
	currentFrame = 0;

	mBox.set({ short(topleft.X + 4), short(2 + topleft.Y) }, { short(skin[0].getWidth() - 4 + topleft.X), short(skin[0].getHeight() - 2 + topleft.Y) });
}
cPeople::~cPeople() {


}

COORD cPeople::getPos() {
	return topleft;
}
void cPeople::setPos(COORD pos) {
	topleft = pos;
	mBox.set({ short(topleft.X + 4), short(2 + topleft.Y) }, { short(skin[0].getWidth() - 4 + topleft.X), short(skin[0].getHeight() - 2 + topleft.Y) });
}
bool cPeople::getState()
{
	return mState;
}

void cPeople::setState(bool state)
{
	mState = state;
}

bool cPeople::isDead() {
	mState = false;
	return true; // why?
}
bool cPeople::isFinish() {
	return true;
}

void cPeople::changeskin(bool isChange)
{
	isRabbit = (isRabbit && isChange);
}


bool cPeople::move() {
	if (moveCooldown > 0)
	{
		moveCooldown--;
		return false;
	}
	bool ismove = false;
	bool horizon;
	float dx = 0, dy = 0;
	if (GetAsyncKeyState(VK_LEFT) < 0 && topleft.X > 0) {
		dx--;
		horizon = true;
		ismove = true;
		pMotionFrame = &skin[3];
	}

	if (GetAsyncKeyState(VK_RIGHT) < 0 && topleft.X < PlayBoxRect.Right - pMotionFrame->getWidth()) {
		dx++;	
		horizon = true;
		ismove = true;
		pMotionFrame = &skin[1];

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
			pMotionFrame = &skin[0];
		}
	} 

	if (GetAsyncKeyState(VK_DOWN) < 0 && topleft.Y < PlayBoxRect.Bottom - pMotionFrame->getHeight() + 1) {
		dy++;
		horizon = false;
		ismove = true;
		pMotionFrame = &skin[2];
	}
	if (ismove )
	{
		isMoving = true;
		if (!horizon)
		{
			moveCooldown = 4;
			topleft.Y += dy * pMotionFrame->getHeight();
			dx = 0;
		}
		else
		{
			topleft.X += dx * 6;
			dy = 0;
		}
		mBox.move({ short(dx * 6), short(dy * pMotionFrame->getHeight())});
		return ismove;
	}
}
