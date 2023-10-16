#include "position.hpp"

void Position::getCoordinates(int &x, int &y)
{
    x = coordX;
    y = coordY;
}

void Position::setCoordinates(int x, int y)
{
    coordX = x;
    coordY = y;
}
