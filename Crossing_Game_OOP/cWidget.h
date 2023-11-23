#ifndef CWIDGET_H
#define CWIDGET_H

#include "setup.h"
#include "cAsset.h"

class cGameEngine;
class cWidget {

protected:
	COORD OTopleft;
	int bordDensity;
	COORD topleft;
	vector<Texture> textures;
	Texture* pTexture = nullptr;
public:
	

	cWidget(COORD In_topleft, int borderDensity);
};

class cButton: public cWidget {
private:
	void (*buttonFunction) (void) = nullptr;
public:
	friend cGameEngine;
	cButton(COORD In_topleft, int borderDensity, void (*pFunction) ());
	void onSelect();

	void onDeSelect();

	void onEnter();

	void cleanButton(HANDLE curHandle);

	void drawButton(HANDLE curHandle);

	void drawBorder(HANDLE curHandle);
};

#endif