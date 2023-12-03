#include "cObstacle.h"
#include "cAsset.h"
#include "hitbox.h"



cObstacle::~cObstacle()
{
}

cObstacle::cObstacle(COORD In_pos, /* int difficulty, int ttm */ int speed) {
    topleft = In_pos;
    /*speed = difficulty;
    timeUntilMove = ttm;*/
    if (speed < 0)
        speed = 0;
    this -> speed = speed;
    timeUntilMove = speed;
}



COORD cObstacle::getPos() {
    return topleft;
}

int cObstacle::getSpeed()
{
    return speed;
}

bool cObstacle::getDirection()
{
    return isMoveLeft;
}

void cObstacle::setPos(COORD new_Pos) {
    topleft = new_Pos;
    // use if neccessary - sets new hitbox according to new position
    //determineHitbox();
}

void cObstacle::determineHitbox() // default function to determine an obstacle's hitbox, can be overridden for each subclass
{

}

bool cObstacle::collide(Hitbox h)
{
    return true;
}

void cObstacle::advanceTime(int time)
{
    if (isStop)
        return;
    
    timeUntilMove -= time;
    if (timeUntilMove <= 0)
    {
        move();
        timeUntilMove = speed;
    }
    
}

void cObstacle::move() {
    if (isStop) return;
    if (!movable) return;
    topleft.X = (topleft.X + 1) % (PlayBoxRect.Right);
    Box.move({ 1, 0 });
}

void cObstacle::moveHitBox()
{

}

void cObstacle::stop() {
    isStop = true;
}

void cObstacle::resume() {
    isStop = false;
}


