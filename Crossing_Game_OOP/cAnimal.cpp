#include "cAnimal.h"
#include "cAsset.h"
cAnimal::cAnimal(COORD In_pos, int difficult, AnimalIndex Aindex) : cEntity(In_pos)
{
    level = difficult;
    model = cAsset::getModel(Aindex);
    texture = cAsset::getTexture(Aindex);
    padding = cAsset::getPadding(Aindex);
    printer(model, texture, padding);
}

cAnimal::~cAnimal() {
    
    
}

cLion::cLion(COORD In_pos, int difficult) : cAnimal(In_pos, difficult, AnimalIndex::Lion)
{
    
}

cLion::~cLion()
{

}

void cLion::move(bool toRight)
{

}

short** cLion::getHitBoxX()
{
    /*short** hitBox = new short* [5];
    for (int i = 0; i < 5; i++) {
        hitBox[i] = new short[2];
    }
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
    return hitBox;*/
    return nullptr;
}

cRhino::cRhino(COORD In_pos, int difficult) : cAnimal(In_pos, difficult, AnimalIndex::Rhino)
{

}

cRhino::~cRhino()
{

}

void cRhino::move(bool toRight)
{

}
short** cRhino::getHitBoxX()
{
    return nullptr;
}
/*
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
                for (int i = 0; i < 5; i++) {
                    printCharacter(L" ", { short(temp.X), short(temp.Y + i) }, Color::bright_white, Color::bright_white);
                }
                temp.X++;
                lion[j].setPos(temp);
                //Sleep(5);
            }
        }
        //Sleep(200);
    }

}*/

/*
void cRhino::draw(COORD pos) {
    wstring content[5];

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
*/

cCrocodile::cCrocodile(COORD In_pos, int difficult) : cAnimal(In_pos, difficult, AnimalIndex::Crocodile)
{

}

cCrocodile::~cCrocodile()
{

}

void cCrocodile::move(bool toRight)
{

}

short** cCrocodile::getHitBoxX()
{
    return nullptr;
}
