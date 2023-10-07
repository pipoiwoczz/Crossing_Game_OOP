#pragma once
#include "setup.h"

class cAnimal {
	int mX, mY;
	public:
		cAnimal();
		~cAnimal();
		void move();
};

class cDinosaur : public cAnimal {
	public:
		cDinosaur();
		~cDinosaur();
		void draw();
};

class cBird : public cAnimal {
	public:
		cBird();
		~cBird();
		void draw();
};

class cLion : public cAnimal {
	public:
		cLion();
		~cLion();
		void draw(COORD pos);
};