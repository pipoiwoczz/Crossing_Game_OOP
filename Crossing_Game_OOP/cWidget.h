#ifndef CWIDGET_H
#define CWIDGET_H

#include "cAsset.h"

class cGameEngine;

class cButton;
class cLabel;
class cDWindow;
class cBar;

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
	virtual bool show(bool showNow = true);
	virtual bool unshow(bool showNow = true);
	void setPos(COORD In_topleft);
	COORD getPos();

	friend cDWindow;
	friend cButton;
	friend cLabel;
	friend cBar;

	friend cGameEngine;
};



class cDWindow : public cWidget {
private:
public:
	cDWindow(cWidget* parent, COORD Topleft, const string& tagName, const string& imgSrc, bool showNow = false);
	cDWindow(cDWindow* parent, COORD Topleft, const string& tagName, const string& imgSrc, bool showNow = false);

	bool show(bool showNow = true);
	bool unshow(bool showNow = true);
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
	cButton(cDWindow* parent, COORD offsetFromParentTopleft,const string& tagName, const string& imgSrc, short borderDensity, void (*pFunction) ());

	bool show(bool showNow = true);
	bool unshow(bool showNow = true);

	void onSelect();
	void onDeSelect();
	void onEnter();
};


class cLabel {
protected:
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
	bool show(bool showNow = true);
	bool unshow(bool showNow = true);
	void updateText(const string& newText);
};

class cBar {
private:
	cWidget* parentWindow = nullptr;
	short forecolor;
	short backcolor;
	bool IsVisible;
	short length;
	short width;
	short currentFill;
	string tag;
	COORD topleft;
	COORD offset;
	COORD botright;
public:	

	friend cGameEngine;
	
	cBar(cDWindow* parentWindow, COORD offsetFromParentTopleft, const string& tagName, const short& length, const short& width, Color barColor, Color BarBGColor);
	bool setProgress(bool autoRun = true, short percentage = 0, bool showNow = true);
	bool show(bool showNow = true);
	bool unshow(bool showNow = true);
};
#endif