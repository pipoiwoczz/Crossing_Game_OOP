#pragma once
#include "setup.h"
#include "cObstacle.h"
#include "Map.h"

class Tank : public cObstacle {
private:
	COORD pos;
	bool isMovingLeft = true;
	short charHH, charWH, charHV, charWV;
	CHAR_INFO* tankU;
	CHAR_INFO* tankD;
	CHAR_INFO* tankL;
	CHAR_INFO* tankR;
	HANDLE h;

public:
	Tank();
	Tank(COORD pos, int speed);
	~Tank() {
		delete[] tankU;
		delete[] tankD;
		delete[] tankR;
		delete[] tankL;
	};
	void move( Map &map);
	void moveLeft(Map& map);
	void moveRight(Map& map);

	void setSpeed(int speed) {
		this->speed = speed;
	}
	void setDirection(bool isMovingLeft) {
		this->isMovingLeft = isMovingLeft;
	}
};
