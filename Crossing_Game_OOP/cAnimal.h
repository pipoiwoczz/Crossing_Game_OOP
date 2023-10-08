#pragma once
#include "setup.h"

class cAnimal {
	protected:
		int mX, mY;
		int level;
	public:
		cAnimal() {
			mX = mY = 0;
			level = 1;
		}
		~cAnimal() {

		}
		void draw(COORD pos);
		void move();
};

class cLion : public cAnimal {
	int lY, lX;
	public:
		cLion(int x, int y) {
			lX = x;
			lY = y;
		}
		~cLion() {

		}
		void draw(COORD pos);
		void move(short y);
};

class cRhyno : public cAnimal {
	int rY, rX;
	public:
		cRhyno() {
			rX = rY = 0;
		}
		~cRhyno() {

		}
		void draw(COORD pos);
		void move(short y);
};

class cCrocodile : public cAnimal {
	int cX, cY;
	public:
		cCrocodile() {
			cX = cY = 0;
		}
		~cCrocodile() {

		}
		void draw(COORD pos);
		void move(short y);
};