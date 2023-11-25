#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include "setup.h"
#include "cWidget.h"

class cGame;
class cButton;
class cDWindow;
class cLabel;
class cPeople;
class cObstacle;

class cGameEngine {
private:
	static COORD buffsize;

	//Buffer
	static CHAR_INFO* mainBuffer;
	static CHAR_INFO* reservedBuffer;
	static short h;
	static short w;


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
public:
	friend cGame;
	static HANDLE curHandle;

	static void startEngine();

	static void cleanEngine();
	
	static void swapHandle();

	static void refreshBackGround(bool fillNow = false);
	static void pizzaDraw(cGame* pGame);

	friend void cWidget::unshow();

	friend void cButton::highLight();
	friend void cButton::unHighLight();

	friend void cDWindow::unshow();

	friend void cLabel::show();
	friend void cLabel::unshow();
};

#endif
