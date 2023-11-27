#ifndef CASSET_H
#define CASSET_H
#include "setup.h"

const vector<string> lionFile { "unk1.txt", "unk2.txt" };
const vector<string> rhinoFile { "rhino.txt" };
const vector<string> crocoFile { "croco.txt" };
const vector<string> truckFile { "truck.txt" };
const vector<string> heliFile { "heli.txt" };
const vector<string> motorbFile { "motorb.txt" };
const vector<string> lionImpactEffect { "fxframe.txt", "base.txt", "purple.txt", "blast.txt", "explosion1.txt","explosion2.txt", "explosion3.txt","fade1.txt", "fade2.txt", "fade3.txt", "dissappear.txt" };
const vector<string> maplist { "menuBG.txt", "map_forest.txt" };

const vector<string> peopleFile { "player.txt" };

class cGameEngine;
class Texture {
private:
	short height;
	short width;
public:
	friend class gameMap;
	friend class cAsset;
	friend class cObstacle;
	friend class cGame;
	friend cGameEngine;
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
class cLabel;
class cAsset {
private:
	cAsset();
public:
	static vector<Texture> alphabet;
	static vector<Texture> number;
	static Texture blankchar;
	friend cLabel;
	friend cGameEngine;
	static Texture assetLoader(string filename);
	static vector<Texture> assetLoaders(const vector<string> &textureList);
	static void alphabetLoader();
	static void numberLoader();
};


#endif