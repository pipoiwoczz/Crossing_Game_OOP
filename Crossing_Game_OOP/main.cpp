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

cDWindow br(&cWidget::window, { 0, 0 }, "bg", "menuBg.txt");

vector<Texture> cLilyleaf::textureLily = cAsset::assetLoaders(lilyFile);
vector<Texture> cLion::textureLion = cAsset::assetLoaders(lionFile);
vector<Texture> cRhino::textureRhino = cAsset::assetLoaders(rhinoFile);
vector<Texture> cCrocodile::textureCroco = cAsset::assetLoaders(crocoFile);
vector<Texture> cTruck::textureTruck = cAsset::assetLoaders(truckFile);
vector<Texture> cHelicopter::textureHeli = cAsset::assetLoaders(heliFile);
vector<Texture> cMotorbike::textureMotorb = cAsset::assetLoaders(motorbFile);
vector<Texture> cMotorbike::impactEffect = cAsset::assetLoaders(lionImpactEffect);
vector<Texture> cHelicopter::impactEffect = cAsset::assetLoaders(lionImpactEffect);
vector<Texture> cTruck::impactEffect = cAsset::assetLoaders(lionImpactEffect);
vector<Texture> cLion::impactEffect = cAsset::assetLoaders(lionImpactEffect);
vector<Texture> cCrocodile::impactEffect = cAsset::assetLoaders(lionImpactEffect);
vector<Texture> cRhino::impactEffect = cAsset::assetLoaders(lionImpactEffect);



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
	Sleep(2000);
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

