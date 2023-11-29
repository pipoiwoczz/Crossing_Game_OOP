#include "cEnvironment.h"
#include "hitbox.h"
#include "cAsset.h"

cRiver::cRiver(short line, cObstacle*& safeThingAboveThis) : cObstacle({ 0, line }, 0)
{
    movable = false;
    pSafe = safeThingAboveThis;
    pTexture = nullptr;
    boxes.push_back(Hitbox({ 0, line }, { PlayBoxRect.Right, short(line + 17) }));
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
    pTexture = &cLilyleaf::textureLily[0];
    pLTexture = pTexture;
    currentFrame = 0;
    nFrame = textureLily.size();
    boxes.push_back(Hitbox(topleft, { short(topleft.X + pTexture->getWidth() - 1), short(topleft.Y + pTexture->getHeight() - 1) }));
}
unsigned char cLilyleaf::getType() {
    return '\0';
}

void cLilyleaf::hitEffect(cPeople* pVictim)
{

}
void cLilyleaf::hitSound() {

}
