#ifndef _CPEOPLE_H
#define _CPEOPLE_H
#include "setup.h"
#include "cAnimal.h"
#include "cVehicle.h"
#include <Windows.h>

class cPeople {
	//int mX, mY;
    COORD position;
	bool mState; // true is alive, false is dead =))
	vector<Hitbox> mBoxes;
	public:
		cPeople() {
			//mX = mY = 50;
            position.X = position.Y = 50;
			mState = true;
		}
		cPeople(int x, int y) {
            position.X = x;
            position.Y = y;
			mState = true;
//			mX = x;
//			mY = y;
		}
		~cPeople() {

		}

		COORD getPos() {
			return position;
		}
		void setPos(COORD pos) {
            position = pos;
		}

		void draw(COORD pos);
		void up();
		void down();
		void left();
		void right();
		void move(char &MOVING);
		void erase();
//		bool isImpactOneLion(cLion *lion);
//		bool isImpactLion(cLion *lion);
//		bool isImpact(cVehicle *vehicle);
		bool isImpact(cObstacle obsta);
		bool isDead() {
			mState = false;
			return true;
		}
		bool isFinish() {
			if (mY == 10) {
				return true;
			}
			return false;
		}
};

#endif
