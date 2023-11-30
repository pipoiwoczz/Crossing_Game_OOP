#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include "setup.h"
#include "cWidget.h"

class cGame;



class cWidget;
class cButton;
class cDWindow;
class cLabel;
class cBar;

class cPeople;
class cObstacle;

class cGameEngine {
private:
	static COORD buffsize;
	//Buffer
	static CHAR_INFO* mainBuffer;
	static CHAR_INFO* reservedBuffer;

	//handles for double-buffs tech
	static HANDLE Hbuffer1;
	static HANDLE Hbuffer2;
	
	//count for double-buffs tech
	static int count;
	static void renderPeople(cPeople* pPeople);
	static void renderObstacle(cObstacle* pObstacle);
	
	static COORD GetMonitorDimension();
	static void FixConsoleBuffer(HANDLE H);
	static void FixConsoleFont(HANDLE H);
	static void HideCursor(HANDLE H);
	static void HideScrollBar();
	static void DisableCtrButton(bool Close, bool Min, bool Max);
	static void disableUserSelection();
	static void disableCtrlHandler();

	static bool showWidget(cWidget* pWidget, bool instant = true);
	static bool unshowWidget(cWidget* pWidget, bool instant = true);

	static bool HighLightButton(cButton* pButton, bool instant = true);
	static bool UnHighLightButton(cButton* pButton, bool instant = true);

	static bool showLabel(cLabel* pLabel, bool instant = true);
	static bool unshowLabel(cLabel* pLabel, bool instant = true);

	static bool showBar(cBar* pBar, bool instant = true);
	static bool unshowBar(cBar* pBar, bool instant = true);

	//Processing type

	//fill des buffer with non-blank pixel of src
	static void fillEffectivePixel(CHAR_INFO*& des, const COORD& desSize, CHAR_INFO*& src, const COORD& srcSize, const COORD& StartCoord);
	//fill blank pixel of des buffer with a  position-equivalent pixel in src
	static void replaceBlankPixel(CHAR_INFO*& des, const COORD& desSize, CHAR_INFO*& src, const COORD& srcSize, const COORD& StartCoord);
	//fill all pixels of a size-restricted des with their position-equilvalent pixels in src
	static void replaceAllPixel(CHAR_INFO*& des, const COORD& desSize, CHAR_INFO*& src, const COORD& srcSize, const COORD& StartCoord);
	//fill pixels of a size-restricted des with designated color
	static void paintBucket(CHAR_INFO* des, const COORD& desSize, short color);
public:
	
	friend cGame;
	friend cWidget;
	friend cButton;
	friend cLabel;
	friend cPeople;
	friend cBar;

	static HANDLE curHandle;

	//For game rendering
	static bool startEngine();

	static void cleanEngine();
	
	static void swapHandle();

	static void refreshBackGround(bool fillNow = false);

	static void maindraw(cGame* pGame);
	static void updateInfo(cGame* pGame);
	static void pizzaDraw(cGame* pGame);
	static void playEffect(cObstacle* obsta, cPeople* people);
	//For label rendering
};

#endif
