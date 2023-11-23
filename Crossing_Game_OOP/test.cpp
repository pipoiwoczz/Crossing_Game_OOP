#include "Graphics.h"
#include "cGame.h"
#include "gameEngine.h"
#include "cObstacle.h"
#include "cWidget.h"
#include "cAnimal.h"
#include "cVehicle.h"
#include "Sound.h"
#include "Map.h"

int Sound::BGSoundVolume = 1000;
int Sound::EffectSoundVolume = 1000;
bool runing = true;
void oncl(void)
{
	cGame a;
	a.MainGame();
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
	//cGameEngine::refreshBackGround(true);
	//cButton rq({ 30, 30 }, 1, oncl);
	//
	Texture r = cAsset::assetLoader(menuBackGround);
	WriteConsoleOutput(cGameEngine::curHandle, r.textureArray, { r.getWidth(), r.getHeight() }, { 0,0 }, &My_Windows);

	cButton b({ 305, 55 }, 1, oncl);
	b.drawButton(cGameEngine::curHandle);
	while (runing)
	{
	//	rq.drawButton(cGameEngine::curHandle);
		if (GetAsyncKeyState(0x51) < 0)
			break;
		if (GetAsyncKeyState(0x0d) < 0)
		{
			b.drawBorder(cGameEngine::curHandle);
			Sleep(1000);
			b.cleanButton(cGameEngine::curHandle);
			b.onEnter();
		}
		Sleep(100);
	}
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//_CrtDumpMemoryLeaks();
}

