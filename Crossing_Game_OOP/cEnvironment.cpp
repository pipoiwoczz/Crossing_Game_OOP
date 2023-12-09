#include "cEnvironment.h"
#include "hitbox.h"
#include "cAsset.h"


cEnvironment::cEnvironment(COORD In_pos, int speed, bool fromRight) : cObstacle(In_pos, speed, fromRight) {}

cRiver::cRiver(short line, cEnvironment*& safeThingAboveThis) : cEnvironment({ 0, line }, 0, true)
{
    movable = false;
    pSafe = safeThingAboveThis;
    pMotionFrame = nullptr;

    Box.set({ 0, line }, { PlayBoxRect.Right, short(line + 17) });
}
unsigned char cRiver::getType()
{
    return 'R';
}
void cRiver::hitEffect(cPeople* pVictim)
{

}
void cRiver::hitSound()
{

}

cLilyleaf::cLilyleaf(COORD In_pos, int speed, bool fromRight) : cEnvironment(In_pos, speed, fromRight)
{
    defaulttimeUntilRender = 4;

    friendly = true;
    pMotionFrame = &motionFrames[0];
    pLMotionFrames = pMotionFrame;
    currentFrame = 0;
    numMotionFrame = motionFrames.size();
    Box.set(topleft, { short(topleft.X + pMotionFrame->getWidth() - 1), short(topleft.Y + pMotionFrame->getHeight() - 1) });
}
unsigned char cLilyleaf::getType() {
    return 'L';
}

void cLilyleaf::hitEffect(cPeople* pVictim)
{

}
void cLilyleaf::hitSound() {

}

cTrafficLight::cTrafficLight(COORD In_pos) : cEnvironment(In_pos, 0, true)
{

    defaulttimeUntilRender = 4;

    friendly = true;
    hasEvent = true;
    hasFrameMove = false;
    movable = false;
    pMotionFrame = &motionFrames[0];
    pLMotionFrames = pMotionFrame;
    currentFrame = 0;
    numMotionFrame = motionFrames.size();
    Box.set(topleft, { short(topleft.X + pMotionFrame->getWidth() - 1), short(topleft.Y + pMotionFrame->getHeight() - 1) });
}
unsigned char cTrafficLight::getType() {
    return 'f';
}

void cTrafficLight::hitEffect(cPeople* pVictim)
{

}
void cTrafficLight::hitSound() {

}

void cTrafficLight::playEvent()
{
    if (allowMove)
    {
        pMotionFrame = &motionFrames[0];
    }
    else {
        pMotionFrame = &motionFrames[1];
    }
    allowMove = !allowMove;
}

bool cTrafficLight::getFrameMove()
{
    return allowMove;
}

void cTrafficLight::changeLight(bool isGreen)
{
    if (allowMove == isGreen) return;
    allowMove = isGreen;
    if (allowMove)
    {
		pMotionFrame = &motionFrames[0];
	}
    else {
		pMotionFrame = &motionFrames[1];
	}
}

cCoin::cCoin(COORD In_pos): cEnvironment(In_pos, 0, true) {
    defaulttimeUntilMove = 10;

    friendly = true;
    hasEvent = false;
    hasFrameMove = false;
    movable = true;
    pMotionFrame = &motionFrame;
    pLMotionFrames = pMotionFrame;
    currentFrame = 0;
    numMotionFrame = 1;
    Box.set(topleft, { short(topleft.X + pMotionFrame->getWidth() - 1), short(topleft.Y + pMotionFrame->getHeight() - 1) });
}

void cCoin::move()
{
    if (timeUntilMove > 0)
    {
        timeUntilMove--;
    }
    else {
        if (up)
        {
            topleft.Y -= 2;
            Box.move({ 0,-2 });
        }
        else {
            topleft.Y += 2;
            Box.move({ 0, 2 });
        }
        up = !up;
        timeUntilMove = defaulttimeUntilMove;
    }

}

unsigned char cCoin::getType()
{
    return '1';
}

void cCoin::hitEffect(cPeople* pVictim)
{
}

void cCoin::hitSound()
{
}
