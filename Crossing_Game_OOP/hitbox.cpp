#include "hitbox.h"

bool Hitbox::isOverlap(Hitbox h)
{
    if (h.topleft.X <= botright.X && h.botright.X >= topleft.X
        && h.topleft.Y <= botright.Y && h.botright.Y >= topleft.Y)
        return true;
    else
        return false;
}

void Hitbox::getHitbox(COORD &topleftGet, COORD &botrightGet)
{
    topleftGet = topleft;
    botrightGet = botright;
}

void Hitbox::move(COORD displace)
{
    topleft.X += displace.X;
    topleft.Y += displace.Y;
    botright.X += displace.X;
    botright.Y += displace.Y;
}
