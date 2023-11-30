#ifndef _CANIMAL_H
#define _CANIMAL_H
#include "cObstacle.h"

class Texture;
class cAnimal: public cObstacle {
private:

public:
    cAnimal(COORD In_pos, int speed);
};

class cLion : public cAnimal {
   // static cObstacle * bootstrapObjectcLion;
    static vector<Texture> hitEffectFrame;
	static vector<Texture> textureLion;
    
public:
    friend bool mainLoader();
    static vector<Texture> impactEffect;
	cLion();
    cLion (COORD In_pos, int speed);
    ~cLion();
    

    unsigned char getType();
    virtual void hitEffect(cPeople* pVictim);
    virtual void hitSound();
};

class cRhino : public cAnimal {
    //static cObstacle * bootstrapObjectcRhino;

	static vector<Texture> textureRhino;
    static vector<Texture> impactEffect;
public:
    friend bool mainLoader();


	cRhino();
	cRhino(COORD In_pos, int speed);
    ~cRhino();

    unsigned char getType();
    virtual void hitEffect(cPeople* pVictim);
    virtual void hitSound();
};

class cCrocodile : public cAnimal {
   // static cObstacle * bootstrapObjectcCrocodile;

	static vector<Texture> textureCroco;
    static vector<Texture> impactEffect;

public:
    friend bool mainLoader();


	cCrocodile();
	cCrocodile(COORD In_pos, int speed);
    ~cCrocodile();
    
    unsigned char getType();
    virtual void hitEffect(cPeople* pVictim);
    virtual void hitSound();
};



#endif
