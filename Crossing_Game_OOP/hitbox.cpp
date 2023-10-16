#include "hitbox.hpp"

bool Hitbox::isOverlap(Hitbox h)
{
    if (h.topleft.getX() <= botright.getX() && h.botright.getX() >= topleft.getX()
        && h.topleft.getY() <= botright.getY() && h.botright.getY() >= topleft.getY())
        return true;
    else
        return false;
}
