#pragma once
#include "setup.h"

class cPeople {
	int mX, mY;
	bool mState;
	public:
		cPeople();
		~cPeople();
		void draw();
		void move(char MOVING);
		void erase();
		bool isImpact(cAnimal *animal);
		bool isImpact(cVehicle *vehicle);
		bool isDead();
		bool isFinish();
};