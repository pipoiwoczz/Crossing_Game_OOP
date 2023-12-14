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
class cCoin;

class cPeople;
class cObstacle;
class cEnvironment;
class cGameEngine {
private:
	static bool startDrawThread;
	
	static COORD buffsize;
	//Buffer
	static CHAR_INFO* mainBuffer;
	static CHAR_INFO* reservedBuffer;

	//Double-buffers stuffs
	static HANDLE Hbuffer1;
	static HANDLE Hbuffer2;
	static int count;

	//Object rendering

	//Initialization Phase
	static COORD GetMonitorDimension();
	static void FixConsoleBuffer(HANDLE H);
	static void FixConsoleFont(HANDLE H);
	static void HideCursor(HANDLE H);
	static void HideScrollBar();
	static void DisableCtrButton(bool Close, bool Min, bool Max);
	static void disableUserSelection();
	static void disableCtrlHandler();

	//Widgets rendering
	static bool showWidget(cWidget* pWidget, bool instant = true);
	static bool unshowWidget(cWidget* pWidget, bool instant = true);

	static bool HighLightButton(cButton* pButton, bool instant = true);
	static bool UnHighLightButton(cButton* pButton, bool instant = true);

	static bool showLabel(cLabel* pLabel, bool instant = true);
	static bool unshowLabel(cLabel* pLabel, bool instant = true);

	static bool showBar(cBar* pBar, bool instant = true);
	static bool unshowBar(cBar* pBar, bool instant = true);

	//Pixel Processing

	//fill des buffer with non-blank pixel of src
	static void fillEffectivePixel(CHAR_INFO*& des, const COORD& desSize, CHAR_INFO*& src, const COORD& srcSize, const COORD& StartCoord);
	//fill blank pixel of des buffer with a  position-equivalent pixel in src
	static void replaceBlankPixel(CHAR_INFO*& des, const COORD& desSize, CHAR_INFO*& src, const COORD& srcSize, const COORD& StartCoord);
	//fill all pixels of a size-restricted des with their position-equilvalent pixels in src
	static void replaceAllPixel(CHAR_INFO*& des, const COORD& desSize, CHAR_INFO*& src, const COORD& srcSize, const COORD& StartCoord);
	//fill pixels of a size-restricted des with designated color
	static void paintBucket(CHAR_INFO* des, const COORD& desSize, short color);
public:
	//Friends for fast accessing
	friend cGame;
	friend cWidget;
	friend cButton;
	friend cLabel;
	friend cPeople;
	friend cBar;

	// game control

	static HANDLE curHandle;

	//For game rendering
	static bool startEngine();
	static void cleanEngine();
	
	static void swapHandle();
	static void refreshBackGround(bool fillNow = false);
	static void fillScreenWithLastFrame(bool fillNow = false);
	static void fillScreen();

	static void renderPeople(cPeople* pPeople);
	static void renderObstacle(cObstacle* pObstacle);
	static void renderEnvironment(cEnvironment* pEnvironmentObject);
	static void renderWidget(cWidget* pWidget);
	static void renderCoin(cCoin* pCoin);

	static void playEffect(cObstacle* obsta, cPeople* people);
	static void playFlashEffect(const COORD& topleft);
	//For label rendering
};

#endif
