#ifndef MAP_H
#define MAP_H
#include "setup.h"
class cAsset;
class gameMap {
private:
public:
	static vector<gameMap> listMap;
	static gameMap* currentMap;
	static MapIndex currentMapIndex;

	CHAR_INFO* mapArray = nullptr;
	short width;
	short height;

	friend class cObstacle;
	friend class cGame;
	friend class cPeople;
	friend class cGameEngine;
	gameMap();
	~gameMap();
	gameMap(const gameMap& a);
	gameMap& operator=(const gameMap& a);

	static vector<gameMap> loadMap();
	static gameMap* getCurrentMap();
	static void changeMap(MapIndex newMapIndex);
	static void nextMap();

	friend cAsset;
};

#endif