#pragma once
#ifndef _CANIMAL_H
#define _CANIMAL_H

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
	bool isStop = false;
	public:
		cLion() {
			lX = -20;
			lY = 40;
		}
		cLion(int x, int y) {
			lX = x;
			lY = y;
		}
		~cLion() {

		}
		void draw(COORD pos);
		void erase();
		COORD getPos() {
			return { short(lX), short(lY) };
		}
		void setPos(COORD pos) {
			lX = pos.X;
			lY = pos.Y;
		}
		short** getHitBoxX();
		short getHitBoxY() {
			return getPos().Y;
		}
		void move(COORD pos);
		void move(COORD pos, cLion* lion);
		void stop() {
			isStop = true;
		}
		void next() {
			isStop = false;
		}
};

class cRhino : public cAnimal {
	int rY, rX;
	public:
		cRhino() {
			rX = rY = 0;
		}
		~cRhino() {

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

#endif