#ifndef _CVEHICLE_H
#define _CVEHICLE_H
#include "cObstacle.h"
class cVehicle: public cObstacle {
public:
    cVehicle(COORD In_pos, int speed);

};

class cTruck : public cVehicle {
    static cObstacle * bootstrapObjectcTruck;

	static vector<Texture> textureTruck;

public:
	cTruck();
	//cTruck(COORD In_pos, int difficulty, int ttm);
    cTruck (COORD In_pos, int speed);
    ~cTruck();
    
    virtual char getType();
    
    virtual cObstacle* copy(COORD pos);

    virtual cObstacle* construct(COORD pos, int spd);
    
    virtual void hitEffect(cPeople* pVictim);

    virtual void hitSound();
};

class cHelicopter : public cVehicle {
    static cObstacle * bootstrapObjectcHelicopter;

	static vector<Texture> textureHeli;
public:
	cHelicopter();
	//cHelicopter(COORD In_pos, int difficulty, int ttm);
    cHelicopter (COORD In_pos, int speed);
    ~cHelicopter();
    
    virtual char getType();
    
    virtual cObstacle* copy(COORD pos);

    virtual cObstacle* construct(COORD pos, int spd);
    
    virtual void hitEffect(cPeople* pVictim);

    virtual void hitSound();
};

class cMotorbike : public cVehicle {
    static cObstacle * bootstrapObjectcMotorbike;

	static vector<Texture> textureMotorb;

public:
	cMotorbike();
	//cMotorbike(COORD In_pos, int difficulty, int ttm);
    cMotorbike (COORD In_pos, int speed);
    ~cMotorbike();
    
    virtual char getType();
    
    virtual cObstacle* copy(COORD pos);

    virtual cObstacle* construct(COORD pos, int spd);
    
    virtual void hitEffect(cPeople* pVictim);

    virtual void hitSound();
};



#endif
