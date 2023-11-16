#ifndef _COBSTACLE_H
#define _COBSTACLE_H

#include "setup.h"
#include "hitbox.h"
#include "cAsset.h"
class cPeople;
class cObstacle {
protected:
    COORD topleft; // coordinates of center of sprite
    int speed; // determines time interval between moves. smaller = faster
    int timeUntilMove; // time left before move is executed. if 0 or less, move, then reset this to be equal to speed
    bool isStop = false; // currently stopped? halts timeUntilMove and prevents move from being executed
     // list of hitboxes
    Texture* pTexture;
    Texture* pLTexture;
    short currentFrame;
    short nFrame;

public:
    vector <Hitbox> boxes;
    friend cPeople;
    //cObstacle(COORD In_pos, int difficulty, int ttm);
    cObstacle (COORD In_pos, int speed); // constructor: set center and speed. timeUntilMove automatically set to be equal to speed
    COORD getPos();
    int getSpeed();
    
    void setPos(COORD new_Pos);

    void draw(); // draws sprite based on texture
    void erase(); // deletes sprite on screen
    void move(); // moves obstacle to new position
    virtual void hitEffect() {
    
    }; // (optional) effect on collision with player
    void stop() {
        isStop = true;
    }
    void resume() {
        isStop = false;
    }

    // shared methods
    
    bool collide (Hitbox h); // (unused) check collision with other obstacles
    void advanceTime (int time); // counts down timeUntilMove and executes move if it reaches 0. does nothing while obstacle is stopped
};

#endif
