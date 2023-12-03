#include "hitbox.h"


Hitbox::Hitbox() : Hitbox({ 0,0 }, { 0,0 }) {}
Hitbox::Hitbox(COORD tl, COORD br)
{
    topleft = tl;
    botright = br;
}

bool Hitbox::isOverlap(const Hitbox &h)
{
    if (topleft.Y > h.botright.Y || botright.Y < h.topleft.Y)
        return false;

    if (topleft.X <= botright.X)
    {
        if (h.topleft.X <= botright.X && h.topleft.X >= topleft.X)
            return true;
        if (h.botright.X >= topleft.X && h.botright.X <= botright.X)
            return true;
        return false;
    }
    else {
        if (h.topleft.X <= botright.X && h.topleft.X >= 0)
            return true;
        if (h.botright.X >= topleft.X && h.botright.X <= PlayBoxRect.Right)
            return true;
        return false;
    }

}

void Hitbox::getHitbox(COORD &topleftGet, COORD &botrightGet)
{
    topleftGet = topleft;
    botrightGet = botright;
}

void Hitbox::set(const COORD &newTopleft, const COORD &newBotright)
{
    topleft = newTopleft;
    botright = newBotright;
}
void Hitbox::move(const COORD& dPos)
{
    // move the hitbox by a vector defined by dPos. wraps around the screen if bound(s) are reached
    topleft.X = (topleft.X + dPos.X + PlayBoxRect.Right) % PlayBoxRect.Right;
    topleft.Y = (topleft.Y + dPos.Y + PlayBoxRect.Bottom) % PlayBoxRect.Bottom;
    botright.X = (botright.X + dPos.X + PlayBoxRect.Right) % PlayBoxRect.Right;
    botright.Y = (botright.Y + dPos.Y + PlayBoxRect.Bottom) % PlayBoxRect.Bottom;
}
