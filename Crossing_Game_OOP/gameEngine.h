#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include "cAsset.h"
#include "Map.h"
#include "cObstacle.h"
#include "cPeople.h"
#include "cGame.h"

class cGameEngine {
private:
public:
	static COORD buffsize;

	//Buffer
	static CHAR_INFO* mainBuffer;
	static short h;
	static short w;


	//handles for double-buffs tech
	static HANDLE Hbuffer1;
	static HANDLE Hbuffer2;
	static HANDLE curHandle;
	//count for double-buffs tech
	static int count;


	~cGameEngine()
	{
		delete[]mainBuffer;
		CloseHandle(Hbuffer1);
		CloseHandle(Hbuffer2);
	}

	static void startEngine();

	static void drawT(cGame* pGame);
};

#endif // !GAME_ENGINE_H
