#include "hitbox.h"


Hitbox::Hitbox() : Hitbox({ 0,0 }, { 0,0 }) {}
Hitbox::Hitbox(COORD tl, COORD br)
{
    topleft = tl;
    botright = br;
}
bool Hitbox::isOverlap(Hitbox h)
{
    if (h.topleft.X <= botright.X && h.botright.X >= topleft.X
        && h.topleft.Y <= botright.Y && h.botright.Y >= topleft.Y)
        return true;
    return false;
}

void Hitbox::getHitbox(COORD &topleftGet, COORD &botrightGet)
{
    topleftGet = topleft;
    botrightGet = botright;
}

void Hitbox::set(const COORD &newTopleft, const COORD &newBotright)
{
    topleft = newTopleft;
    botright = newBotright;
}
