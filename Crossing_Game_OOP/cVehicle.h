#ifndef _CVEHICLE_H
#define _CVEHICLE_H
#include "cObstacle.h"

class cVehicle: public cObstacle {
public:
	//cVehicle(COORD In_pos, int difficulty, int ttm) : cObstacle(In_pos, difficulty, ttm) {}
    cVehicle (COORD In_pos, int speed) : cObstacle(In_pos, speed);

	virtual void playSound() {}
};

class cTruck : public cVehicle {
	static vector<vector<unsigned char>> textureTruck;
public:
	cTruck();
	//cTruck(COORD In_pos, int difficulty, int ttm);
    cTruck (COORD In_pos, int speed);
	~cTruck() {

	}
};

class cHelicopter : public cVehicle {
	static vector<vector<unsigned char>> textureHeli;
public:
	cHelicopter();
	//cHelicopter(COORD In_pos, int difficulty, int ttm);
    cHelicopter (COORD In_pos, int speed);
	~cHelicopter() {

	}
};

class cMotorbike : public cVehicle {
	static vector<vector<unsigned char>> textureMotorb;

public:
	cMotorbike();
	//cMotorbike(COORD In_pos, int difficulty, int ttm);
    cMotorbike (COORD In_pos, int speed);
	~cMotorbike() {

	}
};

#endif
