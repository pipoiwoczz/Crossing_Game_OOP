#ifndef hitbox_h
#define hitbox_h

#include "setup.h"

class Hitbox
{
private:

    
public:
    COORD topleft;  
    COORD botright;
    Hitbox();

    Hitbox(COORD tl, COORD br);
    void getHitbox (COORD &topleftGet, COORD &botrightGet);
    void set(const COORD& newTopleft, const COORD& newBotright);
    void move(const COORD& dPos);
    bool isOverlap (const Hitbox &h);
};

#endif /* hitbox_hpp */
