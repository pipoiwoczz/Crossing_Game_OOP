#ifndef _CANIMAL_H
#define _CANIMAL_H
#include "cObstacle.h"

class cAnimal: public cObstacle {
private:

public:
    cAnimal(COORD In_pos, int speed);
};

class cLion : public cAnimal {
    static cObstacle * bootstrapObjectcLion;
    static vector<Texture> hitEffectFrame;
	static vector<Texture> textureLion;

public:
	cLion();
    cLion (COORD In_pos, int speed);
    ~cLion();
    
    virtual char getType();

    virtual cObstacle* copy(COORD pos);
    
    virtual cObstacle* construct(COORD pos, int spd);
    
    virtual void hitEffect(cPeople* pVictim);
    virtual void hitSound();
};

class cRhino : public cAnimal {
    static cObstacle * bootstrapObjectcRhino;

	static vector<Texture> textureRhino;

public:
	cRhino();
	cRhino(COORD In_pos, int speed);
    ~cRhino();

    virtual char getType();
    virtual cObstacle* copy(COORD pos);
    virtual cObstacle* construct(COORD pos, int spd);
    
    virtual void hitEffect(cPeople* pVictim);
    virtual void hitSound();
};

class cCrocodile : public cAnimal {
    static cObstacle * bootstrapObjectcCrocodile;

	static vector<Texture> textureCroco;


public:
	cCrocodile();
	cCrocodile(COORD In_pos, int speed);
    ~cCrocodile();
    virtual char getType();
    
    virtual cObstacle* copy(COORD pos);
    virtual cObstacle* construct(COORD pos, int spd);
    
    virtual void hitEffect(cPeople* pVictim);
    virtual void hitSound();
};



#endif
