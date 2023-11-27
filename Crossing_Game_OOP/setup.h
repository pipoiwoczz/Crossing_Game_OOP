#ifndef _SETUP_H
#define _SETUP_H
#define _CRT_SECURE_NO_WARNINGS
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>	


#include <iostream>	
#include <string>
#include <wchar.h>
#include <Windows.h>
#include <conio.h>
#include <direct.h>
#include <fstream>
#include <ctime>
#include <thread>
#include <wchar.h>
#include <future>
#include <vector>
#include <mutex>
#include <algorithm>
#include <mmsystem.h>
#include <future>

#pragma comment(lib, "winmm.lib")

//#ifdef _DEBUG
//#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_NEW
//#endif

using namespace std;

extern SMALL_RECT My_Windows;
extern SMALL_RECT PlayBoxRect;

extern const HANDLE mainHandle;
enum class Color {
	black = 0,
	blue = 1,
	green = 2,
	aqua = 3,
	red = 4,
	purple = 5,
	yellow = 6,
	white = 7,
	gray = 8,
	light_blue = 9,
	light_green = 10,
	light_aqua = 11,
	light_red = 12,
	light_purple = 13,
	light_yellow = 14,
	bright_white = 15,
};

enum class BGIndex {
	BGMenu = 0,
	Jungle = 1
};

enum class AnimalIndex {
	Lion = 0,
	Rhino = 1,
	Crocodile = 2
};

enum class VehicleIndex {
	Truck = 0,
	Heli = 1,
	Motorbike = 2
};
#endif
