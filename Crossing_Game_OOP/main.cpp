#include "cGame.h"
#include "gameEngine.h"
#include "cObstacle.h"
#include "cWidget.h"
#include "cAnimal.h"
#include "cEnvironment.h"
#include "cVehicle.h"
#include "Sound.h"
#include "Map.h"

const HANDLE mainHandle = GetStdHandle(STD_OUTPUT_HANDLE);

int Sound::BGSoundVolume = 1000;
int Sound::EffectSoundVolume = 1000;

bool running = true;
SMALL_RECT My_Windows = { 0, 0, 0, 0 };
SMALL_RECT PlayBoxRect = { 0, 0, 0, 0 };
COORD cGameEngine::buffsize = { 0,0 };
CHAR_INFO* cGameEngine::mainBuffer = nullptr;
CHAR_INFO* cGameEngine::reservedBuffer = nullptr;
HANDLE cGameEngine::Hbuffer1 = 0;
HANDLE cGameEngine::Hbuffer2 = 0;

int cGameEngine::count = 0;
HANDLE cGameEngine::curHandle = 0;
bool enginecheck = cGameEngine::startEngine();
cWidget cWidget::loadingscreen;

cWidget cWidget::window;
bool cWidget::hasWd = cWidget::createMainWindow("mainbg");
cDWindow br(&cWidget::window, { 0, 0 }, "bg","menuBg.txt");
cDWindow settingpanel(&cWidget::window, {0,0}, "settingpanel", "settingframe.txt");

vector<Texture> cLilyleaf::textureLily = cAsset::assetLoaders(lilyFile, TexturePrefix);
vector<Texture> cLion::textureLion = cAsset::assetLoaders(lionFile, TexturePrefix);
vector<Texture> cRhino::textureRhino = cAsset::assetLoaders(rhinoFile, TexturePrefix);
vector<Texture> cCrocodile::textureCroco = cAsset::assetLoaders(crocoFile, TexturePrefix);
vector<Texture> cTruck::textureTruck = cAsset::assetLoaders(truckFile, TexturePrefix);
vector<Texture> cHelicopter::textureHeli = cAsset::assetLoaders(heliFile, TexturePrefix);
vector<Texture> cMotorbike::textureMotorb = cAsset::assetLoaders(motorbFile, TexturePrefix);

vector<Texture> cMotorbike::impactEffect = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
vector<Texture> cHelicopter::impactEffect = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
vector<Texture> cTruck::impactEffect = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
vector<Texture> cLion::impactEffect = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
vector<Texture> cCrocodile::impactEffect = cAsset::assetLoaders(lionImpactEffect, FxPrefix);
vector<Texture> cRhino::impactEffect = cAsset::assetLoaders(lionImpactEffect, FxPrefix);


void pmap1()
{
	cGame a;
	a.MainGame();
}

void pmap2()
{
	Sleep(1000);
}

void pmap3()
{				
	Sleep(1000);
}
void b1F(void)
{
	cDWindow mapMenu(&br, { 240, 55 }, "menumap", "mapPanel.txt");
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
			br.show();
			for (int i = 0; i < 3; i++)
			{
				buttonlist[i].show();
			}
			buttonlist[x].onSelect();

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
	Sleep(2000);
}
void b3F(void)
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

	cButton selectarrow(&settingpanel, { 370, 61 }, "arrowL", "arrowL.txt", 1, pmap1);



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
		if (GetAsyncKeyState(0x51) < 0)
		{
			break;
		}
		if (GetAsyncKeyState(VK_DOWN) < 0 && currentarrowpos < 1)
		{
			currentarrowpos++;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, arrowPos[currentarrowpos]});
			selectarrow.show();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && currentarrowpos > 0)
		{
			currentarrowpos--;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, arrowPos[currentarrowpos]});
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
	}
	selectarrow.show();

	FXvolume.unshow();
	FXsound.unshow();
	musicvolume.unshow();
	music.show();

	settingpanel.unshow();
}

int main() {
	br.show();

	cButton b1(&br, { 516, 55 }, "b1", "playbutton.txt", 1, b1F);
	cButton b2(&br, { 516, 90 }, "b2", "loadbutton.txt", 1, b2F);
	cButton b3(&br, { 516, 125 }, "b3", "settingbutton.txt", 1, b3F);

	cButton buttonlist[3] = { b1, b2, b3 };
	int x = 0;
	for (int i = 0; i < 3; i++)
	{
		buttonlist[i].show();
	}
	buttonlist[x].onSelect();

	while (running)
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
			br.show();
			for (int i = 0; i < 3; i++)
			{
				buttonlist[i].show();
			}
			buttonlist[x].onSelect();

		}
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
		Sleep(200);
	}
	buttonlist[x].onDeSelect();
	for (int i = 0; i < 3; i++)
	{
		buttonlist[i].unshow();
	}
	//b.unshow();
	////_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	////_CrtDumpMemoryLeaks();
	br.unshow();

	cleanGame();
}

