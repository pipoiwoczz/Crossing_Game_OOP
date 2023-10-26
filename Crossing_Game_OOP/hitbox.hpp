#ifndef hitbox_hpp
#define hitbox_hpp


//#include "position.hpp"
#include <Windows.h>


class Hitbox
{
private:
    COORD topleft;
    COORD botright;
    
public:
    void getHitbox (COORD &topleftGet, COORD &botrightGet);
    void move(const int move_x, const int move_y);
    bool isOverlap (Hitbox h);
};

#endif /* hitbox_hpp */
