#include "Coin.h"

Coin::Coin(COORD In_pos) : cObstacle(In_pos, 0, false)
{
	Box = Hitbox(In_pos, { 1,1 });
	Box.move({ 0,1 });
	Box.move({ 0,-1 });
}
