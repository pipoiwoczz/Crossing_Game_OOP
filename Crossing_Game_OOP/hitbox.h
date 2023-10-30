#ifndef hitbox_h
#define hitbox_h

#include "setup.h"
class cObstacle;
class cPeople;

class Hitbox
{
private:
    COORD topleft;
    COORD botright;

public:
    friend cObstacle;
    friend cPeople;
    void getHitbox(COORD& topleftGet, COORD& botrightGet);
    void move(const int move_x, const int move_y);
    bool isOverlap(Hitbox h);
};

#endif /* hitbox_hpp */