#ifndef hitbox_hpp
#define hitbox_hpp

#include "position.hpp"

class Hitbox
{
private:
    Position topleft;
    Position botright;
    
public:
    void getHitbox (Position &topleftGet, Position &botrightGet);
    void move(const int move_x, const int move_y);
    bool isOverlap (Hitbox h);
};

#endif /* hitbox_hpp */
