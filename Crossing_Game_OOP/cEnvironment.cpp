#include "cEnvironment.h"
#include "hitbox.h"
#include "cAsset.h"


cEnvironment::cEnvironment(COORD In_pos, int speed) : cObstacle(In_pos, speed) {}

cRiver::cRiver(short line, cEnvironment*& safeThingAboveThis) : cEnvironment({ 0, line }, 0)
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

cLilyleaf::cLilyleaf(COORD In_pos) : cEnvironment(In_pos, 0)
{
    friendly = true;

    pMotionFrame = &motionFrames[0];
    pLMotionFrames = pMotionFrame;
    currentFrame = 0;
    numMotionFrame = motionFrames.size();
    Box.set(topleft, { short(topleft.X + pMotionFrame->getWidth() - 1), short(topleft.Y + pMotionFrame->getHeight() - 1) });
}
unsigned char cLilyleaf::getType() {
    return '\0';
}

void cLilyleaf::hitEffect(cPeople* pVictim)
{

}
void cLilyleaf::hitSound() {

}

cTrafficLight::cTrafficLight(COORD In_pos) : cEnvironment(In_pos, 0)
{
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
        pMotionFrame = &motionFrames[1];
        Sleep(500);
        pMotionFrame = &motionFrames[2];
    }
    else {
        pMotionFrame = &motionFrames[1];
        Sleep(500);
        pMotionFrame = &motionFrames[0];
    }
    allowMove = !allowMove;
}