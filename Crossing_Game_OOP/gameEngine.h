#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include "cAsset.h"
#include "Map.h"
#include "cObstacle.h"
#include "cPeople.h"
#include "cGame.h"

class cGameEngine {
private:
	static COORD buffsize;

	//Buffer
	static CHAR_INFO* mainBuffer;
	static short h;
	static short w;


	//handles for double-buffs tech
	static HANDLE Hbuffer1;
	static HANDLE Hbuffer2;
	//count for double-buffs tech
	static int count;
public:
	static HANDLE curHandle;

	~cGameEngine()
	{
		delete[]mainBuffer;
		CloseHandle(Hbuffer1);
		CloseHandle(Hbuffer2);
	}

	static void startEngine();

	static void drawT(cGame* pGame);
	static void drawHitEffect(const cObstacle* &pObstacle);
};

#endif // !GAME_ENGINE_H
