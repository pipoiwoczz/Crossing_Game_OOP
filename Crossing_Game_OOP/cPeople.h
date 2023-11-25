#ifndef _CPEOPLE_H
#define _CPEOPLE_H

#include "setup.h"

class Hitbox;
class Texture;
class cPeople {
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
		cPeople();
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
