#ifndef _CANIMAL_H
#define _CANIMAL_H

#include "cEntity.h"

class cAnimal : public cEntity {
protected:
	int level;
public:
	cAnimal(COORD In_pos, int difficult, AnimalIndex Aindex);
	~cAnimal();
	virtual void move(bool toRight = true)
	{

	}

};

class cLion : public cAnimal {
public:
	cLion();
	cLion(COORD In_pos, int difficult);
	~cLion();

	void move(bool toRight = true);
	short** getHitBoxX();
};
class cRhino : public cAnimal {
public:
	cRhino();
	cRhino(COORD In_pos, int difficult);
	~cRhino();

	void move(bool toRight = true);
	short** getHitBoxX();
};
/*
class cDinosaur : public cAnimal {
public:
	cDinosaur(COORD In_pos, int difficult);
	void move(bool toRight) override;
	short** getHitBoxX() override;
};
class cDog : public cAnimal {
public:
	cDog(COORD In_pos, int difficult);
	void move(bool toRight) override;
	short** getHitBoxX() override;
};*/
class cCrocodile : public cAnimal {
public:
	cCrocodile();
	cCrocodile(COORD In_pos, int difficult);
	~cCrocodile();

	void move(bool toRight = true);
	short** getHitBoxX();
};

#endif