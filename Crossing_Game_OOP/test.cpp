#include "Graphics.h"
#include "cGame.h"
#include "gameEngine.h"
#include "cObstacle.h"
#include "cWidget.h"
#include "cAnimal.h"
#include "cVehicle.h"
#include "Sound.h"

int Sound::BGSoundVolume = 1000;
int Sound::EffectSoundVolume = 1000;
bool runing = true;
void oncl()
{
	runing = false;
}

vector<cObstacle*> cObstacle::objects;
cObstacle* cLion::bootstrapObjectcLion = cObstacle::addObject(new cLion());
cObstacle* cRhino::bootstrapObjectcRhino = cObstacle::addObject(new cRhino());
cObstacle* cCrocodile::bootstrapObjectcCrocodile = cObstacle::addObject(new cCrocodile());

cObstacle* cTruck::bootstrapObjectcTruck = cObstacle::addObject(new cTruck());
cObstacle* cHelicopter::bootstrapObjectcHelicopter = cObstacle::addObject(new cHelicopter());
cObstacle* cMotorbike::bootstrapObjectcMotorbike = cObstacle::addObject(new cMotorbike());


int main() {
	Graphic gr;
	cGameEngine::startEngine();
	cGameEngine::refreshBackGround(true);
	//cButton rq({ 30, 30 }, 1, oncl);
	//
	cGame a;
	a.MainGame();

	//while (runing)
	//{
	//	rq.drawButton(cGameEngine::curHandle);
	//	if (GetAsyncKeyState(0x51) < 0)
	//		break;
	//	if (GetAsyncKeyState(0x0D) < 0)
	//	{
	//		rq.drawBorder(cGameEngine::curHandle);
	//		Sleep(1000);
	//		rq.cleanButton(cGameEngine::curHandle);
	//		rq.onEnter();
	//	}
	//	Sleep(100);
	//}
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//_CrtDumpMemoryLeaks();
}

