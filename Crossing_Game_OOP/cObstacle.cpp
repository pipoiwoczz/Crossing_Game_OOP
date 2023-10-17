#include "cObstacle.h"

bool cObstacle::collide(Hitbox h)
{
    for (Hitbox check : boxes)
        if (h.isOverlap(check))
            return true;
    return false;
}
