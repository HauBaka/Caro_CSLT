#ifndef _CARO_CSLT_H
#define _CARO_CSLT_H
#include "terminalUtils.h"
#include "IntroScreen.h"
using namespace std;
void  FixConsoleWindow();
void ShowConsoleCursor(bool);
void GotoXY(int, int );
void printColoredText(int, int, wstring, int, int);
void printColoredText(int, int, string, int, int);
#endif
