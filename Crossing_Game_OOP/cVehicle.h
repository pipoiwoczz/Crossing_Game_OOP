#ifndef _CVEHICLE_H
#define _CVEHICLE_H
#include "cObstacle.h"

class cGameEngine;
class Texture;
class cVehicle: public cObstacle {
public:
    cVehicle(COORD In_pos, int speed);

};

class cTruck : public cVehicle {
    //static cObstacle * bootstrapObjectcTruck;
    static vector<Texture> impactEffect;
	static vector<Texture> textureTruck;

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

class cHelicopter : public cVehicle {
   // static cObstacle * bootstrapObjectcHelicopter;
    static vector<Texture> impactEffect;
	static vector<Texture> textureHeli;
public:
    friend bool mainLoader();


	cHelicopter();
	//cHelicopter(COORD In_pos, int difficulty, int ttm);
    cHelicopter (COORD In_pos, int speed);
    ~cHelicopter();
    
    unsigned char getType();
    virtual void hitEffect(cPeople* pVictim);
    virtual void hitSound();
};

class cMotorbike : public cVehicle {
    //static cObstacle * bootstrapObjectcMotorbike;

	static vector<Texture> textureMotorb;
    static vector<Texture> impactEffect;
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



#endif
