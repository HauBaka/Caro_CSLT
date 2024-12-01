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
void RGBPrint(int, int, string, RGB, RGB);
void printColoredText(int, int, wstring, int, int);
void printColoredText(int, int, string, int, int);
void BetterDraw(int, int, string, int); 
void BetterDraw(int, int, wstring, int);

void drawLOGO(int, int);
void veMay(int, int); 

void drawPlayer(bool, bool, int, int, RGB, RGB);
void drawTurn(bool, int, int, RGB, RGB, RGB);
void drawGameBoard(int, int, int, int, RGB, RGB);

void drawStartButton(int, int);
void drawMainMenuButton(int, int);
void drawMainMenu_Play(int, int);
void drawMainMenu_Options(int, int);
void drawMainMenu_Authors(int, int);
void drawMainMenu_Out(int, int);
void drawTriagle(int, int, bool);

void drawPanel(int, int, int);
void removePanel(int, int, int);
void drawSlider(int, int, int, int);
void drawDOT(int, int);
void drawCheckBox(int, int, RGB);

void fill(RGB);

void drawInGameHeader(int, int);
void drawInGamePanel_1(int, int, RGB, RGB, RGB, RGB);
void drawInGamePanel_2(int, int, RGB, RGB, RGB, RGB);
void drawInGamePanel_3(int, int, RGB, RGB, RGB, RGB);
void drawInGamePanel_4(int, int, RGB, RGB, RGB, RGB);
void drawInGameKeyboard(int, int, char, bool, RGB, RGB);
void drawKeyCap(int, int, bool, RGB, RGB);
void drawInGameKeyboard(int, int, char, bool, RGB, RGB);
void drawMiniPopUp(int, int, RGB, RGB, RGB, RGB);
void drawDrawText(int, int, RGB);
void drawPauseText(int, int, RGB);

void drawPineTree(int, int, RGB, int);
void drawSnowFlake(int, int, RGB);
#endif