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
cWidget cWidget::window;

bool enginecheck = cGameEngine::startEngine();
bool cWidget::hasWd = cWidget::createMainWindow("main");

//GameAsset
Texture cAsset::blankchar;
vector<Texture> cLilyleaf::motionFrames;
vector<Texture> cLion::motionFrames;
vector<Texture> cRhino::motionFrames;
vector<Texture> cCrocodile::motionFrames;
vector<Texture> cTruck::motionFrames;
vector<Texture> cHelicopter::motionFrames;
vector<Texture> cMotorbike::motionFrames;

Texture cAsset::FxFrame;
vector<Texture> cMotorbike::impactFx;
vector<Texture> cHelicopter::impactFx;
vector<Texture> cTruck::impactFx;
vector<Texture> cLion::impactFx;
vector<Texture> cCrocodile::impactFx;
vector<Texture> cRhino::impactFx;
vector<vector<gameMap>> gameMap::listMap;

int gameMap::currentTheme;
gameMap* gameMap::currentMap;
int gameMap::currentMapIndex;
int gameMap::numCurrentMapFrame;

int gameMap::mapLoopCooldown = 15;

cDWindow mainMenu(&cWidget::window, { 0, 0 }, "bg", "menuBg.txt", true);
bool mainLoader()
{
	cBar loadingBar(&mainMenu, { 20, 140 }, "loadingbar", 500, 8, Color::red, Color::white);
	cAsset::alphabetLoader();
	cAsset::numberLoader();
	cAsset::specialCharLoader();
	cAsset::blankchar = cAsset::assetLoader("Char//Alphabet//blank.txt");
	loadingBar.setProgress(false, 10);
	cLilyleaf::motionFrames = cAsset::assetLoaders(lilyFile, TexturePrefix);
	cLion::motionFrames = cAsset::assetLoaders(lionFile, TexturePrefix);
	cRhino::motionFrames = cAsset::assetLoaders(rhinoFile, TexturePrefix);
	cCrocodile::motionFrames = cAsset::assetLoaders(crocoFile, TexturePrefix);
	cTruck::motionFrames = cAsset::assetLoaders(truckFile, TexturePrefix);
	cHelicopter::motionFrames = cAsset::assetLoaders(heliFile, TexturePrefix);
	cMotorbike::motionFrames = cAsset::assetLoaders(motorbFile, TexturePrefix);
	loadingBar.setProgress(false, 50);

	cAsset::FxFrame = cAsset::assetLoader(FxPrefix + FxFrameFile);
	cMotorbike::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cHelicopter::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cTruck::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cLion::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cCrocodile::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
	cRhino::impactFx = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
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

bool running = mainLoader();




cDWindow settingpanel(&cWidget::window, { 0,0 }, "settingpanel", "settingframe.txt");

void pmap1()
{
	cGame a;
	a.MainGame();
}

void pmap2()
{

}

void pmap3()
{				
	Sleep(1000);
}
void b1F(void)
{
	cDWindow mapMenu(&mainMenu, { 240, 55 }, "menumap", "mapPanel.txt");
	mapMenu.show();
	cButton map1(&mapMenu, { 10, 20 }, "map1", "jungleicon.txt", 1, pmap1);
	cButton map2(&mapMenu, { 84, 20 }, "map1", "jungleicon.txt", 1, pmap2);
	cButton map3(&mapMenu, { 158, 20 }, "map1", "jungleicon.txt", 1, pmap3);

	cButton buttonlist[3] = { map1, map2, map3 };


	int x = 0;
	for (int i = 0; i < 3; i++)
	{

		buttonlist[i].show();
	}
	buttonlist[x].onSelect();
		
	while (true)
	{
		if (GetAsyncKeyState(0x51) < 0)
			break;
		if (GetAsyncKeyState(0x0D) < 0)
		{
			buttonlist[x].onDeSelect();
			for (int i = 0; i < 3; i++)
			{
				buttonlist[i].unshow();
			}
			buttonlist[x].onEnter();
			break;

		}
		if (GetAsyncKeyState(VK_LEFT) && x > 0)
		{
			buttonlist[x].onDeSelect();
			x--;
			buttonlist[x].onSelect();
		}
		if (GetAsyncKeyState(VK_RIGHT) && x < 2)
		{
			buttonlist[x].onDeSelect();
			x++;
			buttonlist[x].onSelect();
		}
		Sleep(100);
	}
	for (int i = 0; i < 3; i++)
	{
		buttonlist[i].unshow();
	}
	mapMenu.unshow();

}

void b2F(void)
{
	settingpanel.show();

	void (*pSoundSetting[2][2])() = {
	{ Sound::reduceSoundBackground, Sound::increaseSoundBackground},
	{Sound::reduceEffectSound, Sound::increaseEffectSound}
	};
	int (*pSoundVolume[2])() = { Sound::getCurrentMusicVolume, Sound::getCurrentEffectVolume };

	cLabel music(&settingpanel, { 200, 61 }, "music", "Music Volume", 1, Color::black);
	cLabel musicvolume(&settingpanel, { 335,61 }, "musicvolume", to_string(pSoundVolume[0]() / 10), 1, Color::black);

	cLabel FXsound(&settingpanel, { 200, 91 }, "fx", "Effect Volume", 1, Color::black);
	cLabel FXvolume(&settingpanel, { 335, 91 }, "fxvolume", to_string(pSoundVolume[1]() / 10), 1, Color::black);

	cDWindow selectarrow(&settingpanel, { 370, 61 }, "selectarrow", "arrowL.txt");



	short arrowPos[2] = { 61, 91 };

	cLabel ValueBar[2] = { musicvolume, FXvolume };

	int currentarrowpos = 0;

	settingpanel.show();

	music.show();
	musicvolume.show();
	FXsound.show();
	FXvolume.show();

	selectarrow.show();
	while (true)
	{

		if (GetAsyncKeyState(VK_DOWN) < 0 && currentarrowpos < 1)
		{
			currentarrowpos++;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, arrowPos[currentarrowpos] });
			selectarrow.show();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && currentarrowpos > 0)
		{
			currentarrowpos--;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, arrowPos[currentarrowpos] });
			selectarrow.show();
		}
		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			pSoundSetting[currentarrowpos][0]();
			ValueBar[currentarrowpos].updateText(to_string(pSoundVolume[currentarrowpos]() / 10));
			Sleep(250);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			pSoundSetting[currentarrowpos][1]();
			ValueBar[currentarrowpos].updateText(to_string(pSoundVolume[currentarrowpos]() / 10));
			Sleep(250);
		}
		Sleep(150);
		if (GetAsyncKeyState(0x0D) < 0)
		{
			break;
		}
	}
	selectarrow.show();

	FXvolume.unshow();
	FXsound.unshow();
	musicvolume.unshow();
	music.show();

	settingpanel.unshow();
}

