#ifndef C_ENVIRONMENT_H
#define C_ENVIRONMENT_H
#include "cObstacle.h"

class cGameEngine;
class Texture;
class cRiver : public cObstacle {
private:

    COORD botright;
public:

    cRiver(short line, cObstacle*& safeThingAboveThis);
    unsigned char getType();
    void hitEffect(cPeople* pVictim);
    void hitSound();
};

class cLilyleaf : public cObstacle {
private:
    static vector<Texture> motionFrames;
public:
    friend bool mainLoader();


    cLilyleaf(COORD In_pos);
    unsigned char getType();

    void hitEffect(cPeople* pVictim);
    void hitSound();
};
#endif