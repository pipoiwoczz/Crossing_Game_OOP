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

enum class MapTheme {
	Jungle = 0,
	Beach = 1,
	City = 2
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

class Time {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public:
	Time() {
		year = 0;
		month = 0;
		day = 0;
		hour = 0;
		minute = 0;
		second = 0;
	}

	void getTime() {
		time_t now = time(0);
		std::time_t currentTime = std::time(nullptr);

		// Initialize tm structure
		std::tm timeInfo = {};

		// Convert time_t to tm structure
		if (localtime_s(&timeInfo, &currentTime) == 0) {
			year = timeInfo.tm_year + 1900;
			month = timeInfo.tm_mon + 1;
			day = timeInfo.tm_mday;
			hour = timeInfo.tm_hour;
			minute = timeInfo.tm_min;
			second = timeInfo.tm_sec;
		}
		else {
			year = 0;
			month = 0;
			day = 0;
			hour = 0;
			minute = 0;
			second = 0;
		}
	}

	friend ostream& operator<<(ostream& ofs, const Time& time) {
		/*ofs.write((char*)&time.year, sizeof(int));
		ofs.write((char*)&time.month, sizeof(int));
		ofs.write((char*)&time.day, sizeof(int));
		ofs.write((char*)&time.hour, sizeof(int));
		ofs.write((char*)&time.minute, sizeof(int));
		ofs.write((char*)&time.second, sizeof(int));*/
		ofs << time.year << " " << time.month << " " << time.day << " " << time.hour << " " << time.minute << " " << time.second;
		return ofs;
	}

	friend istream& operator>>(istream& ifs, Time& time) {
		/*ifs.read((char*)&time.year, sizeof(int));
		ifs.read((char*)&time.month, sizeof(int));
		ifs.read((char*)&time.day, sizeof(int));
		ifs.read((char*)&time.hour, sizeof(int));
		ifs.read((char*)&time.minute, sizeof(int));
		ifs.read((char*)&time.second, sizeof(int));*/
		ifs >> time.year >> time.month >> time.day >> time.hour >> time.minute >> time.second;
		return ifs;
	}

	string timeToString() {
		string temp;
		temp = to_string(year) + "-" + to_string(month) + "-" + to_string(day) + "\n" + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
		return temp;
	}

	string dateString() {
		string temp;
		temp = to_string(year) + ":" + to_string(month) + ":" + to_string(day);
		return temp;
	}

	string timeString() {
		string temp;
		temp = to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
		return temp;
	}
};
#endif
