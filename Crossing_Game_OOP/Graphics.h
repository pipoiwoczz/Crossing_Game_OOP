#pragma once
#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "setup.h"
#include <corecrt_wstring.h>

class Graphic {
	
public:
	Graphic() {
		textSize(8);
		SetConsoleTitle(L"Crossing Road");
		fixConsoleWindow();
		showScrollBar(false);
		hideCursor(true);
		DisableCtrButton(false, true, true);
		disableUserSelection();
		disableCtrlHandler();
	}
	~Graphic() {

	}
	void textSize(int);
	void setWindowSize(short width, short height);
	void DisableCtrButton(bool Close, bool Min, bool Max);
	void showScrollBar(BOOL Show);
	void hideCursor(bool isHideCursor);
	void fixConsoleWindow();
	void disableUserSelection();

	void disableCtrlHandler();
};


#endif // !_GRAPHICS_H
