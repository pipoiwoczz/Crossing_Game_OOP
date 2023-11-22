#ifndef _CANIMAL_H
#define _CANIMAL_H
#include "cObstacle.h"

class cAnimal: public cObstacle {
private:
	

public:
	//cAnimal(COORD In_pos, int difficulty, int ttm): cObstacle(In_pos, difficulty, ttm)  {}
    cAnimal() {};

	cAnimal(COORD In_pos, int speed) : cObstacle(In_pos, speed) {
	};

	virtual void playSound() {
	}
    virtual void playHitEffect() {

    }
};

class cLion : public cAnimal {
    static cObstacle * bootstrapObjectcLion;
    static vector<Texture> hitEffectFrame;
	static vector<Texture> textureLion;

public:
	cLion();
	//cLion(COORD In_pos, int difficulty, int ttm);
    cLion (COORD In_pos, int speed);
	~cLion() {

	}
    
    virtual char getType ()
    {
        return 'l';
    }

    virtual cObstacle * copy (COORD pos)
    {
        cLion * obj = new cLion (*this);
        obj -> topleft = pos;
        return obj;
    }
    
    virtual cObstacle * construct (COORD pos, int spd)
    {
        cLion * obj = new cLion (*this);
        obj -> topleft = pos;
        obj -> speed = spd;
        return obj;
    }
    
    virtual void hitEffect() {}
};

class cRhino : public cAnimal {
    static cObstacle * bootstrapObjectcRhino;

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
    
    virtual char getType ()
    {
        return 'r';
    }
    
    virtual cObstacle * copy (COORD pos)
    {
        cRhino * obj = new cRhino (*this);
        obj -> topleft = pos;
        return obj;
    }
    virtual cObstacle * construct (COORD pos, int spd)
    {
        cRhino * obj = new cRhino (*this);
        obj -> topleft = pos;
        obj -> speed = spd;
        return obj;
    }
    
    virtual void hitEffect() {}
};

class cCrocodile : public cAnimal {
    static cObstacle * bootstrapObjectcCrocodile;

	static vector<Texture> textureCroco;


public:
	cCrocodile();
	cCrocodile(COORD In_pos, int difficulty, int ttm);
	cCrocodile(COORD In_pos, int speed);
	~cCrocodile() {

	}
    
    virtual char getType ()
    {
        return 'c';
    }
    
    virtual cObstacle * copy (COORD pos)
    {
        cCrocodile * obj = new cCrocodile (*this);
        obj -> topleft = pos;
        return obj;
    }
    virtual cObstacle * construct (COORD pos, int spd)
    {
        cCrocodile * obj = new cCrocodile (*this);
        obj -> topleft = pos;
        obj -> speed = spd;
        return obj;
    }
    
    virtual void hitEffect() {}
};



#endif
