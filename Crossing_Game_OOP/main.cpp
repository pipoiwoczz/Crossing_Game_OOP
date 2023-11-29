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
bool enginecheck = cGameEngine::startEngine();
cWidget cWidget::window;
bool cWidget::hasWd = cWidget::createMainWindow("mainbg");

cDWindow br(&cWidget::window, { 0, 0 }, "bg","menuBg.txt");

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

	cDWindow settingpanel(&br, { 240,55 }, "settingpanel", "settingpanel.txt");
	cLabel music(&settingpanel, { 20, 15 }, "music", "Music Volume", 1, Color::black);
	cLabel musicvolume(&settingpanel, { 155,15 }, "musicvolume", "100", 1, Color::black);

	cLabel FXsound(&settingpanel, { 20, 45 }, "fx", "Effect Volume", 1, Color::black);
	cLabel FXvolume(&settingpanel, { 155, 45 }, "fxvolume", "100", 1, Color::black);

	cButton selectarrow(&settingpanel, { 190, 15 }, "arrowL", "arrowL.txt", 1, pmap1);

	short arrowPos[2] = { 15, 45 };

	cLabel ValueBar[2] = { musicvolume, FXvolume };

	int Value[2] = { 100, 100 };
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
			selectarrow.setPos({ selectarrow.getPos().X, 45 });
			selectarrow.show();
		}
		if (GetAsyncKeyState(VK_UP) < 0 && currentarrowpos > 0)
		{
			currentarrowpos--;
			selectarrow.unshow();
			selectarrow.setPos({ selectarrow.getPos().X, 15 });
			selectarrow.show();
		}
		if (GetAsyncKeyState(VK_LEFT) < 0 && Value[currentarrowpos] > 0)
		{
			Value[currentarrowpos] -= 25;
			ValueBar[currentarrowpos].updateText(to_string(Value[currentarrowpos]));
			Sleep(250);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0 && Value[currentarrowpos] < 100)
		{
			Value[currentarrowpos] += 25;
			ValueBar[currentarrowpos].updateText(to_string(Value[currentarrowpos]));
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

