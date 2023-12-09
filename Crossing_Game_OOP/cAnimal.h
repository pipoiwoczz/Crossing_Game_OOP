#ifndef _CANIMAL_H
#define _CANIMAL_H
#include "cObstacle.h"

class Texture;
class cAnimal: public cObstacle {
private:

public:
    cAnimal(COORD In_pos, int speed, bool fromRight);
    virtual ~cAnimal() {}
};

class cLion : public cAnimal {
   // static cObstacle * bootstrapObjectcLion;
    static vector<Texture> motionFramesL;
    static vector<Texture> motionFramesR;
    static vector<Texture> impactFx;

public:
    friend bool mainLoader();
	cLion();
    cLion (COORD In_pos, int speed, bool fromRight);
    ~cLion();
    

    unsigned char getType();
    virtual void hitSound();
};

class cRhino : public cAnimal {
    //static cObstacle * bootstrapObjectcRhino;

    static vector<Texture> motionFramesL;
    static vector<Texture> motionFramesR;
    static vector<Texture> impactFx;
public:
    friend bool mainLoader();


	cRhino();
	cRhino(COORD In_pos, int speed, bool fromRight);
    ~cRhino();

    unsigned char getType();
    virtual void hitSound();
};

class cCrocodile : public cAnimal {
   // static cObstacle * bootstrapObjectcCrocodile;

    static vector<Texture> motionFramesL;
    static vector<Texture> motionFramesR;
    static vector<Texture> impactFx;

public:
    friend bool mainLoader();


	cCrocodile();
	cCrocodile(COORD In_pos, int speed, bool fromRight);
    ~cCrocodile();
    
    unsigned char getType();
    virtual void hitSound();
};

class cShark : public cAnimal {
    static vector<Texture> motionFramesL;
    static vector<Texture> motionFramesR;
    static vector<Texture> impactFx;

public:
    friend bool mainLoader();


    cShark();
    cShark(COORD In_pos, int speed, bool fromRight);
    ~cShark();

    unsigned char getType();
    virtual void hitSound();
};

class cSurfer : public cAnimal {
    static vector<Texture> motionFramesL;
    static vector<Texture> motionFramesR;
    static vector<Texture> impactFx;

public:
    friend bool mainLoader();


    cSurfer();
    cSurfer(COORD In_pos, int speed, bool fromRight);
    ~cSurfer();

    unsigned char getType();
    virtual void hitSound();
};

#endif
