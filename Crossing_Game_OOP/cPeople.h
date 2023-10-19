#ifndef _CPEOPLE_H
#define _CPEOPLE_H
#include "cEntity.h"

class cPeople: public cEntity {
	int mX, mY;
	bool mState; // true is alive, false is dead =))
	public:
		cPeople();
		cPeople(COORD In_pos);
		~cPeople();

		void draw(COORD pos);
		void up();
		void down();
		void left();
		void right();
		void move(char &MOVING);
		void erase() {

		}
		//bool isImpactOneLion(cLion *lion);
		//bool isImpactLion(cLion *lion);
		//bool isImpact(cVehicle *vehicle);

		bool isDead() {
			mState = false;
			return true;
		}
		bool isFinish()
		{
			return true;
		}
};

#endif