#ifndef CASSET_H
#define CASSET_H
#include "setup.h"

class cObstacle;

const vector<string> lionFile { "lion.txt" };
const vector<string> rhinoFile {"rhino.txt"};
const vector<string> crocoFile { "croco.txt" };
const vector<string> truckFile { "truck.txt" };
const vector<string> heliFile { "heli.txt" };
const vector<string> motorbFile {"motorb.txt"};
const vector<string> maplist { "jungle.txt" };

const vector<string> peopleFile{ "people.txt" };

enum class MapIndex {
	Jungle = 0
};

enum class AnimalIndex {
	Lion = 0,
	Rhino = 1,
	Crocodile = 2
};

enum class VehicleIndex {
	Truck = 0,
	Heli = 1,
	Motorbike = 2
};

struct BlankSegment {
	short start, end;
};

class cAsset;

class Texture {
private:
public:
	short height;
	short width;
	//vector<vector<BlankSegment>> blankTexture;
	CHAR_INFO* textureArray;
	Texture() {
		textureArray = nullptr;
	}
	Texture(const Texture& a)
	{
		height = a.height;
		width = a.width;
		textureArray = new CHAR_INFO[height * width];
		memcpy(textureArray, a.textureArray, a.height * a.width * sizeof(CHAR_INFO));
	}
	Texture& operator=(const Texture& a)
	{
		height = a.height;
		width = a.width;
		delete[]textureArray;
		textureArray = new CHAR_INFO[height * width];
		memcpy(textureArray, a.textureArray, a.height * a.width * sizeof(CHAR_INFO));
	}
	~Texture()
	{
		if (textureArray)
			delete[]textureArray;
	}
	friend cAsset;
	friend cObstacle;
};

class gameMap {
public:
	short height;
	short width;
	CHAR_INFO* mapArray;
	gameMap()
	{
		mapArray = nullptr;
	}
	~gameMap()
	{
		if (mapArray)
			delete[]mapArray;
	}
	friend cAsset;
	gameMap(const gameMap& a)
	{
		height = a.height;
		width = a.width;
		mapArray = new CHAR_INFO[height*width];
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
};

class cAsset {
private:
	cAsset();
	//Maps textures go here
	static vector<gameMap> listMap;
	static gameMap* currentMap;
			
public:
	static Texture assetLoader(string filename);
	static vector<Texture> assetLoader2(const vector<string>& textureList);
	friend cObstacle;
	static vector<gameMap> loadMap();
	static gameMap* getCurrentMap();
	static void changeMap(MapIndex newMapIndex);
};
#endif