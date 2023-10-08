#include "setup.h"

void cLion::draw(COORD pos) {
    wstring content[5];
    content[0] = L"  ▄▀▀▀▀▀───▄█▀▀▀█▄  ";
    content[1] = L" ▐▄▄▄▄▄▄▄▄██▌▀▄▀▐██ ";
    content[2] = L" ▐▒▒▒▒▒▒▒▒███▌▀▐███ ";
    content[3] = L"  ▌▒▓▒▒▒▒▓▒██▌▀▐██  ";
    content[4] = L"  ▌▓▐▀▀▀▀▌▓─▀▀▀▀▀   ";
    for (int i = pos.Y; i < pos.Y + 5; i++) {
        printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::yellow, Color::bright_white);
    }
}

void cLion::move(short y) {
    int speed = level * 3;
    for (int i = -20; i < 240; i++) {
        for (int j = 0; j < speed; j++) {
            draw({ short(i), y });
            Sleep(20);
            i++;
            lX++;
            lX++;
        }
        draw({ short(i), y });
        lX++;
        lY++;
        Sleep(200);
    }
}

void cRhyno::draw(COORD pos) {
	wstring content[5];
    content[0] = L"░░░░░░░░░░░░▄░░▄░▀█▄░░";
    content[1] = L"░░▄████████▄██▄██▄██░░";
    content[2] = L"░░█████████████▄████▌░";
    content[3] = L"░░▌████████████▀▀▀▀▀░░";
    content[4] = L"▒▀▒▐█▄▐█▄▐█▄▐█▄▒░▒░▒░▒";
    for (int i = pos.Y; i < pos.Y + 5; i++) {
        printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
    }
}

void cRhyno::move(short y) {
	int speed = level * 3;
    for (int i = -20; i < 240; i++) {
        for (int j = 0; j < speed; j++) {
			draw({ short(i), y });
			Sleep(20);
			i++;
			rX++;
			rY++;
		}
		draw({ short(i), y });
		rX++;
		rY++;
		Sleep(200);
	}
}

void cCrocodile::draw(COORD pos) {
	wstring content[5];
    content[0] = L"░░░░░▄▄▄▄▄░▄░▄░▄░▄";
    content[1] = L"▄▄▄▄██▄████▀█▀█▀█▀██▄";
    content[2] = L"▀▄▀▄▀▄████▄█▄█▄█▄█████";
    content[3] = L"▒▀▀▀▀▀▀▀▀██▀▀▀▀██▀▒▄██";
    content[4] = L"▒▒▒▒▒▒▒▒▀▀▒▒▒▒▀▀▄▄██▀▒";
    for (int i = pos.Y; i < pos.Y + 5; i++) {
        printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
    }
}


void cCrocodile::move(short y) {
	int speed = level * 3;
    for (int i = 240; i > -20; i--) {
        for (int j = 0; j < speed; j++) {
			draw({ short(i), y });
			Sleep(20);
			i--;
			cX++;
			cY++;
		}
		draw({ short(i), y });
		cX++;
		cY++;
		Sleep(200);
	}
}
