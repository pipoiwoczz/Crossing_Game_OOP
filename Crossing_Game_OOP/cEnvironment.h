#ifndef C_ENVIRONMENT_H
#define C_ENVIRONMENT_H
#include "cObstacle.h"

class cGameEngine;
class Texture;
class cObstacle;

class cEnvironment: public cObstacle {
protected:
    bool hasEvent = false;
    bool friendly = false;
    bool hasFrameMove = true;
    cEnvironment* pSafe = nullptr;

    virtual void playEvent() = 0;
    friend class cGame;
    friend cGameEngine;

    cEnvironment(COORD In_pos, int speed, bool fromRight);
};
class cRiver : public cEnvironment {
private:

    COORD botright;
public:

    cRiver(short line, cEnvironment* &safeThingAboveThis);
    unsigned char getType();
    void hitEffect(cPeople* pVictim);
    void hitSound();

    void playEvent()
    {

    }
};

class cLilyleaf : public cEnvironment {
private:
    static vector<Texture> motionFrames;
public:
    friend bool mainLoader();


    cLilyleaf(COORD In_pos, int speed, bool fromRight);
    unsigned char getType();

    void hitEffect(cPeople* pVictim);
    void hitSound();

    void playEvent()
    {

    }
};

class cTrafficLight : public cEnvironment {
private: static vector<Texture> motionFrames;
public:
    friend bool mainLoader();
    bool allowMove = false;

    cTrafficLight(COORD In_pos);
    unsigned char getType();

    void playEvent();


    void hitEffect(cPeople* pVictim);
    void hitSound();
};
#endif