#include "cEnvironment.h"
#include "hitbox.h"
#include "cAsset.h"

cRiver::cRiver(short line, cObstacle*& safeThingAboveThis) : cObstacle({ 0, line }, 0)
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

cLilyleaf::cLilyleaf(COORD In_pos) : cObstacle(In_pos, 0)
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
