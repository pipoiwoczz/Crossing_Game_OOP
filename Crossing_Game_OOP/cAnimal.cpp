#include "cAnimal.h"
#include "cAsset.h"
#include "hitbox.h"

vector<Texture> cLion::textureLion = cAsset::assetLoaders(lionFile);
vector<Texture> cRhino::textureRhino = cAsset::assetLoaders(rhinoFile);
vector<Texture> cCrocodile::textureCroco = cAsset::assetLoaders(crocoFile);



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
cLion::~cLion()
{
    delete bootstrapObjectcLion;
}

char cLion::getType()
{
    return 'l';
}

cObstacle* cLion::copy(COORD pos)
{
    cLion* obj = new cLion(*this);
    obj->topleft = pos;
    return obj;
}

cObstacle* cLion::construct(COORD pos, int spd)
{
    cLion* obj = new cLion(*this);
    obj->topleft = pos;
    obj->speed = spd;
    return obj;
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
cRhino::~cRhino()
{
    delete bootstrapObjectcRhino;
}
char cRhino::getType()
{
    return 'r';
}

cObstacle* cRhino::copy(COORD pos)
{
    cRhino* obj = new cRhino(*this);
    obj->topleft = pos;
    return obj;
}
cObstacle* cRhino::construct(COORD pos, int spd)
{
    cRhino* obj = new cRhino(*this);
    obj->topleft = pos;
    obj->speed = spd;
    return obj;
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
cCrocodile::~cCrocodile()
{
    delete bootstrapObjectcCrocodile;
}
char cCrocodile::getType()
{
    return 'c';
}

cObstacle* cCrocodile::copy(COORD pos)
{
    cCrocodile* obj = new cCrocodile(*this);
    obj->topleft = pos;
    return obj;
}
cObstacle* cCrocodile::construct(COORD pos, int spd)
{
    cCrocodile* obj = new cCrocodile(*this);
    obj->topleft = pos;
    obj->speed = spd;
    return obj;
}

void cCrocodile::hitEffect(cPeople* pVictim)
{

}

void cCrocodile::hitSound()
{

}