void b3F(void)
{
	cDWindow exitpanel(&cWidget::window, { 233, 60 }, "exitpanel", "exitpanel.txt", true);
	cDWindow selectarrow(&exitpanel, { 96, 37 }, "selectarrow", "enterarrow.txt", true);
	
	short arrowPos[2] = { 24, 37 };
	int currentarrowpos = 1;
	while (true)
	{
		if (GetAsyncKeyState(VK_DOWN) < 0 && currentarrowpos < 1)
		{
			currentarrowpos++;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, arrowPos[currentarrowpos] });
			selectarrow.show();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && currentarrowpos > 0)
		{
			currentarrowpos--;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, arrowPos[currentarrowpos] });
			selectarrow.show();
		}
		Sleep(150);
		if (GetAsyncKeyState(0x0D) < 0)
		{
			if (currentarrowpos == 0)
			{
				running = false;
			}
			break;

		}
	}
	exitpanel.unshow();	
}
int main() {
	mainMenu.show();
	cButton b1(&mainMenu, { 516, 55 }, "b1", "playbutton.txt", 1, b1F);
	cButton b2(&mainMenu, { 516, 90 }, "b2", "settingbutton.txt", 1, b2F);
	cButton b3(&mainMenu, { 516, 125 }, "b3", "exitbutton.txt", 1, b3F);

	cButton buttonlist[3] = { b1, b2, b3 };
	int x = 0;
	for (int i = 0; i < 3; i++)
	{
		buttonlist[i].show();
	}
	buttonlist[x].onSelect();

	while (running)
	{
		if (GetAsyncKeyState(VK_UP) && x > 0)
		{
			buttonlist[x].onDeSelect();
			x--;
			buttonlist[x].onSelect();
		}
		if (GetAsyncKeyState(VK_DOWN) && x < 2)
		{
			buttonlist[x].onDeSelect();
			x++;
			buttonlist[x].onSelect();
		}
		Sleep(150);
		if (GetAsyncKeyState(0x51) < 0)
			break;
		if (GetAsyncKeyState(0x0D) < 0)
		{
			buttonlist[x].onDeSelect();
			for (int i = 0; i < 3; i++)
			{
				buttonlist[i].unshow();
			}
			buttonlist[x].onEnter();
			mainMenu.show();
			for (int i = 0; i < 3; i++)
			{
				buttonlist[i].show();
			}
			buttonlist[x].onSelect();
		}

	}
	buttonlist[x].onDeSelect();
	for (int i = 0; i < 3; i++)
	{
		buttonlist[i].unshow();
	}
	//b.unshow();
	////_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	////_CrtDumpMemoryLeaks();
	mainMenu.unshow();

	cleanGame();
}

