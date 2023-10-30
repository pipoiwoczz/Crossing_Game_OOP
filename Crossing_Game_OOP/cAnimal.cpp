#include "setup.h"

void cLion::draw(COORD pos) {
    wstring content[5];
    content[0] = L"         ▄▓▓▓▓▓▄";
    content[1] = L" ▂▄██████▓▓▀▄▀▓▓";
    content[2] = L"▕ ███████▓▓▄█▄▓▓";
    content[3] = L"▕ ████████▓▓▓▓▓";
    content[4] = L" ▀ ▓█▄   ██▀▀▀";

    
    for (int i = pos.Y; i < pos.Y + 5; i++) {
        int temp = content[i - pos.Y].length() - 200 + pos.X;
        while (temp > 0) {
            content[i - pos.Y].pop_back();
            temp--;
        }
        printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::yellow, Color::bright_white);
        if (i == pos.Y) {
            printCharacter2(L"         ", { short(pos.X), short(i) }, Color::yellow, Color::bright_white);
        }
        else if (i == pos.Y + 4) {
            printCharacter2(L" ", { short(pos.X + 2), short(i) }, Color::yellow, Color::bright_white);
            printCharacter2(L"   ", { short(pos.X + 5), short(i) }, Color::yellow, Color::bright_white);
        }
        printCharacter2(L" ", { short(pos.X), short(i) }, Color::yellow, Color::bright_white);
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

void cLion::erase() {
    for (int i = 18; i >= 0; i--) {
        for (int j = 0; j < 5; j++) {
            printCharacter(L" ", { short(lX + i), short(lY + j) }, Color::bright_white, Color::bright_white);
        }
        Sleep(1);
    }
}

void cLion::move(COORD pos, cLion* lion) {
    int speed = level * 3;
    while (!isStop) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 7; j++) { // num of lions
                COORD temp = lion[j].getPos();
                lion[j].draw(temp);             
                if (temp.X >= 200) {
                    temp.X = -61;
                }
                temp.X++;
                lion[j].setPos(temp);
                
                //Sleep(5);
            }
        }
        //Sleep(200);
    }

}

short** cLion::getHitBoxX() {
    short** hitBox = new short* [5];
    for (int i = 0; i < 5; i++) {
        hitBox[i] = new short[2];
    }
    COORD pos = getPos();
    hitBox[0][0] = pos.X + 1;
    hitBox[0][1] = pos.X + 18;
    hitBox[1][0] = pos.X;
    hitBox[0][1] = pos.X + 19;
    hitBox[2][0] = pos.X;
    hitBox[0][1] = pos.X + 19;
    hitBox[3][0] = pos.X + 1;
    hitBox[0][1] = pos.X + 18;
    hitBox[4][0] = pos.X + 1;
    hitBox[0][1] = pos.X + 17;
    return hitBox;
}

void cRhino::draw(COORD pos) {
    wstring content[5];
    content[0] = L"             ▄▄  ";
    content[1] = L"▂▄███████▄█▄█▄██ ";
    content[2] = L"▎██████████▀█████";
    content[3] = L"▀ ███████████▀▀▀ ";
    content[4] = L"   ▓█▄   ▓█▄     ";
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
    wstring content[4];
    content[0] = L"            ▄ ▄ ▄  ▄▄ ▄▄       ";
    content[1] = L"▀▄▄    ▄▄▄██████████▄██▄█▀█▀█▀█";
    content[2] = L"  ▀▀██████████████████████▄█▄█ ";
    content[3] = L"           ▀█▄▀▄  ▀█▄▀█▄       ";
    for (int i = pos.Y; i < pos.Y + 4; i++) {
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
