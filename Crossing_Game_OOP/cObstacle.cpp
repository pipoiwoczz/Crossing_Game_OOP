#include "cObstacle.h"

vector<cObstacle *> cObstacle::objects;

cObstacle * cObstacle::addObject (cObstacle * obj)
{
    if (obj == nullptr)
        return nullptr;
    objects.push_back(obj);
    return obj;
}

cObstacle * cObstacle::copyObject(char type, COORD pos)
{
    for (cObstacle * sample : objects)
    {
        if (type == sample -> getType())
            return sample -> copy(pos);
    }
    return nullptr;
}

cObstacle * cObstacle::constructObject(char type, COORD pos, int spd)
{
    for (cObstacle * sample : objects)
    {
        if (type == sample -> getType())
            return sample -> construct(pos, spd);
    }
    return nullptr;
}

void cObstacle::cleanBootstrap()
{
    for (cObstacle * sample : objects)
    {
        delete sample;
        sample = nullptr;
    }
    objects.clear();
}

cObstacle::cObstacle(COORD In_pos, /* int difficulty, int ttm */ int speed) {
    topleft = In_pos;
    /*speed = difficulty;
    timeUntilMove = ttm;*/
    if (speed <= 0)
        speed = 1;
    this -> speed = speed;
    timeUntilMove = speed;
}

COORD cObstacle::getPos() {
    return topleft;
}

int cObstacle::getSpeed()
{
    return speed;
}

void cObstacle::setPos(COORD new_Pos) {
    topleft = new_Pos;
    // use if neccessary - sets new hitbox according to new position
    //determineHitbox();
}

void cObstacle::determineHitbox() // default function to determine an obstacle's hitbox, can be overridden for each subclass
{
    boxes.clear();
    Hitbox a({short(topleft.X + 2), short(topleft.Y)}, {short(topleft.X + pTexture->getWidth() - 2), short(topleft.Y + pTexture->getHeight())});
    boxes.push_back(a);
}

bool cObstacle::collide(Hitbox h)
{
    for (Hitbox check : boxes)
        if (h.isOverlap(check))
            return true;
    return false;
}

void cObstacle::advanceTime(int time)
{
    if (isStop)
        return;
    
    timeUntilMove -= time;
    if (timeUntilMove <= 0)
    {
        move();
        timeUntilMove = speed;
    }
    
}

void cObstacle::move() {
    if (isStop) return;
    topleft.X = (topleft.X + 1) % (My_Windows.Right + 1);
    
    for (int i = 0; i < boxes.size(); i++)
    {
        boxes[i].set({ short(topleft.X + 10), short(topleft.Y + 10)}, { short((topleft.X + pTexture->getWidth() - 10) % My_Windows.Right), short((topleft.Y + pTexture->getHeight() - 10) % My_Windows.Bottom) });
    }

    /*if (topleft.X >= cAsset::currentMap->width)
    {
		topleft.X = -100;
        for (int i = 0; i < boxes.size(); i++)
            boxes[i].setHitHox(topleft.X);
        return;
	}*/

    
}
 

