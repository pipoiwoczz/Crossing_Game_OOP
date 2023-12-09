#include "cObstacle.h"
#include "cAsset.h"
#include "hitbox.h"
#include "gameEngine.h"


cObstacle::~cObstacle()
{
}

cObstacle::cObstacle(COORD In_pos, int speed, bool fromRight) {
    topleft = In_pos;
    /*speed = difficulty;
    timeUntilMove = ttm;*/
    if (speed < 0)
        speed = 0;
    this -> speed = speed;
    timeUntilMove = speed;
    this->fromRight = fromRight;
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
    return fromRight;
}

void cObstacle::setPos(COORD new_Pos) {
    topleft = new_Pos;
    // use if neccessary - sets new hitbox according to new position
    //determineHitbox();
}

void cObstacle::determineHitbox() // default function to determine an obstacle's hitbox, can be overridden for each subclass
{

}


void cObstacle::move() {
    if (isStop)
        return;
    if (!movable) return;
    if (fromRight) {
        topleft.X = (topleft.X - speed + PlayBoxRect.Right) % (PlayBoxRect.Right);
        Box.move({ short(-speed), 0 });
    }
	else {
        topleft.X = (topleft.X + speed) % (PlayBoxRect.Right);
        Box.move({ short(speed), 0 });
    }
}

void cObstacle::hitEffect(cPeople* victim)
{
    cGameEngine::playEffect(this, victim);
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


