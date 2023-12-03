#include "cAnimal.h"
#include "hitbox.h"
#include "cAsset.h"




cAnimal::cAnimal(COORD In_pos, int speed) : cObstacle(In_pos, speed) {};

cLion::cLion() : cLion({ 0,20 }, 3) {}
cLion::cLion(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cAnimal(In_pos, /*difficulty, ttm*/ speed) {
    defaulttimeUntilRender = 4;

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

unsigned char cLion::getType()
{
    return 'l';
}

cLion::~cLion()
{
}

void cLion::hitEffect(cPeople* pVictim)
{

}

void cLion::hitSound()
{

}

cRhino::cRhino() : cRhino({ 0,20 }, 3) {}
cRhino::cRhino(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cAnimal(In_pos, /*difficulty, ttm*/ speed) {
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

unsigned char cRhino::getType()
{
    return 'r';
}

cRhino::~cRhino()
{
}

void cRhino::hitEffect(cPeople* pVictim)
{

}

void cRhino::hitSound()
{

}
cCrocodile::cCrocodile() : cCrocodile({ 0,20 }, 3) {}
cCrocodile::cCrocodile(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cAnimal(In_pos, /*difficulty, ttm*/ speed) {
    defaulttimeUntilRender = 6;

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

unsigned char cCrocodile::getType()
{
    return 'c';
}

cCrocodile::~cCrocodile()
{
}

void cCrocodile::hitEffect(cPeople* pVictim)
{

}

void cCrocodile::hitSound()
{

}


cShark::cShark() : cShark({ 0,20 }, 3) {}
cShark::cShark(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cAnimal(In_pos, /*difficulty, ttm*/ speed) {
    defaulttimeUntilRender = 6;

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

unsigned char cShark::getType()
{
    return 's';
}

cShark::~cShark()
{
}

void cShark::hitEffect(cPeople* pVictim)
{

}

void cShark::hitSound()
{

}


cSurfer::cSurfer() : cSurfer({ 0,20 }, 3) {}
cSurfer::cSurfer(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cAnimal(In_pos, /*difficulty, ttm*/ speed) {
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

unsigned char cSurfer::getType()
{
    return 'S';
}

cSurfer::~cSurfer()
{
}

void cSurfer::hitEffect(cPeople* pVictim)
{

}

void cSurfer::hitSound()
{

}