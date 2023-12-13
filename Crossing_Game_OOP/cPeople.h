#ifndef _CPEOPLE_H
#define _CPEOPLE_H

#include "setup.h"
#include "hitbox.h"
class Texture;
class cButton;

enum class SkinIndex {
	rabbit = 0,
	cube = 1
};

class cPeople {
	static vector<Texture> skinRabbit;
	static vector<Texture> skinCube;

	Texture* pLMotionFrame;
	Texture* pMotionFrame;
	int numFrame;
	int currentFrame;

	//Handle people movement when being carried by an object, Ex: standing on lilypad
	COORD carryOffset = { 0, 0 };

    COORD topleft;

	//For skill
	COORD oldPos = { 0,0 };

	int controlKey[4];
	int skillKey[2];

	int isFlashing = 0;
	bool mState; // true is alive, false is dead
	int moveCooldown;
	bool passLevel = false;
	bool forceStop = false;
	bool used[2] = { false, false };
	int skillCooldown[2] = { 0,0 };
	public:
		friend class cGame;
		friend class cGameEngine;
		friend bool mainLoader();
		Hitbox mBox;
		cPeople(int skin);
		cPeople(COORD In_pos, int skin);
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
		void changeskin(SkinIndex skin);
};

#endif
