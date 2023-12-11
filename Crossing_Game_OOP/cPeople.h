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
	int isFlashing = 0;
	bool mState; // true is alive, false is dead
	int moveCooldown;
	bool passLevel = false;
	static bool isRabbit;
	bool forceStop = false;
	bool skill[2] = { false, false };
	bool used[2] = { false, false };
	int skillCooldown[2] = { 30, 30 };

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
		void teleport();
		void setForceStop();
		bool isDead();
		bool isFinish();
		void moveHitBox();
		void resetCooldown();
		int getCooldown(int skill);
		void setCooldown(int skill, int value);
		static void changeskin(bool isChange);
};

#endif
