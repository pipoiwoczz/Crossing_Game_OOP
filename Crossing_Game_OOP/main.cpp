#include "cAsset.h"
#include "cGame.h"
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
const string PlayerPrefix = "Player//";
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
vector<Texture> cAsset::alphabet;
vector<Texture> cAsset::number;
vector<Texture> cAsset::special;
int cGameEngine::count = 0;
HANDLE cGameEngine::curHandle = 0;

bool enginecheck = cGameEngine::startEngine();

//GameAsset
Texture cAsset::blankchar;
vector<Texture> cTrafficLight::motionFrames;
vector<Texture> cLilyleaf::motionFrames;
vector<Texture> cLion::motionFrames;
vector<Texture> cRhino::motionFrames;
vector<Texture> cCrocodile::motionFrames;
vector<Texture> cShark::motionFrames;
vector<Texture> cSurfer::motionFrames;
vector<Texture> cTruck::motionFrames;
vector<Texture> cCar::motionFrames;
vector<Texture> cMotorbike::motionFrames;

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

int gameMap::currentTheme;
gameMap* gameMap::currentMap;
int gameMap::currentMapIndex;
int gameMap::numCurrentMapFrame;
int gameMap::mapLoopCooldown = 15;

cWidget cGame::window;
cDWindow cGame::mainMenu;
cGame cGame::game;

bool gameinit = cGame::InitGame();

bool mainLoader()
{
	cBar loadingBar(&cGame::mainMenu, { 20, 140 },  500, 8, Color::red, Color::white);
	cAsset::alphabetLoader();
	cAsset::numberLoader();
	cAsset::specialCharLoader();
	cAsset::blankchar = cAsset::assetLoader("Char//Alphabet//blank.txt");
	loadingBar.setProgress(false, 10);
	cTrafficLight::motionFrames = cAsset::assetLoaders(trafficlightFile, TexturePrefix);
	cLilyleaf::motionFrames = cAsset::assetLoaders(lilyFile, TexturePrefix);
	cLion::motionFrames = cAsset::assetLoaders(lionFile, TexturePrefix);
	cRhino::motionFrames = cAsset::assetLoaders(rhinoFile, TexturePrefix);
	cCrocodile::motionFrames = cAsset::assetLoaders(crocoFile, TexturePrefix);
	cShark::motionFrames = cAsset::assetLoaders(sharkFile, TexturePrefix);
	cSurfer::motionFrames = cAsset::assetLoaders(surferFile, TexturePrefix);
	cCar::motionFrames = cAsset::assetLoaders(carFile, TexturePrefix);
	cTruck::motionFrames = cAsset::assetLoaders(truckFile, TexturePrefix);
	cMotorbike::motionFrames = cAsset::assetLoaders(motorbFile, TexturePrefix);
	loadingBar.setProgress(false, 50);

	cAsset::FxFrame = cAsset::assetLoader(FxPrefix + FxFrameFile);
	cMotorbike::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cTruck::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cCar::impactFx = cAsset::assetLoaders(carFile, TexturePrefix);
	cLion::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cCrocodile::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cRhino::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cShark::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cSurfer::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	loadingBar.setProgress(false, 80);

	gameMap::listMap;
	for (int i = 0; i < mapFiles.size(); i++)
	{
		gameMap::listMap.push_back(gameMap::loadMap(mapFiles[i]));
	}
	

	loadingBar.setProgress(false, 100);
	Sleep(100);
	loadingBar.unshow();
	return true;
}

bool cGame::mainloop = mainLoader();

int main() {
	cGame::onGameReady();
	cGameEngine::cleanEngine();
}