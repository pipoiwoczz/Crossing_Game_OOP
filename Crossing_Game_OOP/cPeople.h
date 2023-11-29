#ifndef _CPEOPLE_H
#define _CPEOPLE_H

#include "setup.h"
#include "hitbox.h"
class Texture;
class cPeople {
	vector<Texture> skin;
	Texture* pTexture;
	int currentFrame;
    COORD topleft;
	bool isMoving = false;
	bool mState; // true is alive, false is dead =))
	int moveCooldown;
	int step = 2;
	bool passLevel = false;

	public:
		friend class cGame;
		friend class cGameEngine;
		/*vector<Hitbox> mBoxes;*/
		Hitbox mBox;
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
