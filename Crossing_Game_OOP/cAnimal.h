#ifndef _CANIMAL_H
#define _CANIMAL_H
#include "cObstacle.h"

class cAnimal: public cObstacle {
public:
	cAnimal(COORD In_pos, int difficulty, int ttm): cObstacle(In_pos, difficulty, ttm)  {
	}

	virtual void playSound() {

	}
};

class cLion : public cAnimal {
public:
	cLion();
	cLion(COORD In_pos, int difficulty, int ttm);
	~cLion() {

	}
};

class cRhino : public cAnimal {
public:
	cRhino();
	cRhino(COORD In_pos, int difficulty, int ttm);
	~cRhino() {

	}
};

class cCrocodile : public cAnimal {
public:
	cCrocodile();
	cCrocodile(COORD In_pos, int difficulty, int ttm);
	~cCrocodile() {

	}
};

#endif