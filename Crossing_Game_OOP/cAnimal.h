#pragma once
#include "setup.h"

class cAnimal {
	int mX, mY;
	public:
		cAnimal();
		~cAnimal();
		void move();
};

class cLion : public cAnimal {
	public:
		cLion();
		~cLion();
		void draw(COORD pos);
};

class cRhyno : public cAnimal {
	public:
		cRhyno();
		~cRhyno();
		void draw(COORD pos);
};

class cCrocodile : public cAnimal {
	public:
		cCrocodile();
		~cCrocodile();
		void draw(COORD pos);
};