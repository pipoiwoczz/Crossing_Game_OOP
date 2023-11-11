#pragma once
#include "setup.h"

class Map {
private:
	COORD pos;
	short height, width;
	HANDLE h ;
	CHAR_INFO* bg;
public:

	Map();
	Map(string filename );
	Map(int map, int level);
	~Map() {
		delete[] bg;
		bg = NULL;
	};
	void draw();
	CHAR_INFO* getBG() {
		return bg;
	}
	short getWidth() {
		return width;
	}
	short getHeight() {
		return height;
	}
};