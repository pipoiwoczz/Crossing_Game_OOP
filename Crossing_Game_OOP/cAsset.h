#ifndef CASSET_H
#define CASSET_H
#include "setup.h"

const vector<string> lilyFile{ "lily.txt" };		
const vector<string> lionFile { "lionmove1.txt", "lionmove2.txt","lionmove3.txt","lionmove4.txt","lionmove5.txt","lionmove6.txt","lionmove7.txt" };
const vector<string> rhinoFile { "RhinoR1.txt","RhinoR2.txt","RhinoR3.txt" };
const vector<string> crocoFile { "croco.txt" };
const vector<string> truckFile { "truck.txt" };
const vector<string> heliFile { "heli.txt" };
const vector<string> motorbFile { "motorb.txt" };
const vector<string> hedgeImpactEffect { "fxframe.txt", "base.txt", "purple.txt", "blast.txt", "explosion1.txt","explosion2.txt", "explosion3.txt","fade1.txt", "fade2.txt", "fade3.txt", "dissappear.txt" };
const vector<string> lionImpactEffect{ "fxframe.txt", "lioneffect1.txt", "lioneffect2.txt","lioneffect3.txt","lioneffect4.txt","lioneffect5.txt" ,"lioneffect6.txt" ,"lioneffect7.txt","lioneffect8.txt","lioneffect9.txt","lioneffect10.txt" };

const vector<string> maplist {"jungle1.txt", "jungle2.txt", "jungle3.txt"};
const vector<string> peopleFile { "up.txt", "right.txt", "down.txt", "left.txt"};
const string UIPrefix = "UI//";
const string TexturePrefix = "Obstacles//";
const string FxPrefix = "FX//";
const string PlayerPrefix = "Player//";
const string MapPrefix = "Maps//";
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
	static vector<Texture> assetLoaders(const vector<string> &textureList, const string& prefix);
	static void alphabetLoader();
	static void numberLoader();
};


#endif