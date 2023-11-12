#ifndef _CPEOPLE_H
#define _CPEOPLE_H
#include "setup.h"
#include "cAnimal.h"
#include "cVehicle.h"
#include "Map.h"
#include <Windows.h>

class cPeople {
	//int mX, mY;
	CHAR_INFO *character;
	short height, width;
	HANDLE h;
    COORD position;
	bool mState; // true is alive, false is dead =))
	vector<Hitbox> mBoxes;


	public:
		cPeople() {
			character = loader("c.txt", height, width);
			h = GetStdHandle(STD_OUTPUT_HANDLE);
			position = { 200,100 };
			mState = true;
		}
		cPeople(COORD In_pos) {
			character = loader("c.txt", height, width);
			h = GetStdHandle(STD_OUTPUT_HANDLE);
			position = In_pos;
			mState = true;
		}
		~cPeople() {
			delete[] character;

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
		void move(Map &map);
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
			//if (mY == 10) {
			//	return true;
			//}
			//return false;
		}
};

#endif
