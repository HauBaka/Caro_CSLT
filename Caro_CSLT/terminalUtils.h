#ifndef _TERMINALUTILS_H_
#define _TERMINALUTILS_H_
#include <iostream>
#include <conio.h>//_getch,...
#include <fcntl.h>//_O_WTEXT
#include "MainScreen.h"
#include <io.h>//_setmode
#include "ModelUtils.h"
using namespace std;
void FixConsoleWindow();
void ShowConsoleCursor(bool);
void GotoXY(int, int);
void clearLine(int);
void drawOptions(int,int,string options[], int, int&, int&);
char getCharAtCoord(COORD);
void SetUpWindow();
#endif
