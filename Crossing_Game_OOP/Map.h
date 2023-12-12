#ifndef MAP_H
#define MAP_H
#include "setup.h"
class cAsset;
class gameMap {
private:
	static vector<vector<gameMap>> listMap;

	static int currentTheme;
	static gameMap* currentMap;
	static int currentMapIndex; // current bg # (for the theme)
	static int numCurrentMapFrame; // total bg # for the theme

	static int mapLoopCooldown; // timer until cycle
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

	static vector<gameMap> loadMap(const vector<string>& mapFrames); // load listMap
	static gameMap* getCurrentMap();
	static void changeMapTheme(MapTheme newTheme); // change theme
	static void changeMapTheme(int newTheme);
	static void nextMapFrame(); // cycle through backgrounds
	static void mapChangeTick(); // loop and call nextMapFrame periodically

	friend cAsset;
	friend bool mainLoader();
};

#endif	
