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
	cDWindow br({ 0,0 }, "bg", "Sprites//menuBg.txt");
	br.show();
	cDWindow infortab({ 324, 0 }, "infortab", "Sprites//info.txt");
	cLabel scr(&infortab, { 10, 5 }, "src", "TOTAL SCORES", 1, Color::red);
	cLabel num(&infortab, { 10,15 }, "num", "999999999", 2, Color::red);
	infortab.show();
	scr.show();
	num.show();

	//cButton but(&pan , {10, 10}, "map1", "Sprites//jungleicon.txt", 2, oncl);
	//but.show();
	int i = 0;
	while (runing)
	{
		if (GetAsyncKeyState(0x51) < 0)
			break;
		Sleep(100);
		if (GetAsyncKeyState(0x0D) < 0)
		{
			scr.updateText("YOU LOSE");
		}
		


	}
	//b.unshow();
	////_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	////_CrtDumpMemoryLeaks();
	cGameEngine::cleanEngine();
}

