#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "setup.h"

class Graphic {
public:
	Graphic() {
		textSize(6);
		SetConsoleTitle(L"Crossing Road");
		fixConsoleWindow();
		showScrollBar(false);
		hideCursor(GetStdHandle(STD_OUTPUT_HANDLE), true);
		DisableCtrButton(false, true, true);
		disableUserSelection();
		disableCtrlHandler();
	}
	~Graphic();
	void textSize(int);
	void setWindowSize(short width, short height);
	void DisableCtrButton(bool Close, bool Min, bool Max);
	void showScrollBar(BOOL Show);
	static void hideCursor(HANDLE h, bool isHideCursor = true);
	void fixConsoleWindow();
	void disableUserSelection();

	void disableCtrlHandler();
};


#endif // !_GRAPHICS_H
