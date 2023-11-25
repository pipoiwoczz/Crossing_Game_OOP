#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "setup.h"

class Graphic {
public:
	Graphic() {
		textSize(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		SetConsoleTitle(L"Crossing Road");
		fixConsoleWindow();
		showScrollBar(false);
		hideCursor(GetStdHandle(STD_OUTPUT_HANDLE), true);
		DisableCtrButton(false, true, true);
		disableUserSelection();
		disableCtrlHandler();
	}
	~Graphic();
	static void textSize(HANDLE hStdOut, int fsize);
	void setWindowSize(short width, short height);
	void DisableCtrButton(bool Close, bool Min, bool Max);
	static void showScrollBar(BOOL Show);
	static void hideCursor(HANDLE h, bool isHideCursor = true);
	static void fixConsoleWindow();
	void disableUserSelection();

	void disableCtrlHandler();
};


#endif // !_GRAPHICS_H
