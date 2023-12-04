#ifndef CWIDGET_H
#define CWIDGET_H

#include "cAsset.h"

class cGameEngine;
class cGame;
class cButton;
class cLabel;
class cDWindow;
class cBar;

class cWidget {
private:
	cWidget() {
		IsVisible = false;
	}
protected:
	bool IsVisible = false;
	COORD topleft = { 0,0 };
	COORD offset = { 0, 0 };
	COORD botright = { 0, 0 };
	cWidget* parentWindow = nullptr;;
	Texture WidgetFace;

	cWidget(cWidget* parentWindow, COORD offsetFromParentTopleft, const string& imgSrc);
public:
	virtual bool show(bool showNow = true);
	virtual bool unshow(bool showNow = true);
	void setOffset(COORD In_topleft);
	COORD getTL();
	COORD getOffset();

	friend cDWindow;
	friend cButton;
	friend cLabel;
	friend cBar;

	friend cGame;
	friend cGameEngine;
};



class cDWindow : public cWidget {
private:
public:
	cDWindow(): cWidget() {};
	cDWindow(cWidget* parent, COORD offsetFromParentTopleft, const string& imgSrc, bool showNow = false);
	cDWindow(cDWindow* parent, COORD offsetFromParentTopleft, const string& imgSrc, bool showNow = false);

	bool show(bool showNow = true);
	bool unshow(bool showNow = true);

	cDWindow& operator=(const cDWindow& newWindow) {
		if (this != &newWindow) {
			// Copy base class members
			this->IsVisible = newWindow.IsVisible;
			this->topleft = newWindow.topleft;
			this->offset = newWindow.offset;
			this->botright = newWindow.botright;
			this->parentWindow = newWindow.parentWindow;
			this->WidgetFace = newWindow.WidgetFace;  // Assuming Texture has a proper assignment operator or copy constructor

			// Additional assignments specific to cDWindow
			// Add more assignments if cDWindow has additional members

			// You may also need to handle dynamic memory if any, e.g., deep copy

		}
		return *this;

	}
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
	cButton(cDWindow* parent, COORD offsetFromParentTopleft, const string& imgSrc, short borderDensity, void (*pFunction) (), bool showNow = false);
	cButton(cDWindow* parent, COORD offsetFromParentTopleft, const string& imgSrc, short borderDensity, bool showNow = false);
	bool show(bool showNow = true);
	bool unshow(bool showNow = true);

	void onSelect();
	void onDeSelect();
	void onEnter();
};


class cLabel {
protected:
	cDWindow* parentWindow = nullptr;
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
	cLabel(cDWindow* parentWindow, COORD offsetFromParentTopleft, const string& text, const short& align, Color textColor, bool showNow = false);
	//cLabel(cButton* parentWindow, COORD offsetFromParentTopleft, const string& text, const short& align, Color textColor, bool showNow = false);
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
	COORD topleft;
	COORD offset;
	COORD botright;
public:	

	friend cGameEngine;
	
	cBar(cDWindow* parentWindow, COORD offsetFromParentTopleft, const short& length, const short& width, Color barColor, Color BarBGColor, bool showNow = false);
	bool setProgress(bool autoRun = true, short percentage = 0, bool showNow = true);
	bool show(bool showNow = true);
	bool unshow(bool showNow = true);
};
#endif