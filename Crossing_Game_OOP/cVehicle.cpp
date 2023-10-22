#include "setup.h"

void cTruck::draw(COORD pos) {
	wstring content[5];
	content[0] = L"──────▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▌";
	content[1] = L"───▄▄██▌█░░░░░░░░░░░░▐";
	content[2] = L"▄▄▄▌▐██▌█░░░░░░░░░░░░▐";
	content[3] = L"███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▌";
	content[4] = L"▀❍▀▀▀▀▀▀▀❍❍▀▀▀▀▀▀❍❍▀";
	
	for (int i = pos.Y; i < pos.Y + 5; i++) {
		printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
	}
}	

void cHelicopter::draw(COORD pos) {
	wstring content[5];
	content[0] = L"▀▀▀▀█▀▀▀▀";
	content[1] = L"─▄▀█▀▀█──────▄";
	content[2] = L"█▄▄█▄▄██████▀";
	content[3] = L"▀▀█▀▀▀█▀▀";
	content[4] = L"─▀▀▀▀▀▀▀";
	for (int i = pos.Y; i < pos.Y + 5; i++) {
		printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
	}
}

void cMotorbike::draw(COORD pos) {
	wstring content[5];
	content[0] = L"";
	content[0] = L"───────────▀▄";
	content[1] = L"──█▄▄▄▄▄███▀▄─▄▄";
	content[2] = L"▄▀──▀▄─▀▀█▀▀▄▀──▀▄";
	content[3] = L"▀▄▀▀█▀▀████─▀▄──▄▀";
	content[4] = L"──▀▀──────────▀▀";
	for (int i = pos.Y; i < pos.Y + 5; i++) {
		printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
	}
}

