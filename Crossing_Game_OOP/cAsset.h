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
const vector<string> trafficlightFile {"trafficlightgreen.txt", "trafficlightred.txt"};
const vector<string> lilyFile { "lily.txt" };		

//Obstacles objects
const vector<string> lionFileR { "LionR1.txt","LionR2.txt","LionR3.txt", "LionR2.txt" };
const vector<string> lionFileL { "LionL1.txt", "LionL2.txt", "LionL3.txt", "LionL2.txt"};

const vector<string> rhinoFileR { "RhinoR1.txt","RhinoR2.txt","RhinoR3.txt", "RhinoR2.txt"};
const vector<string> rhinoFileL { "RhinoL1.txt","RhinoL2.txt","RhinoL3.txt", "RhinoL2.txt" };

const vector<string> crocoFileR { "CrocodileR1.txt","CrocodileR2.txt","CrocodileR3.txt", "CrocodileR2.txt" };
const vector<string> crocoFileL { "CrocodileL1.txt","CrocodileL2.txt","CrocodileL3.txt", "CrocodileL2.txt" };

const vector<string> sharkFileR { "SharkR1.txt","SharkR2.txt" ,"SharkR3.txt" , "SharkR2.txt" };
const vector<string> sharkFileL { "SharkL1.txt","SharkL2.txt" ,"SharkL3.txt" , "SharkL2.txt" };

const vector<string> surferFileR { "SurferR1.txt","SurferR2.txt" ,"SurferR3.txt" , "SurferR2.txt" };
const vector<string> surferFileL { "SurferL1.txt","SurferL2.txt" ,"SurferL3.txt" , "SurferL2.txt" };

const vector<string> truckFileR { "TruckR.txt" };
const vector<string> truckFileL { "TruckL.txt" };

const vector<string> carFileR { "CarR.txt" };
const vector<string> carFileL { "CarL.txt" };

const vector<string> motorbFileR { "BikeR.txt" };
const vector<string> motorbFileL { "BikeL.txt" };

const string FxFrameFile { "fxframe.txt" };
const vector<string> hedgeImpactEffect {"base.txt", "purple.txt", "blast.txt", "explosion1.txt","explosion2.txt", "explosion3.txt","fade1.txt", "fade2.txt", "fade3.txt", "dissappear.txt" };
const vector<string> lionImpactEffect{"Lionimpact1.txt","Lionimpact2.txt","Lionimpact3.txt","Lionimpact4.txt","Lionimpact.txt" };
const vector<string> RhinoImpactEffect{ "Rhinoimpact1.txt","Rhinoimpact2.txt","Rhinoimpact3.txt","Rhinoimpact4.txt","Rhinoimpact5.txt" };
const vector<string> CrocoImpactEffect{ "Crocodileimpact1.txt","Crocodileimpact2.txt","Crocodileimpact3.txt","Crocodileimpact4.txt" };
const vector<string> BikeImpactEffect{ "Bikeimpact1.txt","Bikeimpact2.txt","Bikeimpact3.txt","Bikeimpact4.txt" };
const vector<string> CarImpactEffect{ "Carimpact1.txt","Carimpact2.txt","Carimpact3.txt" };
const vector<string> TruckImpactEffect{ "Truckimpact1.txt","Truckimpact2.txt","Truckimpact3.txt"};
const vector<string> SharkImpactEffect{ "Sharkimpact1.txt","Sharkimpact2.txt","Sharkimpact3.txt","Sharkimpact4.txt" };
const vector<string> SurferImpactEffect{ "Surferimpact1.txt","Surferimpact2.txt","Surferimpact3.txt" };

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
