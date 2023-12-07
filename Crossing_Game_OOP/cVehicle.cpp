#include "cVehicle.h"
#include "cAsset.h"
#include "hitbox.h"

cVehicle::cVehicle(COORD In_pos, int speed, bool fromRight) : cObstacle(In_pos, speed, fromRight)
{
}

cTruck::cTruck() : cTruck({ 0, 40 }, 2, true) {};
cTruck::cTruck(COORD In_pos, /*int difficulty, int ttm*/ int speed, bool fromRight) : cVehicle(In_pos, /*difficulty, ttm*/ speed, fromRight) {
	defaulttimeUntilRender = 5;

	if (fromRight)
	{
		pMotionFrame = &motionFramesL[0];
		pLMotionFrames = pMotionFrame;
		currentFrame = 0;
		numMotionFrame = motionFramesL.size();
	}
	else {
		pMotionFrame = &motionFramesR[0];
		pLMotionFrames = pMotionFrame;
		currentFrame = 0;
		numMotionFrame = motionFramesR.size();
	}
	
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


cMotorbike::cMotorbike() : cMotorbike({ 0, 40 }, 2, true) {};
cMotorbike::cMotorbike(COORD In_pos, /*int difficulty, int ttm*/ int speed, bool fromRight) : cVehicle(In_pos, /*difficulty, ttm*/ speed, fromRight) {
	defaulttimeUntilRender = 5;

	if (fromRight)
	{
		pMotionFrame = &motionFramesL[0];
		pLMotionFrames = pMotionFrame;
		currentFrame = 0;
		numMotionFrame = motionFramesL.size();
	}
	else {
		pMotionFrame = &motionFramesR[0];
		pLMotionFrames = pMotionFrame;
		currentFrame = 0;
		numMotionFrame = motionFramesR.size();
	}

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


cCar::cCar() : cCar({ 0, 40 }, 2, true) {};
cCar::cCar(COORD In_pos, /*int difficulty, int ttm*/ int speed, bool fromRight) : cVehicle(In_pos, /*difficulty, ttm*/ speed, fromRight) {
	defaulttimeUntilRender = 5;

	if (fromRight)
	{
		pMotionFrame = &motionFramesL[0];
		pLMotionFrames = pMotionFrame;
		currentFrame = 0;
		numMotionFrame = motionFramesL.size();
	}
	else {
		pMotionFrame = &motionFramesR[0];
		pLMotionFrames = pMotionFrame;
		currentFrame = 0;
		numMotionFrame = motionFramesR.size();
	}

	pFxFrame = &impactFx[0];
	pLFxFrames = pFxFrame;
	currentFxFrame = 0;
	numFxFrame = impactFx.size();

	Box.set({ short(topleft.X + 2), short(topleft.Y) }, { short(topleft.X + pMotionFrame->getWidth() - 2), short(topleft.Y + pMotionFrame->getHeight()) });
}

unsigned char cCar::getType()
{
	return 'C';
}

cCar::~cCar()
{
}

void cCar::hitEffect(cPeople* pVictim)
{
}
void cCar::hitSound()
{}