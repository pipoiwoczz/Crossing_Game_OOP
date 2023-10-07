#pragma once
#include "setup.h"

class cVehicle {
	int mX, mY;
	public:
		cVehicle();
		~cVehicle();
		void move();
};

class cCar : public cVehicle {
	public:
		cCar();
		~cCar();
		void draw();
};

class cTruck : public cVehicle {
	public:
		cTruck();
		~cTruck();
		void draw();
};