#include "cAsset.h"
#include "cGame.h"
#include "cPeople.h"
#include "gameEngine.h"
#include "cObstacle.h"
#include "cWidget.h"
#include "cAnimal.h"
#include "cEnvironment.h"
#include "cVehicle.h"
#include "Sound.h"
#include "Map.h"

//Game Core
const string UIPrefix = "UI//";
const string TexturePrefix = "Obstacles//";
const string FxPrefix = "FX//";
const string CubePrefix = "Player//Cube//";
const string RabbitPrefix = "Player//Rabbit//";
const string MapPrefix = "Maps//";
const string LevelPrefix = "Level//";
const HANDLE mainHandle = GetStdHandle(STD_OUTPUT_HANDLE);

int Sound::BGSoundVolume = 1000;
int Sound::EffectSoundVolume = 1000;

SMALL_RECT My_Windows = { 0, 0, 0, 0 };
SMALL_RECT PlayBoxRect = { 0, 0, 0, 0 };
COORD cGameEngine::buffsize = { 0,0 };
CHAR_INFO* cGameEngine::mainBuffer = nullptr;
CHAR_INFO* cGameEngine::reservedBuffer = nullptr;
HANDLE cGameEngine::Hbuffer1 = 0;
HANDLE cGameEngine::Hbuffer2 = 0;
bool cGameEngine::startDrawThread = true;
vector<Texture> cAsset::alphabet;
vector<Texture> cAsset::number;
vector<Texture> cAsset::special;
int cGameEngine::count = 0;
HANDLE cGameEngine::curHandle = 0;

bool enginecheck = cGameEngine::startEngine();

//GameAsset
//Textures
Texture cAsset::blankchar;
Texture cCoin::motionFrame;
Texture cAsset::flashEffect;
vector<Texture> cTrafficLight::motionFrames;
vector<Texture> cLilyleaf::motionFrames;
vector<Texture> cLion::motionFramesR;
vector<Texture> cLion::motionFramesL;
vector<Texture> cRhino::motionFramesR;
vector<Texture> cRhino::motionFramesL;
vector<Texture> cCrocodile::motionFramesR;
vector<Texture> cCrocodile::motionFramesL;
vector<Texture> cShark::motionFramesR;
vector<Texture> cShark::motionFramesL;
vector<Texture> cSurfer::motionFramesR;
vector<Texture> cSurfer::motionFramesL;
vector<Texture> cTruck::motionFramesR;
vector<Texture> cTruck::motionFramesL;
vector<Texture> cCar::motionFramesR;
vector<Texture> cCar::motionFramesL;
vector<Texture> cMotorbike::motionFramesR;
vector<Texture> cMotorbike::motionFramesL;

//FX Textures
Texture cAsset::FxFrame;
vector<Texture> cMotorbike::impactFx;
vector<Texture> cCar::impactFx;
vector<Texture> cTruck::impactFx;
vector<Texture> cLion::impactFx;
vector<Texture> cCrocodile::impactFx;
vector<Texture> cRhino::impactFx;
vector<Texture> cShark::impactFx;
vector<Texture> cSurfer::impactFx;
vector<vector<gameMap>> gameMap::listMap;

//Sound Assets
wstring Sound::currentSound;
vector<wstring> Sound::SoundEffectList = { L"menuMove", L"coinEarn", L"LionFx", L"RhinoFx", L"CrocoFx", L"SharkFx", L"SurferFx", L"VehicleFx", L"RiverFx", L"flashFx", L"freezeFx", L"levelUp"};
vector<wstring> Sound::TrackList = { L"background" };

//Map-related stuffs
int gameMap::currentTheme;
gameMap* gameMap::currentMap;
int gameMap::currentMapIndex;
int gameMap::numCurrentMapFrame;
int gameMap::mapLoopCooldown = 15;

//UI-Window stuffs
cWidget cGame::window;
cDWindow cGame::mainMenu;
cGame cGame::game;
bool cPeople::isRabbit = true;


bool gameinit = cGame::InitGame();

