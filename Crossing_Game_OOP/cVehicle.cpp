#include "cVehicle.h"
#include "cAsset.h"
#include "hitbox.h"

cVehicle::cVehicle(COORD In_pos, int speed) : cObstacle(In_pos, speed)
{
}

cTruck::cTruck() : cTruck({ 0, 40 }, 2) {};
cTruck::cTruck(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cVehicle(In_pos, /*difficulty, ttm*/ speed) {
	defaulttimeUntilRender = 5;

	pMotionFrame = &motionFrames[0];
	pLMotionFrames = pMotionFrame;
	currentFrame = 0;
	numMotionFrame = motionFrames.size();

	pFxFrame = &impactFx[0];
	pLFxFrames = pFxFrame;
	currentFxFrame = 0;
	numFxFrame = impactFx.size();

	Box.set({ short(topleft.X + 2), short(topleft.Y) }, { short(topleft.X + pMotionFrame->getWidth() - 2), short(topleft.Y + pMotionFrame->getHeight()) });
}

unsigned char cTruck::getType()
{
	return 'T';
}

cTruck::~cTruck()
{
}

void cTruck::hitEffect(cPeople* pVictim) {}
void cTruck::hitSound() {}

cHelicopter::cHelicopter() : cHelicopter({ 0, 40 }, 2) {};
cHelicopter::cHelicopter(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cVehicle(In_pos, /*difficulty, ttm*/ speed) {
	defaulttimeUntilRender = 5;

	pMotionFrame = &motionFrames[0];
	pLMotionFrames = pMotionFrame;
	currentFrame = 0;
	numMotionFrame = motionFrames.size();

	pFxFrame = &impactFx[0];
	pLFxFrames = pFxFrame;
	currentFxFrame = 0;
	numFxFrame = impactFx.size();

	Box.set({ short(topleft.X + 2), short(topleft.Y) }, { short(topleft.X + pMotionFrame->getWidth() - 2), short(topleft.Y + pMotionFrame->getHeight()) });
}

unsigned char cHelicopter::getType()
{
	return 'H';
}

cHelicopter::~cHelicopter()
{
}

void cHelicopter::hitEffect(cPeople* pVictim)
{
}
void cHelicopter::hitSound()
{
}
cMotorbike::cMotorbike() : cMotorbike({ 0, 40 }, 2) {};
cMotorbike::cMotorbike(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cVehicle(In_pos, /*difficulty, ttm*/ speed) {
	defaulttimeUntilRender = 5;

	pMotionFrame = &motionFrames[0];
	pLMotionFrames = pMotionFrame;
	currentFrame = 0;
	numMotionFrame = motionFrames.size();

	pFxFrame = &impactFx[0];
	pLFxFrames = pFxFrame;
	currentFxFrame = 0;
	numFxFrame = impactFx.size();

	Box.set({ short(topleft.X + 2), short(topleft.Y) }, { short(topleft.X + pMotionFrame->getWidth() - 2), short(topleft.Y + pMotionFrame->getHeight()) });
}

unsigned char cMotorbike::getType()
{
	return 'M';
}

cMotorbike::~cMotorbike()
{
}

void cMotorbike::hitEffect(cPeople* pVictim)
{
}
void cMotorbike::hitSound()
{}

