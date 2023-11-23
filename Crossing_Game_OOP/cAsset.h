#ifndef CASSET_H
#define CASSET_H
#include "setup.h"

const vector<string> lionFile { "unk1.txt", "unk2.txt" };
const vector<string> rhinoFile { "rhino.txt" };
const vector<string> crocoFile { "croco.txt" };
const vector<string> truckFile { "truck.txt" };
const vector<string> heliFile { "heli.txt" };
const vector<string> motorbFile { "motorb.txt" };

const vector<string> maplist { "Sprites//map_forest.txt" };

const vector<string> peopleFile { "people.txt" };


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
	CHAR_INFO* textureArray = nullptr;
	Texture();
	Texture(const Texture& a);
	Texture& operator=(const Texture& a);
	~Texture();
	void setHeight(const short& height);
	void setWidth(const short& width);
	short getHeight();
	short getWidth();
};

class cAsset {
private:
	cAsset();
public:
	static Texture assetLoader(string filename);
	static vector<Texture> assetLoaders(const vector<string> &textureList);
};


#endif