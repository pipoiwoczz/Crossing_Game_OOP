#include "cAnimal.h"
#include "hitbox.h"
#include "cAsset.h"
#include "Sound.h"



cAnimal::cAnimal(COORD In_pos, int speed, bool fromRight) : cObstacle(In_pos, speed, fromRight) {};

cLion::cLion() : cLion({ 0,20 }, 3, true) {}
cLion::cLion(COORD In_pos, /*int difficulty, int ttm*/ int speed, bool fromRight) : cAnimal(In_pos, speed, fromRight) {
    defaulttimeUntilRender = 4;

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
    if (!FxPlaying)
    {
        Sound::playSoundEffect(SoundEffect::lionFx);
    }
    else {
        Sound::pauseSoundEffect(SoundEffect::lionFx);
    }
    FxPlaying = !FxPlaying;
}

cRhino::cRhino() : cRhino({ 0,20 }, 3, true) {}
cRhino::cRhino(COORD In_pos, /*int difficulty, int ttm*/ int speed, bool fromRight) : cAnimal(In_pos, /*difficulty, ttm*/ speed, fromRight) {
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
    if (!FxPlaying)
    {
        Sound::playSoundEffect(SoundEffect::rhinoFx);
    }
    else {
        Sound::pauseSoundEffect(SoundEffect::rhinoFx);
    }
    FxPlaying = !FxPlaying;
}
cCrocodile::cCrocodile() : cCrocodile({ 0,20 }, 3, true) {}
cCrocodile::cCrocodile(COORD In_pos, /*int difficulty, int ttm*/ int speed, bool fromRight) : cAnimal(In_pos, /*difficulty, ttm*/ speed, fromRight) {
    defaulttimeUntilRender = 6;

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
    if (!FxPlaying)
    {
        Sound::playSoundEffect(SoundEffect::crocoFx);
    }
    else {
        Sound::pauseSoundEffect(SoundEffect::crocoFx);
    }
    FxPlaying = !FxPlaying;
}


cShark::cShark() : cShark({ 0,20 }, 3, true) {}
cShark::cShark(COORD In_pos, /*int difficulty, int ttm*/ int speed, bool fromRight) : cAnimal(In_pos, /*difficulty, ttm*/ speed, fromRight) {
    defaulttimeUntilRender = 6;

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


cSurfer::cSurfer() : cSurfer({ 0,20 }, 3, true) {}
cSurfer::cSurfer(COORD In_pos, /*int difficulty, int ttm*/ int speed, bool fromRight) : cAnimal(In_pos, /*difficulty, ttm*/ speed, fromRight) {
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