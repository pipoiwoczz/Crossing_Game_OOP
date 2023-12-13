#ifndef _CPEOPLE_H
#define _CPEOPLE_H

#include "setup.h"
#include "hitbox.h"
class Texture;
class cPeople {
	vector<Texture> skin;


	Texture* pMotionFrame;
	int currentFrame;

	//Handle people movement when being carried by an object, Ex: standing on lilypad
	COORD carryOffset = { 0, 0 };

    COORD topleft;

	//For skill
	COORD oldPos = { 0,0 };


	long coinNow = 0;
	long coinBonus = 0;
	long totalPoint = 0;

	int isFlashing = 0;
	bool mState; // true is alive, false is dead
	int moveCooldown;
	bool passLevel = false;
	static bool isRabbit;
	bool forceStop = false;
	bool used[2] = { false, false };
	int skillCooldown[2] = { 0,0 };
	public:
		friend class cGame;
		friend class cGameEngine;
		/*vector<Hitbox> mBoxes;*/
		Hitbox mBox;
		cPeople();
		cPeople(COORD In_pos);
		~cPeople();
		void normalizingTopleft();
		COORD getPos();
		void setPos(COORD pos);
		bool getState();
        void setState(bool state);
		bool move();
		int useSkill();
		void setForceStop();
		bool isDead();
		bool isFinish();
		void moveHitBox();
		void resetCooldown();
		static void changeskin(bool isChange);
};

#endif
