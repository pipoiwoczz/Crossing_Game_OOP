#ifndef MAP_H
#define MAP_H
#include "cAsset.h"
class gameMap {
private:
public:
	static vector<gameMap> listMap;
	static gameMap* currentMap;
	static MapIndex currentMapIndex;

	CHAR_INFO* mapArray;
	short width;
	short height;

	friend class cObstacle;
	friend class cGame;
	friend class cPeople;
	friend class cGameEngine;
	gameMap() {
		mapArray = nullptr;
	}
	~gameMap()
	{
		if (mapArray)
			delete[]mapArray;
	}
	gameMap(const gameMap& a)
	{
		height = a.height;
		width = a.width;
		mapArray = new CHAR_INFO[height * width];
		memcpy(mapArray, a.mapArray, a.height * a.width * sizeof(CHAR_INFO));
	}
	gameMap& operator=(const gameMap& a)
	{
		height = a.height;
		width = a.width;
		delete[]mapArray;
		mapArray = new CHAR_INFO[height * width];
		memcpy(mapArray, a.mapArray, a.height * a.width * sizeof(CHAR_INFO));
	}

	static vector<gameMap> loadMap();
	static gameMap* getCurrentMap();
	static void changeMap(MapIndex newMapIndex);
	static void nextMap();

	friend cAsset;
};

#endif