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

void cPeople::normalizingTopleft()
{
	if (topleft.X > PlayBoxRect.Right - pMotionFrame->getWidth() + 1)
	{
		topleft.X = PlayBoxRect.Right - pMotionFrame->getWidth() + 1;
	}
	else if (topleft.X < 0)
		topleft.X = 0;

	if (topleft.Y < 1)
		topleft.Y = 1;
	else if (topleft.Y > PlayBoxRect.Bottom - pMotionFrame->getHeight() + 1)
	{
		topleft.Y = PlayBoxRect.Bottom - pMotionFrame->getHeight() + 1;
	}
};

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

void cPeople::setForceStop()
{
	forceStop = !forceStop;
}

bool cPeople::isDead() {
	mState = false;
	return true; // why?
}
bool cPeople::isFinish() {
	return true;
}

void cPeople::moveHitBox()
{
	mBox.set({ short(topleft.X + 4), short(2 + topleft.Y) }, { short(skin[0].getWidth() - 4 + topleft.X), short(skin[0].getHeight() - 2 + topleft.Y) });
}

void cPeople::resetCooldown()
{
	skillCooldown[0] = 0;
	skillCooldown[1] = 0;
}

int cPeople::getCooldown(int skill)
{
	return skillCooldown[skill];
}

void cPeople::setCooldown(int skill, int value)
{
	if (skill < 0 || skill > 1)
		return;
	skillCooldown[skill] = value;
}

void cPeople::changeskin(bool isChange)
{
	isRabbit = (isChange);
}

int cPeople::useSkill()
{
	if (!used[0] && (GetKeyState(0x31) & 0x8000))
	{
		setCooldown(0, 6000);
		used[0] = true;
		skill[0] = true;
		return 0;
	}
	if (!used[1] && (GetKeyState(0x32) & 0x8000))
	{
		setCooldown(1, 6000);
		used[1] = true;
		skill[1] = true;
		return 1;
	}
	return -1;
}

void cPeople::teleport()
{
	if (currentFrame == 0)
	{
		topleft.Y -= 36;
	}
	else if (currentFrame == 1)
	{
		topleft.X += 48;
	}
	else if (currentFrame == 2)
	{
		topleft.Y += 36;
	}
	else {
		topleft.X -= 48;
	}
}
bool cPeople::move() {
	if (forceStop)
		return false;
	if (moveCooldown > 0)
	{
		moveCooldown--;
		return false;
	}
	bool ismove = false;
	bool horizon;
	float dx = 0, dy = 0;
	if (GetAsyncKeyState(VK_LEFT) < 0/* && topleft.X > 0*/) {
		dx--;
		horizon = true;
		ismove = true;
		currentFrame = 3;
	}

	if (GetAsyncKeyState(VK_RIGHT) < 0 /*&& topleft.X < PlayBoxRect.Right - pMotionFrame->getWidth()*/) {
		dx++;	
		horizon = true;
		ismove = true;
		currentFrame = 1;

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
			currentFrame = 0;
		}
	} 

	if (GetAsyncKeyState(VK_DOWN) < 0 /*&& topleft.Y < PlayBoxRect.Bottom - pMotionFrame->getHeight() + 1*/) {
		dy++;
		horizon = false;
		ismove = true;
		currentFrame = 2;
	}
	topleft.X += carryOffset.X;
	topleft.Y += carryOffset.Y;

	if (ismove)
	{
		pMotionFrame = &skin[currentFrame];
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
	}
	carryOffset = { 0,0 };
	normalizingTopleft();
	return ismove;
}
