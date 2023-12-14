#ifndef _COBSTACLE_H
#define _COBSTACLE_H

#include "hitbox.h"

class cPeople;
class Texture;
class cObstacle {
private:

protected:
    COORD topleft; // coordinates of center of sprite
    int speed; // determines time interval between moves. smaller = faster
    int timeUntilMove = 0; // time left before move is executed. if 0 or less, move, then reset this to be equal to speed
    int defaulttimeUntilMove;

    int timeUntilRender = 0;
    int defaulttimeUntilRender;
    
    bool isStop = false; // currently stopped? halts timeUntilMove and prevents move from being executed
     // list of hitboxes
    Texture* pMotionFrame;
    Texture* pLMotionFrames;
    short currentFrame;
    short numMotionFrame;

    
    Texture* pFxFrame;
    Texture* pLFxFrames;
    short currentFxFrame;
    short numFxFrame;

    bool movable = true;
    bool fromRight;
    bool FxPlaying = false;
public:
    Hitbox Box;

    friend cPeople;
    friend class cGameEngine;
    friend class cGame;

    cObstacle (COORD In_pos, int speed, bool fromRight); // constructor: set topleft and speed. timeUntilMove automatically set to be equal to speed
    virtual ~cObstacle();
    
    COORD getPos();
    int getSpeed();
    bool getDirection();
    
    void setPos(COORD new_Pos);
    virtual void determineHitbox();

    virtual void move(); // moves obstacle to new position
    void moveHitBox();

    virtual unsigned char getType() = 0;
    virtual void hitEffect(cPeople* pVictim);// (optional) effect on collision with player
    virtual void hitSound() = 0;
    void stop(); //stop object (object will not move)
    void resume(); //un-stop object

    // shared methods
    
};

#endif
