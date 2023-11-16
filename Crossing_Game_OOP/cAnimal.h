#ifndef _CANIMAL_H
#define _CANIMAL_H
#include "cObstacle.h"

class cAnimal: public cObstacle {
private:
	

public:
	//cAnimal(COORD In_pos, int difficulty, int ttm): cObstacle(In_pos, difficulty, ttm)  {}
	cAnimal(COORD In_pos, int speed) : cObstacle(In_pos, speed) {
	};

	virtual void playSound() {
	}
};

class cLion : public cAnimal {
	static vector<Texture> textureLion;

public:
	cLion();
	//cLion(COORD In_pos, int difficulty, int ttm);
    cLion (COORD In_pos, int speed);
	~cLion() {

	}

};

class cRhino : public cAnimal {
	static vector<Texture> textureRhino;

public:
	cRhino();
	//cRhino(COORD In_pos, int difficulty, int ttm);
	cRhino(COORD In_pos, int speed);
	~cRhino() {

	}
	//void draw()
	//{
	//	//cObstacle::draw();
	//	//currentFrame = (currentFrame + 1) % textureRhino.size();
	//	//pTexture = &textureRhino[currentFrame];
	//}
};

class cCrocodile : public cAnimal {
	static vector<Texture> textureCroco;


public:
	cCrocodile();
	cCrocodile(COORD In_pos, int difficulty, int ttm);
	cCrocodile(COORD In_pos, int speed);
	~cCrocodile() {

	}
};
#endif
