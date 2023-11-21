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
    void setHitHox(short topLeftX) {
        short dis = botright.X - topleft.X;
        topleft.X = topLeftX;
        botright.X = topleft.X + dis;
    }
    void getHitbox (COORD &topleftGet, COORD &botrightGet);
    void set(const COORD& newTopleft, const COORD& newBotright);
    bool isOverlap (Hitbox h);
};

#endif /* hitbox_hpp */
