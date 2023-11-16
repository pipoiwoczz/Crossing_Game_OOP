//#include "Map.h"
//
//vector<Texture> Map::listMap = loadMap();
//Texture* Map::currentMap = &Map::listMap[0];
//
//vector<Texture> Map::loadMap()
//{
//	ifstream mapIn;
//	vector<Texture> loadedMap;
//	for (string mapName: maplist)
//	{
//		mapIn.open(mapName);
//		if (mapIn.is_open()) {
//			Texture map;
//			mapIn >> map.height >> map.width;
//			map.textureArray = new CHAR_INFO[map.height * map.width];
//			for (int i = 0; i < map.height * map.width; i++)
//			{
//				int x;
//				mapIn >> x;
//				if (x == 16)
//				{
//					CHAR_INFO t = { L'b', 15 * 16 };
//					map.textureArray[i] = t;
//				}
//				else {
//					CHAR_INFO t = { L' ', x * 16 };
//					map.textureArray[i] = t;
//				}
//			}
//			mapIn.close();
//			loadedMap.push_back(map);
//		}
//	}
//	return loadedMap;
//}
//
//void Map::cleanup()
//{
//	for (int i = listMap.size() - 1; i >= 0; i--)
//	{
//		delete[] (listMap[i].textureArray);
//		listMap[i].textureArray = nullptr;
//	}
//}
//
////Map::Map() {
////	pos = { 0, 0 };
////	height = 0;
////	width = 0;
////	h = GetStdHandle(STD_OUTPUT_HANDLE);
////	bg = NULL;
////}
////
////Map::Map(string filename) {
////	pos = { 0, 0 };
////	h = GetStdHandle(STD_OUTPUT_HANDLE);
////	ifstream ifs;
////	ifs.open(filename);
////	ifs >> height >> width;
////	bg = new CHAR_INFO[height * width];
////	for (int i = 0; i < height * width; i++)
////	{
////		int x;
////		ifs >> x;
////		if (x == 16)
////		{
////			CHAR_INFO t = { L'b', 15 * 16 };
////			bg[i] = t;
////		}
////		else {
////			CHAR_INFO t = { L' ', x * 16 };
////			bg[i] = t;
////		}
////	}
////	ifs.close();
////
////	// draw
////	draw();
////}
////
////Map::Map(int map, int level) {
////	string filename = "map" + to_string(map) + "_" + to_string(level) + ".txt";
////	pos = { 0, 0 };
////	h = GetStdHandle(STD_OUTPUT_HANDLE);
////	ifstream ifs;
////	ifs.open(filename);
////	ifs >> height >> width;
////	bg = new CHAR_INFO[height * width];
////	for (int i = 0; i < height * width; i++)
////	{
////		int x;
////		ifs >> x;
////		if (x == 16)
////		{
////			CHAR_INFO t = { L'b', 15 * 16 };
////			bg[i] = t;
////		}
////		else {
////			CHAR_INFO t = { L' ', x * 16 };
////			bg[i] = t;
////		}
////	}
////	ifs.close();
////
////
////	draw();
////}
////
////void Map::draw() {
////	// draw
////	SMALL_RECT bgRect = { 0, 0, width , height };
////	WriteConsoleOutput(h, bg, { width, height }, { 0,0 }, &bgRect);
////}
