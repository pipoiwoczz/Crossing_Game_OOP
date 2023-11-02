#ifndef _CANIMAL_H
#define _CANIMAL_H
#include "cObstacle.h"

class cAnimal: public cObstacle {
private:
	

public:
	cAnimal(COORD In_pos, int difficulty, int ttm): cObstacle(In_pos, difficulty, ttm)  {
	}

	virtual void playSound() {

	}
};

class cLion : public cAnimal {
	static vector<vector<unsigned char>> textureLion;

public:
	cLion();
	cLion(COORD In_pos, int difficulty, int ttm);
	~cLion() {

	}
	short** getHitBoxX();
};

class cRhino : public cAnimal {
	static vector<vector<unsigned char>> textureRhino;

public:
	cRhino();
	cRhino(COORD In_pos, int difficulty, int ttm);
	~cRhino() {

	}
};

class cCrocodile : public cAnimal {
	static vector<vector<unsigned char>> textureCrocodile;

public:
	cCrocodile();
	cCrocodile(COORD In_pos, int difficulty, int ttm);
	~cCrocodile() {

	}
};

//class lion : cObstacle {
//	
//};




#endif