#ifndef _CVEHICLE_H
#define _CVEHICLE_H
#include "cObstacle.h"

class cGameEngine;
class Texture;
class cVehicle: public cObstacle {
public:
    cVehicle(COORD In_pos, int speed);
    virtual ~cVehicle() {}
};

class cTruck : public cVehicle {
    //static cObstacle * bootstrapObjectcTruck;
    static vector<Texture> motionFrames;
	static vector<Texture> impactFx;

public:
    friend bool mainLoader();


	cTruck();
	//cTruck(COORD In_pos, int difficulty, int ttm);
    cTruck (COORD In_pos, int speed);
    ~cTruck();
    
    unsigned char getType();
    virtual void hitEffect(cPeople* pVictim);
    virtual void hitSound();
};

class cMotorbike : public cVehicle {
    //static cObstacle * bootstrapObjectcMotorbike;

	static vector<Texture> motionFrames;
    static vector<Texture> impactFx;
public:
    friend bool mainLoader();


	cMotorbike();
	//cMotorbike(COORD In_pos, int difficulty, int ttm);
    cMotorbike (COORD In_pos, int speed);
    ~cMotorbike();
 
    unsigned char getType();
    virtual void hitEffect(cPeople* pVictim);
    virtual void hitSound();
};

class cCar : public cVehicle {
    //static cObstacle * bootstrapObjectcMotorbike;

    static vector<Texture> motionFrames;
    static vector<Texture> impactFx;
public:
    friend bool mainLoader();


    cCar();
    //cCar(COORD In_pos, int difficulty, int ttm);
    cCar(COORD In_pos, int speed);
    ~cCar();

    unsigned char getType();
    virtual void hitEffect(cPeople* pVictim);
    virtual void hitSound();
};
#endif
