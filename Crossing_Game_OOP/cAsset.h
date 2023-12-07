#ifndef CASSET_H
#define CASSET_H
#include "setup.h"

extern const string UIPrefix; 
extern const string TexturePrefix;
extern const string FxPrefix;
extern const string CubePrefix;
extern const string RabbitPrefix;
extern const string MapPrefix;
extern const string LevelPrefix;

const vector<string> trafficlightFile {"trafficlightgreen.txt", "trafficlightred.txt"};
const vector<string> lilyFile { "lily.txt" };		
const vector<string> lionFile { "LionR1.txt","LionR2.txt","LionR3.txt", "LionR2.txt" };
const vector<string> rhinoFile { "RhinoR1.txt","RhinoR2.txt","RhinoR3.txt", "RhinoR2.txt"};
const vector<string> crocoFile { "CrocodileR1.txt","CrocodileR2.txt","CrocodileR3.txt", "CrocodileR2.txt" };
const vector<string> sharkFile{ "SharkR1.txt","SharkR2.txt" ,"SharkR3.txt" , "SharkR2.txt" };
const vector<string> surferFile{ "SurferR1.txt","SurferR2.txt" ,"SurferR3.txt" , "SurferR2.txt" };
const vector<string> truckFile { "TruckR.txt" };
const vector<string> carFile { "CarR.txt" };
const vector<string> motorbFile { "BikeR.txt" };

const string FxFrameFile { "fxframe.txt" };
const vector<string> hedgeImpactEffect {"base.txt", "purple.txt", "blast.txt", "explosion1.txt","explosion2.txt", "explosion3.txt","fade1.txt", "fade2.txt", "fade3.txt", "dissappear.txt" };
const vector<string> lionImpactEffect{"Lionimpact1.txt","Lionimpact2.txt","Lionimpact3.txt","Lionimpact4.txt"};

const vector<vector<string>> mapFiles{
	{"jungle1.txt", "jungle2.txt", "jungle3.txt"},
	{"beach1.txt", "beach2.txt", "beach3.txt"},
	{"city1.txt"}
};
const vector<string> peopleFile { "up.txt", "right.txt", "down.txt", "left.txt"};



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
	static vector<Texture> special;
	static Texture blankchar;
	static Texture FxFrame;
	friend cLabel;
	friend cGameEngine;
	static Texture assetLoader(string filename);
	static vector<Texture> assetLoaders(const vector<string> &textureList, const string& prefix);
	static void alphabetLoader();
	static void numberLoader();
	static void specialCharLoader();
	static void settingsLoader();
	static void settingSave();
	static Texture* getChar(unsigned char In_char);
    
    Texture loader(string filename); // temporary (waiting for testing)
};


#endif
