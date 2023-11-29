#include "cAnimal.h"
#include "hitbox.h"
#include "cAsset.h"




cAnimal::cAnimal(COORD In_pos, int speed) : cObstacle(In_pos, speed) {};

cLion::cLion() : cLion({ 0,20 }, 3) {}
cLion::cLion(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cAnimal(In_pos, /*difficulty, ttm*/ speed) {
    pTexture = &cLion::textureLion[0];
    pLTexture = pTexture;
    currentFrame = 0;
    nFrame = textureLion.size();
    Hitbox a({short(topleft.X + 2), short(topleft.Y)}, {short(topleft.X + pTexture->getWidth() - 2), short(topleft.Y + pTexture->getHeight())});

    boxes.push_back(a);
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
   // pTexture = &cRhino::textureRhino;
    pTexture = &cRhino::textureRhino[0];
    pLTexture = pTexture;
    currentFrame = 0;
    nFrame = textureRhino.size();
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
    pTexture = &cCrocodile::textureCroco[0];
    pLTexture = pTexture;
    currentFrame = 0;
    nFrame = textureCroco.size();
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


