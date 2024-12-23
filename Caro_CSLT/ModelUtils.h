#ifndef _MODELUTILS_H_
#define _MODELUTILS_H_
#include "string.h"
#include <iostream>
#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
#define MaxSize 30
using namespace std;
struct RGB {
	int R, G, B;
};
extern RGB aqua, white_aqua, light_aqua, black, white, default_white;
extern RGB rainbows[16];
void RGBPrint(int, int, wstring, RGB, RGB, bool);
void RGBPrint(int, int, string, RGB, RGB);
void drawSmallSantaHat(int, int);
void drawLOGO(int, int);
void veMay(int, int); 

void drawPlayer(bool, bool, int, int, RGB, RGB);
void drawTurn(bool, int, int, RGB, RGB, RGB);
void drawGameBoard(int, int, int, int, RGB, RGB);

void drawMainMenuButton(int, int);
void drawMainMenu_Play(int, int);
void drawMainMenu_Options(int, int);
void drawMainMenu_Help(int, int);
void drawMainMenu_Authors(int, int);
void drawMainMenu_Out(int, int);
void drawTriagle(int, int, bool);

void drawPanel(int, int, int);
void removePanel(int, int, int);
void drawSlider(int, int, int, int, RGB);
void drawDOT(int, int, RGB);
void drawCheckBox(int, int, RGB, RGB);

void fill(RGB);

void drawInGameEscPanel(int, int);
void drawInGameEscPanel_Settings(int, int);
void drawInGameHeader(int, int);
void drawInGamePanel_1(int, int, RGB, RGB, RGB, RGB);
void drawInGamePanel_1A(int, int, RGB, RGB, RGB, RGB);
void drawInGamePanel_2(int, int, RGB, RGB, RGB, RGB);
void drawInGamePanel_3(int, int, RGB, RGB, RGB, RGB);
void drawInGamePanel_4(int, int, RGB, RGB, RGB, RGB);
void drawInGamePanel_5(int, int, RGB, RGB, RGB, RGB);
void drawInGameKeyboard(int, int, char, bool, RGB, RGB);
void drawKeyCap(int, int, bool, RGB, RGB);
void drawInGameKeyboard(int, int, char, bool, RGB, RGB);
void drawMiniPopUp(int, int, RGB, RGB, RGB, RGB);
void drawDrawText(int, int, RGB);
void drawPauseText(int, int, RGB);
void drawPineTree(int, int, RGB, int);
void drawSnowFlake(int, int, RGB);
void drawGift(int, int, RGB);
void drawCandy(int, int, RGB);
void drawReindeer(int, int, RGB);
void drawPineTree2(int, int, RGB);
void drawSanta(int, int, RGB);
void drawSnowman(int, int, RGB);
#endif