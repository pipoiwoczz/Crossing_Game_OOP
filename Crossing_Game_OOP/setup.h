#ifndef _SETUP_H
#define _SETUP_H
#define _CRT_SECURE_NO_WARNINGS



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



using namespace std;

const string lionFile = "lion.txt";
const string rhinoFile = "rhino.txt";
const string crocoFile = "croco.txt";
const string truckFile = "truck.txt";
const string heliFile = "heli.txt";
const string motorbFile = "motorb.txt";

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

vector<vector<unsigned char>> loadTexture(string filename);

void gotoXY(int x, int y);

void printCharacter(wstring content, COORD spot, Color textColor, Color backgroundColor, short maxlength = -1);
void printCharacter2(wstring content, COORD spot, Color textColor, Color backgroundColor, short maxlength = -1);
void printCenterCharacters(wstring content, Color textColor, Color backgroundColor, short y, SMALL_RECT box, short maxlength = -1);

void clearConsole();

void drawMainMenu(int choice); 
void drawBorder(Color color);
void drawPlay(Color color);
void drawLoad(Color color);
void drawSetting(Color color);
void drawGameTitle();
void drawLosingTitle();


#endif