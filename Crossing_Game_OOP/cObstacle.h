#ifndef _COBSTACLE_H
#define _COBSTACLE_H

#include "hitbox.h"

class cPeople;
//class Hitbox;
class Texture;
class cObstacle {
private:

protected:
    COORD topleft; // coordinates of center of sprite
    int speed; // determines time interval between moves. smaller = faster
    int timeUntilMove; // time left before move is executed. if 0 or less, move, then reset this to be equal to speed
    int timeUntilRender = 0;
    bool isStop = false; // currently stopped? halts timeUntilMove and prevents move from being executed
     // list of hitboxes
    Texture* pTexture;
    Texture* pLTexture;
    short currentFrame;
    short nFrame;

    static cObstacle* addObject(cObstacle*);
public:
    static vector<cObstacle*> objects;
    vector <Hitbox> boxes;

    friend cPeople;
    friend class cGameEngine;
    friend class cGame;

    cObstacle (COORD In_pos, int speed); // constructor: set topleft and speed. timeUntilMove automatically set to be equal to speed
    ~cObstacle();
   // static void cleanBootstrap(); // clean up static objects vector. call before program exits. [better solutions?]
    
    COORD getPos();
    int getSpeed();
    
    virtual char getType() = 0; // returns the class the object belongs to as a char
    
    void setPos(COORD new_Pos);
    virtual void determineHitbox();
    
    static cObstacle * copyObject (char, COORD);
    static cObstacle * constructObject (char, COORD, int spd);
    virtual cObstacle * copy (COORD pos) = 0; // create object at pos, copying speed of original object
    virtual cObstacle * construct (COORD pos, int spd) = 0; // create object at pos, with speed set to spd
    // note: copy constructors have not been declared - currently using default copy constructors

    void move(); // moves obstacle to new position
    void moveHitBox();
    virtual void hitEffect(cPeople* pVictim) = 0;// (optional) effect on collision with player
    virtual void hitSound() = 0;
    void stop();
    void resume();

    // shared methods
    
    bool collide (Hitbox h); // (unused) check collision with other obstacles
    void advanceTime (int time); // (unused) counts down timeUntilMove and executes move if it reaches 0. does nothing while obstacle is stopped
    static void cleanBootstrap()
    {
        for (int i = 0; i < objects.size(); i++)
        {
            delete objects[i];
        }
    }
};


#endif
