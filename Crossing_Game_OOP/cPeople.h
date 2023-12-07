#ifndef _CPEOPLE_H
#define _CPEOPLE_H

#include "setup.h"
#include "hitbox.h"
class Texture;
class cPeople {
	vector<Texture> skin;


	Texture* pMotionFrame;
	int currentFrame;


    COORD topleft;
	bool isMoving = false;
	bool mState; // true is alive, false is dead
	int moveCooldown;
	bool passLevel = false;
	static bool isRabbit;

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
        void setState(bool state);
		bool move();

		bool isDead();
		bool isFinish();

		static void changeskin(bool isChange);
};

#endif
