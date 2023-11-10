#include "Map.h"

Map::Map() {
	pos = { 0, 0 };
	height = 0;
	width = 0;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	bg = NULL;
}

Map::Map(string filename) {
	pos = { 0, 0 };
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	ifstream ifs;
	ifs.open(filename);
	ifs >> height >> width;
	bg = new CHAR_INFO[height * width];
	for (int i = 0; i < height * width; i++)
	{
		int x;
		ifs >> x;
		if (x == 16)
		{
			CHAR_INFO t = { L'b', 15 * 16 };
			bg[i] = t;
		}
		else {
			CHAR_INFO t = { L' ', x * 16 };
			bg[i] = t;
		}
	}
	ifs.close();

	// draw
	draw();
}

Map::Map(int map, int level) {
	string filename = "map" + to_string(map) + "_" + to_string(level) + ".txt";
	pos = { 0, 0 };
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	ifstream ifs;
	ifs.open(filename);
	ifs >> height >> width;
	bg = new CHAR_INFO[height * width];
	for (int i = 0; i < height * width; i++)
	{
		int x;
		ifs >> x;
		if (x == 16)
		{
			CHAR_INFO t = { L'b', 15 * 16 };
			bg[i] = t;
		}
		else {
			CHAR_INFO t = { L' ', x * 16 };
			bg[i] = t;
		}
	}
	ifs.close();


	draw();
}

void Map::draw() {
	// draw
	SMALL_RECT bgRect = { 0, 0, width - 1, height - 1 };
	WriteConsoleOutput(h, bg, { width, height }, { 0,0 }, &bgRect);
}