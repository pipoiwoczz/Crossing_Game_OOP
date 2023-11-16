#ifndef hitbox_h
#define hitbox_h

#include "setup.h"
#include <Windows.h>

class cObstacle;
class cPeople;

class Hitbox
{
private:

    
public:
    COORD topleft;
    COORD botright;
    Hitbox() {}

    Hitbox(COORD tl, COORD br)
    {
        topleft = tl;
        botright = br;
    }
    void getHitbox (COORD &topleftGet, COORD &botrightGet);
    void move(COORD displace);
    bool isOverlap (Hitbox h);
};

#endif /* hitbox_hpp */
