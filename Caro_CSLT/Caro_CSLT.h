#ifndef _CARO_CSLT_H
#define _CARO_CSLT_H
#include <iostream>
using namespace std;
void  FixConsoleWindow();
void ShowConsoleCursor(bool showFlag);
void GotoXY(int x, int y);
void printColoredText(int x, int y, wstring text, int textColor, int bgColor);
void printColoredText(int x, int y, string text, int textColor, int bgColor);
#endif
