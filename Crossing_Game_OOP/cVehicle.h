#ifndef _CVEHICLE_H
#define _CVEHICLE_H
#include "cEntity.h"
class cVehicle: public cEntity {
protected:
	int level;
public:
	cVehicle(COORD In_pos, int difficult, VehicleIndex Vindex);
	~cVehicle();

	virtual void move(bool toRight = true)
	{

	}
};


class cTruck : public cVehicle {
public:
	cTruck();
	cTruck(COORD In_pos, int difficult);
	~cTruck();

	void move(bool toRight);
	short** getHitBoxX();
};

class cHelicopter : public cVehicle {
public:
	cHelicopter();
	cHelicopter(COORD In_pos, int difficult);
	~cHelicopter();

	void move(bool toRight = true);
	short** getHitBoxX();
};

class cMotorbike : public cVehicle {
public:
	cMotorbike();
	cMotorbike(COORD In_pos, int difficult);
	~cMotorbike();

	void move(bool toRight = true);
	short** getHitBoxX();
};

#endif