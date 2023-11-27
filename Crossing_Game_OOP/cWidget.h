#ifndef CWIDGET_H
#define CWIDGET_H

#include "cAsset.h"

class cGameEngine;

class cButton;
class cLabel;
class cDWindow;

class cWidget {
private:
	static bool hasWd;
	cWidget() {
		IsVisible = false;
	}
protected:
	bool IsVisible = false;
	string tag;
	COORD topleft = { 0,0 };
	COORD offset = { 0, 0 };
	COORD botright = { 0, 0 };
	cWidget* parentWindow = nullptr;;
	Texture WidgetFace;

	cWidget(cWidget* parentWindow, COORD offsetFromParentTopleft, const string& tagName, const string& imgSrc);
public:
	static cWidget window;
	static bool createMainWindow(const string& tagName);
	virtual void show(bool showNow = true);
	virtual void unshow(bool showNow = true);
	friend cDWindow;
	friend cButton;
	friend cLabel;

	friend cGameEngine;
};



class cDWindow : public cWidget {
private:
public:
	cDWindow(cWidget* parent, COORD Topleft, const string& tagName, const string& imgSrc);
	cDWindow(cDWindow* parent, COORD Topleft, const string& tagName, const string& imgSrc);

	void show(bool showNow = true);
	void unshow(bool showNow = true);
};
 
class cButton: public cWidget {
private:

	COORD OTopleft;
	COORD OBotright;
	short bordDensity;
	void (*buttonFunction) (void) = nullptr;
	void highLight(bool showNow = true);
	void unHighLight(bool showNow = true);
public:
	friend cGameEngine;
	cButton(cDWindow* parent, COORD offsetFromParentTopleft,const string& tagName, const string& imgSrc, short borderDensity, void (*pFunction) (void));

	void show(bool showNow = true);
	void unshow(bool showNow = true);

	void onSelect();
	void onDeSelect();
	void onEnter();
};


class cLabel {
private:
	cWidget* parentWindow = nullptr;
	struct tchar {
		Texture* pChar = nullptr;
		COORD pos;
	};
	short align;
	short color;
	string text;

	bool IsVisible;
	string tag;
	COORD topleft = { 0,0 };
	COORD offset = { 0, 0 };
	COORD botright = { 0, 0 };

	vector<tchar> textLine;
	void createTextline();
public:
	friend cGameEngine;
	cLabel(cDWindow* parentWindow, COORD offsetFromParentTopleft, const string& tagName, const string& text, const short& align, Color textColor);
	void show(bool showNow = true);
	void unshow(bool showNow = true);
	void updateText(const string& newText);
};
#endif