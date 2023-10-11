#pragma once
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

#include "cAnimal.h"
#include "cVehicle.h"
#include "cPeople.h"
#include "cGame.h"

using namespace std;

const SMALL_RECT My_Windows = { 0, 0, 274, 66 };

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

	test = 0xA12929
};

void clearConsole();
void setWindowSize(short width, short height);
void DisableCtrButton(bool Close, bool Min, bool Max);
void showScrollBar(BOOL Show);
void fixConsoleWindow();
void gotoXY(int x, int y);

void textColor(int color);
void printCharacter(wstring content, COORD spot, Color textColor, Color backgroundColor, short maxlength = -1);
void printCenterCharacters(wstring content, Color textColor, Color backgroundColor, short y, SMALL_RECT box, short maxlength = -1);

void drawMainMenu(); 
void drawGame();
void drawFrame();
void drawCharacter(COORD pos);
void drawGameTitle();
void drawLosingTitle();
void moveTestting();

#endif