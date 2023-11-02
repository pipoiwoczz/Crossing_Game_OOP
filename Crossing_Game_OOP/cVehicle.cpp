#include "cVehicle.h"

vector<vector<unsigned char>> cTruck::textureTruck = loadTexture(truckFile);
vector<vector<unsigned char>> cHelicopter::textureHeli = loadTexture(heliFile);
vector<vector<unsigned char>> cMotorbike::textureMotorb = loadTexture(motorbFile);

cTruck::cTruck() : cTruck({ 0, 40 }, 1, 2) {};
cTruck::cTruck(COORD In_pos, int difficulty, int ttm): cVehicle(In_pos, difficulty, ttm) {
	wstring content[5];
	content[0] = L"  ▄███ ▄████████▄";
	content[1] = L" ▄█▒▒█▓██▒▒▒▒▒▒██";
	content[2] = L"██████▓██▒▒▒▒▒▒██";
	content[3] = L"██████▓██████████";
	content[4] = L" ▀🞕▀       ▀🞕🞕▀";

	texture.assign(content, content + 5);
}

cHelicopter::cHelicopter() : cHelicopter({ 0, 40 }, 1, 2) {};
cHelicopter::cHelicopter(COORD In_pos, int difficulty, int ttm): cVehicle(In_pos, difficulty, ttm) {
	wstring content[5];
	content[0] = L"▂▂▂▂▂▂▂▂▂▂▂▂";
	content[1] = L"      ▌     ";
	content[2] = L"	 ▄▀▀█▐█▄▄▃▃▃▃🞕";
	content[3] = L"	▀▄▄▄█▐█▀";
	content[4] = L" ▄▂▌▂▂▌▂▄";

	texture.assign(content, content + 5);
}

cMotorbike::cMotorbike() : cMotorbike({ 0, 40 }, 1, 2) {};
cMotorbike::cMotorbike(COORD In_pos, int difficulty, int ttm): cVehicle(In_pos, difficulty, ttm) {
	wstring content[5];
	content[0] = L"   ▄██▀";
	content[1] = L"   ▀▀██▄▓▓▓▄ ▄▄██▀▀";
	content[2] = L"▄▀▀▀██▓▓▓▓█████▀▀▀▄";
	content[3] = L"▌ ◾ ▐███▓▓▓▓██▌ ◾ ▐";
	content[4] = L"▀▄▄▄▀         █▄▄▄▀";

	texture.assign(content, content + 5);
}

//void cTruck::draw(COORD pos) {
//
//
//	for (int i = pos.Y; i < pos.Y + 5; i++) {
//		printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
//	}
//}	
//
//void cHelicopter::draw(COORD pos) {
//
//
//	for (int i = pos.Y; i < pos.Y + 5; i++) {
//		printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
//	}
//}
//
//void cMotorbike::draw(COORD pos) {
//
//
//	for (int i = pos.Y; i < pos.Y + 5; i++) {
//		printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
//	}
//}

