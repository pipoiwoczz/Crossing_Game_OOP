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
    bool isOverlap (Hitbox h);
};

#endif /* hitbox_hpp */
