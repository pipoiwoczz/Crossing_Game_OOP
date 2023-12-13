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

//Environment objects
const vector<string> trafficlightFile {"trafficlightgreen", "trafficlightred"};
const vector<string> lilyFile { "lily" };		
const vector<string> coinFile { "coin" };
//Obstacles objects
const vector<string> lionFileR { "LionR1","LionR2","LionR3", "LionR2" };
const vector<string> lionFileL { "LionL1", "LionL2", "LionL3", "LionL2"};

const vector<string> rhinoFileR { "RhinoR1","RhinoR2","RhinoR3", "RhinoR2"};
const vector<string> rhinoFileL { "RhinoL1","RhinoL2","RhinoL3", "RhinoL2" };

const vector<string> crocoFileR { "CrocodileR1","CrocodileR2","CrocodileR3", "CrocodileR2" };
const vector<string> crocoFileL { "CrocodileL1","CrocodileL2","CrocodileL3", "CrocodileL2" };

const vector<string> sharkFileR { "SharkR1","SharkR2" ,"SharkR3" , "SharkR2" };
const vector<string> sharkFileL { "SharkL1","SharkL2" ,"SharkL3" , "SharkL2" };

const vector<string> surferFileR { "SurferR1","SurferR2" ,"SurferR3" , "SurferR2" };
const vector<string> surferFileL { "SurferL1","SurferL2" ,"SurferL3" , "SurferL2" };

const vector<string> truckFileR { "TruckR" };
const vector<string> truckFileL { "TruckL" };

const vector<string> carFileR { "CarR" };
const vector<string> carFileL { "CarL" };

const vector<string> motorbFileR { "BikeR" };
const vector<string> motorbFileL { "BikeL" };

const string FxFrameFile { "fxframe" };
const vector<string> hedgeImpactEffect {"base", "purple", "blast", "explosion1","explosion2", "explosion3","fade1", "fade2", "fade3", "dissappear" };
const vector<string> lionImpactEffect{"Lionimpact1","Lionimpact2","Lionimpact3","Lionimpact4","Lionimpact" };
const vector<string> RhinoImpactEffect{ "Rhinoimpact1","Rhinoimpact2","Rhinoimpact3","Rhinoimpact4","Rhinoimpact5" };
const vector<string> CrocoImpactEffect{ "Crocodileimpact1","Crocodileimpact2","Crocodileimpact3","Crocodileimpact4" };
const vector<string> BikeImpactEffect{ "Bikeimpact1","Bikeimpact2","Bikeimpact3","Bikeimpact4" };
const vector<string> CarImpactEffect{ "Carimpact1","Carimpact2","Carimpact3" };
const vector<string> TruckImpactEffect{ "Truckimpact1","Truckimpact2","Truckimpact3"};
const vector<string> SharkImpactEffect{ "Sharkimpact1","Sharkimpact2","Sharkimpact3","Sharkimpact4" };
const vector<string> SurferImpactEffect{ "Surferimpact1","Surferimpact2","Surferimpact3" };

const vector<vector<string>> mapFiles{
	{"jungle1", "jungle2", "jungle3"},
	{"beach1", "beach2", "beach3"},
	{"city1"}
};
const vector<string> PeopleFile { "up", "right", "down", "left"};



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
	static Texture flashEffect;
	static vector<Texture> alphabet;
	static vector<Texture> number;
	static vector<Texture> special;
	static Texture blankchar;
	static Texture FxFrame;
	friend cLabel;
	friend cGameEngine;
	static Texture assetLoader(string filename, const string& prefix = "");
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
