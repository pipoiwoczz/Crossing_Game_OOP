#include "hitbox.hpp"

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

void Hitbox::move(const COORD displace)
{
//    topleft.setCoordinates(topleft.getX() + move_x, topleft.getY() + move_y);
//    botright.setCoordinates(botright.getX() + move_x, botright.getY() + move_y);
    topleft.X += displace.X;
    topleft.Y += displace.Y;
    botright.X += displace.X;
    botright.Y += displace.Y;
}
