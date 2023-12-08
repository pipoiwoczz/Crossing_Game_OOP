#pragma once
#ifndef _C_COIN_H_
#define _C_COIN_H_

#include "cObstacle.h"

class Texture;

class Coin : public cObstacle
{
public:
	Coin(COORD In_pos);
	~Coin();

	void hitEffect(cPeople* pVictim);
	void hitSound();
};

#endif // !_C_COIN_H_