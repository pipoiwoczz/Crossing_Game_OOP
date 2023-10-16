#include "hitbox.hpp"

bool Hitbox::isOverlap(Hitbox h)
{
    if (h.topleft.getX() <= botright.getX() && h.botright.getX() >= topleft.getX()
        && h.topleft.getY() <= botright.getY() && h.botright.getY() >= topleft.getY())
        return true;
    else
        return false;
}

void Hitbox::getHitbox(Position &topleftGet, Position &botrightGet)
{
    topleftGet = topleft;
    botrightGet = botright;
}

void Hitbox::move(const int move_x, const int move_y)
{
    topleft.setCoordinates(topleft.getX() + move_x, topleft.getY() + move_y);
    botright.setCoordinates(botright.getX() + move_x, botright.getY() + move_y);
}
