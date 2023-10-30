#ifndef _COBSTACLE_H
#define _COBSTACLE_H

#include "setup.h"
#include "hitbox.h"

extern SMALL_RECT My_Windows;
class cObstacle {
protected:
    COORD center;
    int speed;
    int timeUntilMove;
    bool isStop = false;
    vector <Hitbox> boxes;
    vector <vector<unsigned char>> text;
    vector<wstring> texture;

public:
    cObstacle(COORD In_pos, int difficulty, int ttm);
    COORD getPos();
    void setPos(COORD new_Pos);

    // abtract methods
    void draw();
    void erase();
    void move();
    void hitEffect();
    void stop() {
        isStop = true;
    }
    void resume() {
        isStop = false;
    }

    // shared methods
    bool collide (Hitbox h);
    void advanceTime (int time);
};

#endif
