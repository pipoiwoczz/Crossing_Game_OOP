#ifndef hitbox_h
#define hitbox_h

#include "setup.h"
#include <Windows.h>

class cObstacle;
class cPeople;

class Hitbox
{
private:
    COORD topleft;
    COORD botright;
    
public:
    void getHitbox (COORD &topleftGet, COORD &botrightGet);
    void move(const COORD displace);
    bool isOverlap (Hitbox h);
};

#endif /* hitbox_hpp */
