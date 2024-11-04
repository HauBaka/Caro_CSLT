#ifndef _MODELUTILS_H_
#define _MODELUTILS_H_
#include "string.h"
#include <iostream>
#include <conio.h>//_getch,...
#include <fcntl.h>//_O_WTEXT
#include <io.h>//_setmode
#include <Windows.h>
#define MaxSize 30
using namespace std;
struct RGB {
	int R, G, B;
};
extern RGB pink, white_pink, light_pink, black, white, default_white;

void RGBPrint(int, int, wstring, RGB, RGB, bool);
void printColoredText(int, int, wstring, int, int);
void printColoredText(int, int, string, int, int);
void BetterDraw(int, int, string, int); 
void BetterDraw(int, int, wstring, int);
void drawLOGO(int, int);
void veMay(int, int); 
void drawPlayer(bool, bool, int, int, int, int);
void drawTurn(bool, int, int);
void drawGameBoard(int, int, int, int);
void drawStartButton(int, int);
void drawMainMenu_Play(int, int, bool);
void drawMainMenu_Options(int, int, bool);
void drawMainMenu_Authors(int, int, bool);
void drawMainMenu_Out(int, int, bool);
void drawTriagle(int, int, bool);
void drawPanel(int, int, int);
void removePanel(int, int, int);
void drawSlider(int, int, int, int);
void drawDOT(int, int);
void drawCheckBox(int, int, RGB);
#endif