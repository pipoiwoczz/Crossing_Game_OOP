#include "cObstacle.h"

cObstacle::cObstacle(COORD In_pos, /* int difficulty, int ttm */ int speed) {
    center = In_pos;
    /*speed = difficulty;
    timeUntilMove = ttm;*/
    if (speed <= 0)
        speed = 1;
    this -> speed = speed;
    timeUntilMove = speed;
}

COORD cObstacle::getPos() {
    return center;
}

int cObstacle::getSpeed()
{
    return speed;
}

void cObstacle::setPos(COORD new_Pos) {
    center = new_Pos;
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

void cObstacle::draw() {
    COORD drawInit = { center.X - center.X / 2, center.Y - center.Y / 2 };
    for (int i = 0; i < texture.size(); i++) {
        printCharacter(texture[i], drawInit, Color::yellow, Color::bright_white);
        drawInit.Y++;
    }
}

void cObstacle::erase() {
    COORD eraseInit = { center.X - center.X / 2, center.Y - center.Y / 2 };
    for (int i = 0; i < texture.size(); i++) {
        wstring blank(texture[i].length(), '\0');
        printCharacter(blank, eraseInit, Color::bright_white, Color::bright_white);
        eraseInit.Y++;
    }   
}

void cObstacle::move() {
    erase();
    center.X += 3;
    for (auto box : boxes) {
        box.move({1, 0});
    }
    draw();
}
 

