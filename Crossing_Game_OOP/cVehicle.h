#ifndef _CVEHICLE_H
#define _CVEHICLE_H
#include "cObstacle.h"

class cGameEngine;
class Texture;
class cVehicle: public cObstacle {
public:
    cVehicle(COORD In_pos, int speed, bool fromRight);
    virtual ~cVehicle() {}
};

class cTruck : public cVehicle {
    static vector<Texture> motionFramesL;
    static vector<Texture> motionFramesR;
	static vector<Texture> impactFx;

public:
    friend bool mainLoader();


	cTruck();
    cTruck (COORD In_pos, int speed, bool fromRight);
    ~cTruck();
    
    unsigned char getType();
    virtual void hitSound();
};

class cMotorbike : public cVehicle {

    static vector<Texture> motionFramesL;
    static vector<Texture> motionFramesR;
    static vector<Texture> impactFx;
public:
    friend bool mainLoader();


	cMotorbike();
    cMotorbike (COORD In_pos, int speed, bool fromRight);
    ~cMotorbike();
 
    unsigned char getType();
    virtual void hitSound();
};

class cCar : public cVehicle {

    static vector<Texture> motionFramesL;
    static vector<Texture> motionFramesR;
    static vector<Texture> impactFx;
public:
    friend bool mainLoader();


    cCar();
    cCar(COORD In_pos, int speed, bool fromRight);
    ~cCar();

    unsigned char getType();
    virtual void hitSound();
};
#endif
