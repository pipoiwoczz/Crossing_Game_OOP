#ifndef _CPEOPLE_H
#define _CPEOPLE_H

#include "setup.h"
//#include "hitbox.h"
//#include "cAsset.h"

class Hitbox;
class Texture;
class cPeople {
	//int mX, mY;


	vector<Texture> skin;
	Texture* pTexture;
	int currentFrame;
    COORD topleft;
	bool mState; // true is alive, false is dead =))
	int moveCooldown;

	public:
		friend class cGameEngine;
		/*vector<Hitbox> mBoxes;*/
		vector<Hitbox> mBoxes;
		cPeople() : cPeople({ 200, 100 }) {}
		cPeople(COORD In_pos);
		~cPeople();

		COORD getPos();
		void setPos(COORD pos);
		bool getState();
        
		bool move();

		bool isDead();
		bool isFinish();
};

#endif
