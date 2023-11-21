#ifndef CASSET_H
#define CASSET_H
#include "setup.h"

const vector<string> lionFile { "unk1.txt", "unk2.txt"};
const vector<string> rhinoFile {"rhino.txt"};
const vector<string> crocoFile { "croco.txt" };
const vector<string> truckFile { "truck.txt" };
const vector<string> heliFile { "heli.txt" };
const vector<string> motorbFile {"motorb.txt"};

const vector<string> maplist { "Sprites//map_forest.txt" };

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




//predeclare
class Texture {
private:
	short height;
	short width;
public:
	friend class gameMap;
	friend class cAsset;
	friend class cObstacle;
	friend class cGame;
	friend class cGameEngine;
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
	void setHeight(const short &height)
	{
		this->height = height;
	}
	void setWidth(const short &width)
	{
		this->width = width;
	}
	short getHeight() {
		return height;
	}
	short getWidth() {
		return width;
	}
};

class cAsset {
private:
	cAsset();
public:
	static Texture assetLoader(string filename);
	static vector<Texture> assetLoaders(const vector<string>& textureList);
};


#endif