bool mainLoader()
{
	_mkdir("Save");
	cAsset::settingsLoader();
	Sound::startAudioEngine();
	cBar loadingBar(&cGame::mainMenu, { 20, 140 },  500, 8, Color::red, Color::white);
	cAsset::alphabetLoader();
	cAsset::numberLoader();
	cAsset::specialCharLoader();
	cAsset::blankchar = cAsset::assetLoader("blank", "Char//Alphabet//");
	loadingBar.setProgress(false, 10);

	cCoin::motionFrame = cAsset::assetLoader("coin", TexturePrefix);
	cAsset::flashEffect = cAsset::assetLoader("skillFlash", FxPrefix);

	cTrafficLight::motionFrames = cAsset::assetLoaders(trafficlightFile, TexturePrefix);
	cLilyleaf::motionFrames = cAsset::assetLoaders(lilyFile, TexturePrefix);

	cLion::motionFramesR = cAsset::assetLoaders(lionFileR, TexturePrefix);
	cLion::motionFramesL = cAsset::assetLoaders(lionFileL, TexturePrefix);

	cRhino::motionFramesR = cAsset::assetLoaders(rhinoFileR, TexturePrefix);
	cRhino::motionFramesL = cAsset::assetLoaders(rhinoFileL, TexturePrefix);

	cCrocodile::motionFramesR = cAsset::assetLoaders(crocoFileR, TexturePrefix);
	cCrocodile::motionFramesL = cAsset::assetLoaders(crocoFileL, TexturePrefix);

	cShark::motionFramesR = cAsset::assetLoaders(sharkFileR, TexturePrefix);
	cShark::motionFramesL = cAsset::assetLoaders(sharkFileL, TexturePrefix);

	cSurfer::motionFramesR = cAsset::assetLoaders(surferFileR, TexturePrefix);
	cSurfer::motionFramesL = cAsset::assetLoaders(surferFileL, TexturePrefix);

	cCar::motionFramesR = cAsset::assetLoaders(carFileR, TexturePrefix);
	cCar::motionFramesL = cAsset::assetLoaders(carFileL, TexturePrefix);

	cTruck::motionFramesR = cAsset::assetLoaders(truckFileR, TexturePrefix);
	cTruck::motionFramesL = cAsset::assetLoaders(truckFileL, TexturePrefix);

	cMotorbike::motionFramesR = cAsset::assetLoaders(motorbFileR, TexturePrefix);
	cMotorbike::motionFramesL = cAsset::assetLoaders(motorbFileL, TexturePrefix);

	loadingBar.setProgress(false, 50);

	cAsset::FxFrame = cAsset::assetLoader(FxPrefix + FxFrameFile);
	cMotorbike::impactFx = cAsset::assetLoaders(BikeImpactEffect, FxPrefix);
	cTruck::impactFx = cAsset::assetLoaders(TruckImpactEffect, FxPrefix);
	cCar::impactFx = cAsset::assetLoaders(CarImpactEffect, FxPrefix);
	cLion::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cCrocodile::impactFx = cAsset::assetLoaders(CrocoImpactEffect, FxPrefix);
	cRhino::impactFx = cAsset::assetLoaders(RhinoImpactEffect, FxPrefix);
	cShark::impactFx = cAsset::assetLoaders(SharkImpactEffect, FxPrefix);
	cSurfer::impactFx = cAsset::assetLoaders(SurferImpactEffect, FxPrefix);
	loadingBar.setProgress(false, 80);

	gameMap::listMap;
	for (int i = 0; i < mapFiles.size(); i++)
	{
		gameMap::listMap.push_back(gameMap::loadMap(mapFiles[i]));
	}
	loadingBar.unshow();
	loadingBar.setProgress(false, 100);
	Sleep(100);

	return true;
}

bool cGame::mainloop = mainLoader();

int main() {
	srand(NULL);
	cGame::onGameReady();
	cAsset::settingSave();

	Sound::cleanAudioEngine();
	cGameEngine::cleanEngine();
}