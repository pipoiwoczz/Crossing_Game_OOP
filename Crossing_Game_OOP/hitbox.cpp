#include "hitbox.h"

bool Hitbox::isOverlap(Hitbox h)
{
    if (h.topleft.X<= botright.X && h.botright.X >= topleft.X
        && h.topleft.Y <= botright.Y && h.botright.Y >= topleft.Y)
        return true;
    else
        return false;
}

void Hitbox::getHitbox(COORD& topleftGet, COORD& botrightGet)
{
    topleftGet = topleft;
    botrightGet = botright;
}

void Hitbox::move(const int move_x, const int move_y)
{
    topleft = { short(topleft.X + move_x), short(topleft.Y + move_y) };
    botright = { short(botright.X + move_x), short(botright.Y + move_y) };
}
