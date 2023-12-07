#ifndef MAP_H
#define MAP_H
#include "setup.h"
class cAsset;
class gameMap {
private:
	static vector<vector<gameMap>> listMap;

	static int currentTheme;
	static gameMap* currentMap;
	static int currentMapIndex;
	static int numCurrentMapFrame;

	static int mapLoopCooldown;
	CHAR_INFO* mapArray = nullptr;
	short width;
	short height;

public:
	friend class cGame;
	//friend class cPeople;
	friend class cGameEngine;
	gameMap();
	~gameMap();
	gameMap(const gameMap& a);
	gameMap& operator=(const gameMap& a);

	static vector<gameMap> loadMap(const vector<string>& mapFrames);
	static gameMap* getCurrentMap();
	static void changeMapTheme(MapTheme newTheme);
	static vector<short> getcurrentMapLayout();
	static void changeMapTheme(int newTheme);
	static void nextMapFrame();

	friend cAsset;
	friend bool mainLoader();
};

#endif	
