#include "setup.h"
#include "cAsset.h"
#include "cEntity.h"
#include "cAnimal.h"
#include "cVehicle.h"
#include "cPeople.h"
#include "cGame.h"
#include <cmath>
char MOVING;
cGame cg;
bool isRunningDrawGame = true;

/*
void subThread2(cLion *lion) {
	(*lion).move(lion->getPos());
}

void subThread(cGame cg) {
	cg.drawGame();
}

void subThread3(cLion* lion, cPeople* people) {
	while (true) {
		if ((*people).isImpactOneLion(lion)) {
			drawFrame();
		}
	}
}

void threadTest() {
	if (isRunningDrawGame) 
	{
		cg.drawGame();
	}
	
}

void threadTest2(thread *t) {
	while (true) {
		if (cg.isImpact()) {
			break;
		}
	}
	cg.stopDrawAnimal();
	clearConsole();
	drawLosingTitle();
}*/

vector<wstring> cAsset::model_Lion;
vector<vector<TextureInfo>> cAsset::texture_Lion;
vector<int> cAsset::padding_Lion;

vector<wstring> cAsset::model_Rhino;
vector<vector<TextureInfo>> cAsset::texture_Rhino;
vector<int> cAsset::padding_Rhino;

vector<wstring> cAsset::model_Crocodile;
vector<vector<TextureInfo>> cAsset::texture_Crocodile;
vector<int> cAsset::padding_Crocodile;

vector<wstring> cAsset::model_Truck;
vector<vector<TextureInfo>> cAsset::texture_Truck;
vector<int> cAsset::padding_Truck;

vector<wstring> cAsset::model_Helicopter;
vector<vector<TextureInfo>> cAsset::texture_Helicopter;
vector<int> cAsset::padding_Helicopter;

vector<wstring> cAsset::model_Motorbike;
vector<vector<TextureInfo>> cAsset::texture_Motorbike;
vector<int> cAsset::padding_Motorbike;

int main() {
	system("cls");
	textSize(4);
	SetConsoleTitle(L"Crossing Road");
	fixConsoleWindow();
	showScrollBar(false);
	hideCursor(true);
	DisableCtrButton(false, true, true);
	disableUserSelection();
	drawGameTitle();
	cAsset a();

	cMotorbike te({ 20, 20 }, 1);
	return 1;
}