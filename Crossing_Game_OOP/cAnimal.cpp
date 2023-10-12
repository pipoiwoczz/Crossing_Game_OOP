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

void cLion::move(COORD pos) {
    int speed = level * 3;
    for (short i = pos.X; i < 180; i++) {
        for (short j = 0; j < speed; j++) {
            draw({ short(i), pos.Y });
            Sleep(20);
            i++;
            lX++;
        }
        draw({ short(i), pos.Y });
        lX++;
        Sleep(200);
    }
}

void cLion::move(COORD pos, cLion* lion) {
    int speed = level * 3;
    while (!isStop) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 7; j++) {
                COORD temp = lion[j].getPos();
                draw(temp);
                temp.X++;
                lion[j].setPos(temp);
                //Sleep(5);
            }
        }
        //Sleep(200);
    }
	
}

void cRhino::draw(COORD pos) {
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

void cRhino::move(short y) {
	int speed = level * 3;
    for (int i = -20; i < 240; i++) {
        for (int j = 0; j < speed; j++) {
			draw({ short(i), y });
			Sleep(20);
			i++;
			rX++;
		}
		draw({ short(i), y });
		rX++;
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
