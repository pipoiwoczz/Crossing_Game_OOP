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

//void cObstacle::draw() {
//    //chrono::time_point<chrono::high_resolution_clock> start, end;
//    //start = chrono::high_resolution_clock::now();
//
//    //TYPE 1:
//
//    //SMALL_RECT reg = { topleft.X, topleft.Y, topleft.X + pTexture->width - 1, topleft.Y + pTexture->height - 1 };
//    //for (int i = 0; i < pTexture->blankTexture.size(); i++)
//    //{
//    //    for (int j = 0; j < pTexture->blankTexture[i].size(); j++)
//    //    {
//    //        int copysize = (pTexture->blankTexture[i][j].end - pTexture->blankTexture[i][j].start + 1);
//    //        int offsetplayer = i * pTexture->width + pTexture->blankTexture[i][j].start;
//    //        int offsetBackground = (topleft.Y + i) * cAsset::currentMap->width + topleft.X + pTexture->blankTexture[i][j].start;
//    //        memcpy(pTexture->textureArray + offsetplayer, cAsset::currentMap->mapArray + offsetBackground, copysize * sizeof(CHAR_INFO));
//    //    }
//    //}
//    //WriteConsoleOutput(mainHandle, pTexture->textureArray, { pTexture->width, pTexture->height }, { 0,0 }, &reg);
//
//    //TYPE 2:
//    
//    cGameEngine::setBuffer(*pTexture);
//    cGameEngine::
//    CHAR_INFO* readyBuffer = new CHAR_INFO[pTexture->width * pTexture->height];
//    memcpy(readyBuffer, pTexture->textureArray, pTexture->width * pTexture->height * sizeof(CHAR_INFO));
//
//    for (int i = 0; i < pTexture->width * pTexture->height; i++)
//    {
//        if (readyBuffer[i].Char.UnicodeChar == L' ') {
//            readyBuffer[i].Attributes = gameMap::currentMap->mapArray[(topleft.Y + i / pTexture->width) * gameMap::currentMap->width + topleft.X + (i % pTexture->width)].Attributes;
//        }
//    }
//    SMALL_RECT reg = { topleft.X, topleft.Y, topleft.X + pTexture->width - 1, topleft.Y + pTexture->height - 1 };
//    WriteConsoleOutput(mainHandle, readyBuffer, { pTexture->width, pTexture->height }, { 0,0 }, &reg);
//    delete[]readyBuffer;
//
//    currentFrame = (currentFrame + 1) % nFrame;
//    pTexture = pLTexture + currentFrame;
//
//    //end = chrono::high_resolution_clock::now();
//
//    //chrono::duration<double> cost = end - start;
//    //	cout << cost.count() << endl;
//    //    topleft.X += 1;
//    ////Texture* curBg = cAsset::getCurrentMap();
//    //CHAR_INFO* readyBuffer = new CHAR_INFO[pTexture->width * pTexture->height];
//    //memcpy(readyBuffer, pTexture->textureArray, pTexture->width * pTexture->height * sizeof(CHAR_INFO));
//
//    //for (int i = 0; i < pTexture->width * pTexture->height; i++)
//    //{
//    //    if (readyBuffer[i].Char.UnicodeChar == L'b') {
//    //        readyBuffer[i].Char.UnicodeChar = L' ';
//    //        readyBuffer[i].Attributes = cAsset::currentMap->textureArray[(topleft.Y + i / pTexture->width) * cAsset::currentMap->width + topleft.X + (i % pTexture->width)].Attributes;
//    //    }
//    //}
//    //SMALL_RECT reg = { topleft.X, topleft.Y, topleft.X + pTexture->width - 1, topleft.Y + pTexture->height - 1 };
//    //WriteConsoleOutput(mainHandle, readyBuffer, { pTexture->width, pTexture->height }, { 0,0 }, &reg);
//    //delete[]readyBuffer;
//}

void cObstacle::move() {
    if (isStop) return;
    topleft.X = (topleft.X + 1) % My_Windows.Right;
    
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
 

