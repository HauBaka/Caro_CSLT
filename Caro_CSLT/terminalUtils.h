#ifndef _TERMINALUTILS_H_
#define _TERMINALUTILS_H_
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fcntl.h>
#include "MainScreen.h"
#include <io.h>
using namespace std;
void FixConsoleWindow();
void ShowConsoleCursor(bool showFlag);
void GotoXY(int x, int y);
void printColoredText(int x, int y, wstring text, int textColor, int bgColor);
void printColoredText(int x, int y, string text, int textColor, int bgColor);
void SetUpWindow();
void drawOptions(string options[], int size, int& currentSelect, int& previousSelect, int startLine);
void clearLine();
#endif
