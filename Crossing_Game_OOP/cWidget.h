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
	cWidget() {}
protected:
	bool IsVisible;
	PHANDLE pHandle;
	string tag;
	COORD topleft;
	COORD botright;
	cWidget* parentWindow = nullptr;;
	Texture WidgetFace;

	cWidget(cWidget* parentWindow, COORD offsetFromParentTopleft, const string& tagName, const string& imgSrc);
public:
	static cWidget window;
	static void createMainWindow(const string& tagName);
	virtual void show();
	virtual void unshow();
	friend cDWindow;
	friend cButton;
	friend cLabel;
};



class cDWindow : public cWidget {
private:
public:
	cDWindow(cWidget* parent, COORD Topleft, const string& tagName, const string& imgSrc);
	cDWindow(COORD Topleft, const string& tagName, const string& imgSrc);
	void show();
	void unshow();
};
 
class cButton: public cWidget {
private:

	COORD OTopleft;
	COORD OBotright;
	int bordDensity;
	void (*buttonFunction) (void) = nullptr;
	void highLight();
	void unHighLight();
public:
	friend cGameEngine;
	cButton(cDWindow* parent, COORD offsetFromParentTopleft,const string& tagName, const string& imgSrc, int borderDensity, void (*pFunction) (void));

	void show();
	void unshow();

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
	PHANDLE pHandle;
	string tag;
	COORD topleft;
	COORD botright;

	vector<tchar> textLine;
	void createTextline();
	cLabel(cWidget* parentWindow, COORD offsetFromParentTopleft, const string& tagName, const string& text, const short& align, Color textColor);
public:
	cLabel(cDWindow* parentWindow, COORD offsetFromParentTopleft, const string& tagName, const string& text, const short& align, Color textColor);
	void show();
	void unshow();
	void updateText(const string& newText);
};
#endif