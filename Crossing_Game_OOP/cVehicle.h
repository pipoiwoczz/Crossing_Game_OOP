#ifndef _CVEHICLE_H
#define _CVEHICLE_H
#include "cObstacle.h"

class cVehicle: public cObstacle {
public:
	//cVehicle(COORD In_pos, int difficulty, int ttm) : cObstacle(In_pos, difficulty, ttm) {}
	cVehicle(COORD In_pos, int speed) : cObstacle(In_pos, speed) {
	
	};

	virtual void playSound() {}
};

class cTruck : public cVehicle {
    static cObstacle * bootstrapObjectcTruck;

	static vector<Texture> textureTruck;

public:
	cTruck();
	//cTruck(COORD In_pos, int difficulty, int ttm);
    cTruck (COORD In_pos, int speed);
	~cTruck() {

	}
    
    virtual char getType ()
    {
        return 'T';
    }
    
    virtual cObstacle * copy (COORD pos)
    {
        cTruck * obj = new cTruck (*this);
        obj -> topleft = pos;
        return obj;
    }
    virtual cObstacle * construct (COORD pos, int spd)
    {
        cTruck * obj = new cTruck (*this);
        obj -> topleft = pos;
        obj -> speed = spd;
        return obj;
    }
    
    virtual void hitEffect() {}
};

class cHelicopter : public cVehicle {
    static cObstacle * bootstrapObjectcHelicopter;

	static vector<Texture> textureHeli;
public:
	cHelicopter();
	//cHelicopter(COORD In_pos, int difficulty, int ttm);
    cHelicopter (COORD In_pos, int speed);
	~cHelicopter() {

	}
    
    virtual char getType ()
    {
        return 'H';
    }
    
    virtual cObstacle * copy (COORD pos)
    {
        cHelicopter * obj = new cHelicopter (*this);
        obj -> topleft = pos;
        return obj;
    }
    virtual cObstacle * construct (COORD pos, int spd)
    {
        cHelicopter * obj = new cHelicopter (*this);
        obj -> topleft = pos;
        obj -> speed = spd;
        return obj;
    }
    
    virtual void hitEffect() {}
};

class cMotorbike : public cVehicle {
    static cObstacle * bootstrapObjectcMotorbike;

	static vector<Texture> textureMotorb;

public:
	cMotorbike();
	//cMotorbike(COORD In_pos, int difficulty, int ttm);
    cMotorbike (COORD In_pos, int speed);
	~cMotorbike() {

	}
    
    virtual char getType ()
    {
        return 'M';
    }
    
    virtual cObstacle * copy (COORD pos)
    {
        cMotorbike * obj = new cMotorbike (*this);
        obj -> topleft = pos;
        return obj;
    }
    virtual cObstacle * construct (COORD pos, int spd)
    {
        cMotorbike * obj = new cMotorbike (*this);
        obj -> topleft = pos;
        return obj;
    }
    
    virtual void hitEffect() {}
};

cObstacle * cTruck::bootstrapObjectcTruck = cObstacle::addObject(new cTruck());
cObstacle * cHelicopter::bootstrapObjectcHelicopter = cObstacle::addObject(new cHelicopter());
cObstacle * cMotorbike::bootstrapObjectcMotorbike = cObstacle::addObject(new cMotorbike());

#endif
