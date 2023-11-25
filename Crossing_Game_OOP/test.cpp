#include "cGame.h"
#include "gameEngine.h"
#include "cObstacle.h"
#include "cWidget.h"
#include "cAnimal.h"
#include "cVehicle.h"
#include "Sound.h"
#include "Map.h"
vector<cObstacle*> cObstacle::objects;
cObstacle* cLion::bootstrapObjectcLion = cObstacle::addObject(new cLion());
cObstacle* cRhino::bootstrapObjectcRhino = cObstacle::addObject(new cRhino());
cObstacle* cCrocodile::bootstrapObjectcCrocodile = cObstacle::addObject(new cCrocodile());

cObstacle* cTruck::bootstrapObjectcTruck = cObstacle::addObject(new cTruck());
cObstacle* cHelicopter::bootstrapObjectcHelicopter = cObstacle::addObject(new cHelicopter());
cObstacle* cMotorbike::bootstrapObjectcMotorbike = cObstacle::addObject(new cMotorbike());
int Sound::BGSoundVolume = 1000;
int Sound::EffectSoundVolume = 1000;
bool runing = true;

void playN(void)
{
	cGame a;
	a.MainGame();
}
void oncl(void)
{
	//cPanel a(&cWidget::window, { 200,55 }, "choosemap", "mapPanel.txt");
	//a.show();
	//cButton map1({220, 60}, "mapjungle", "jungleicon.txt", 1, playN);
	//map1.show();
	//while (true)
	//{
	//	if (GetAsyncKeyState(0x51) < 0)
	//		break;
	//	if (GetAsyncKeyState(0x0D) < 0)
	//	{
	//		map1.onSelect();
	//		Sleep(250);
	//		map1.onEnter();
	//	}
	//}
	//map1.unshow();
	//a.unshow();
}


int main() {
	//Graphic gr;
	cGameEngine::startEngine();
	cWidget::createMainWindow("mainmenu");
	cDWindow br({ 0, 0 }, "bg", "Sprites//menuBg.txt");
	br.show();
	//cDWindow l1(&br, { 401, 55 }, "l1", "Sprites//playbutton.txt");
	//l1.show();
	cButton b1(&br, { 402, 55 }, "b1", "Sprites//playbutton.txt", 1, oncl);
	b1.show();
	cButton b2(&br, { 402, 90 }, "b2", "Sprites//loadbutton.txt", 1, oncl);
	b2.show();
	cButton b3(&br, { 402, 125 }, "b3", "Sprites//settingbutton.txt", 1, oncl);
	b3.show();
	//cButton but(&pan , {10, 10}, "map1", "Sprites//jungleicon.txt", 2, oncl);
	//but.show();
	cButton buttonlist[3] = { b1, b2, b3 };
	int i = 0;
	buttonlist[i].onSelect();
	while (runing)
	{
		if (GetAsyncKeyState(0x51) < 0)
			break;
		if (GetAsyncKeyState(0x0D) < 0)
		{
			Sleep(200);
			b1.onDeSelect();
		}
		if (GetAsyncKeyState(VK_UP) && i > 0)
		{
			buttonlist[i].onDeSelect();
			i--;
			buttonlist[i].onSelect();
		}
		if (GetAsyncKeyState(VK_DOWN) && i < 2)
		{
			buttonlist[i].onDeSelect();
			i++;
			buttonlist[i].onSelect();
		}
		Sleep(100);

		


	}
	//b.unshow();
	////_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	////_CrtDumpMemoryLeaks();
	cGameEngine::cleanEngine();
}

