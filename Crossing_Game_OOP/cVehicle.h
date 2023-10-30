#pragma once
#ifndef _CVEHICLE_H
#define _CVEHICLE_H
#include "setup.h"

class cVehicle {
	int mX, mY;
	public:
		cVehicle() {

		}
		~cVehicle() {

		}
		void move();
};


class cTruck : public cVehicle {
	public:
		cTruck() {

		}
		~cTruck() {

		}
		void draw(COORD pos);
};

class cHelicopter : public cVehicle {
	public:
		cHelicopter() {

		}
		~cHelicopter() {

		}
		void draw(COORD pos);
};

class cMotorbike : public cVehicle {
	public:
		cMotorbike() {

		}
		~cMotorbike() {

		}
		void draw(COORD pos);
};

#endif