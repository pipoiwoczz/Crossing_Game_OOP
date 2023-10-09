#pragma once
#include "setup.h"

class cPeople {
	int mX, mY;
	bool mState;
	public:
		cPeople() {
			mX = mY = 0;
		}
		cPeople(int x, int y) {
			mX = x;
			mY = y;
		}
		~cPeople() {

		}

		COORD getPos() {
			return { short(mX), short(mY) };
		}
		void setPos(COORD pos) {
			mX = pos.X;
			mY = pos.Y;
		}

		void draw(COORD pos);
		void up();
		void down();
		void left();
		void right();
		void move(char &MOVING, cLion *lion);
		void erase();
		bool isImpactOne(cLion *lion);
		bool isImpact(cAnimal *animal);
		bool isImpact(cVehicle *vehicle);
		bool isDead();
		bool isFinish();
};