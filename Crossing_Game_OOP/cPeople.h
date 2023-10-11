#pragma once
#ifndef _CPEOPLE_H
#define _CPEOPLE_H
#include "setup.h"

class cPeople {
	int mX, mY;
	bool mState; // true is alive, false is dead =))
	public:
		cPeople() {
			mX = mY = 50;
			mState = true;
		}
		cPeople(int x, int y) {
			mState = true;
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
		void move(char &MOVING);
		void erase();
		bool isImpactOneLion(cLion *lion);
		bool isImpactLion(cLion *lion);
		bool isImpact(cVehicle *vehicle);

		bool isDead() {
			mState = false;
			return true;
		}
		bool isFinish();
};

#endif