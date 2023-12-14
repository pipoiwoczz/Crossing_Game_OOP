#include "cPeople.h"
#include "cAsset.h"
#include "gameEngine.h"

cPeople::cPeople(int skin) : cPeople({234, 145}, skin) {}
cPeople::cPeople(COORD In_pos, int skin) {
	topleft = In_pos;
	mState = true;
	moveCooldown = 0;

	if (skin == 0)
	{
		controlKey[0] = VK_UP;
		controlKey[1] = VK_RIGHT;
		controlKey[2] = VK_DOWN;
		controlKey[3] = VK_LEFT;

		skillKey[0] = 0x4F;
		skillKey[1] = 0x50;

		pLMotionFrame = &skinRabbit[0];
		numFrame = skinRabbit.size();
	}
	else {
		controlKey[0] = 0x57;
		controlKey[1] = 0x44;
		controlKey[2] = 0x53;
		controlKey[3] = 0x41;

		skillKey[0] = 0x52;
		skillKey[1] = 0x46;

		pLMotionFrame = &skinCube[0];
		numFrame = skinCube.size();
	}
	
	pMotionFrame = pLMotionFrame;
	currentFrame = 0;

	mBox.set({ short(topleft.X + 4), short(2 + topleft.Y) }, { short(pMotionFrame->getWidth() - 4 + topleft.X), short(pMotionFrame->getHeight() - 2 + topleft.Y) });
	used[0] = false;
	used[1] = false;
	skillCooldown[0] = 0;
	skillCooldown[1] = 0;
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
	mBox.set({ short(topleft.X + 4), short(2 + topleft.Y) }, { short(pMotionFrame->getWidth() - 4 + topleft.X), short(pMotionFrame->getHeight() - 2 + topleft.Y) });
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
	mBox.set({ short(topleft.X + 4), short(2 + topleft.Y) }, { short(pMotionFrame->getWidth() - 4 + topleft.X), short(pMotionFrame->getHeight() - 2 + topleft.Y) });
}

void cPeople::resetCooldown()
{
	skillCooldown[0] = 0;
	skillCooldown[1] = 0;
}

void cPeople::changeskin(SkinIndex skin)
{
	if (skin == SkinIndex::rabbit)
	{
		pLMotionFrame = &skinRabbit[0];
		numFrame = skinRabbit.size();
	}
	else {
		pLMotionFrame = &skinCube[0];
		numFrame = skinCube.size();
	}
}

int cPeople::useSkill()
{
	if (GetKeyState(skillKey[0]) & 0x8000)
	{
		return 0;
	}
	if (GetKeyState(skillKey[1]) & 0x8000)
	{
		return 1;
	}
	return -1;
}

bool cPeople::move() {
	if (forceStop || passLevel)
		return false;
	if (moveCooldown > 0)
	{
		moveCooldown--;
		return false;
	}
	bool ismove = false;
	bool horizon;
	float dx = 0, dy = 0;
	if (GetAsyncKeyState(controlKey[3]) < 0/* && topleft.X > 0*/) {
		dx--;
		horizon = true;
		ismove = true;
		currentFrame = 3;
	}

	if (GetAsyncKeyState(controlKey[1]) < 0 /*&& topleft.X < PlayBoxRect.Right - pMotionFrame->getWidth()*/) {
		dx++;	
		horizon = true;
		ismove = true;
		currentFrame = 1;

	}

	if (GetAsyncKeyState(controlKey[0]) < 0) {
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

	if (GetAsyncKeyState(controlKey[2]) < 0 /*&& topleft.Y < PlayBoxRect.Bottom - pMotionFrame->getHeight() + 1*/) {
		dy++;
		horizon = false;
		ismove = true;
		currentFrame = 2;
	}
	topleft.X += carryOffset.X;
	topleft.Y += carryOffset.Y;

	if (ismove)
	{
		pMotionFrame = pLMotionFrame + currentFrame;
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
