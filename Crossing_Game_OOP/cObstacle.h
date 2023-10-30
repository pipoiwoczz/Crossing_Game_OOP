#pragma once
#ifndef _COBSTACLE_H
#define _COBSTACLE_H

#include "position.h"
#include "hitbox.h"
#include <vector>

using namespace std;

class cObstacle
{
 
protected:
    Position center;
    int speed;
    int timeUntilMove;
    vector <Hitbox> boxes;

public:
    cObstacle() {

    }

    // abtract methods
    void draw();
    void move();
    void hitEffect();
    
    // shared methods
    bool collide (Hitbox h);
    void advanceTime (int time);
};

#endif
