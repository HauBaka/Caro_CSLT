#ifndef _MODELUTILS_H_
#define _MODELUTILS_H_
#include "terminalUtils.h"
#include "string.h"
#define MaxSize 30
using namespace std;
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
#endif