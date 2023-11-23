#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include "setup.h"
//#include "cGame.h"
//#include "cAsset.h"
//#include "Graphics.h"
//#include "Map.h"
class cGame;
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

	static void startEngine();

	static void cleanEngine();
	
	static void swapHandle();

	static void refreshBackGround(bool fillNow = false);
	static void pizzaDraw(cGame* pGame);
};

#endif
