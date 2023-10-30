#ifndef _CVEHICLE_H
#define _CVEHICLE_H
#include "cObstacle.h"

class cVehicle: public cObstacle {
public:
	cVehicle(COORD In_pos, int difficulty, int ttm) : cObstacle(In_pos, difficulty, ttm) {
	}

	virtual void playSound() {

	}
};

class cTruck : public cVehicle {
public:
	cTruck();
	cTruck(COORD In_pos, int difficulty, int ttm);
	~cTruck() {

	}
};

class cHelicopter : public cVehicle {
public:
	cHelicopter();
	cHelicopter(COORD In_pos, int difficulty, int ttm);
	~cHelicopter() {

	}
};

class cMotorbike : public cVehicle {
public:
	cMotorbike();
	cMotorbike(COORD In_pos, int difficulty, int ttm);
	~cMotorbike() {

	}
};

#endif