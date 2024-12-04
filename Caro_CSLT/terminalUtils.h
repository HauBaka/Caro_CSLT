#ifndef _TERMINALUTILS_H_
#define _TERMINALUTILS_H_
#include <iostream>
#include <conio.h>//_getch,...
#include <fcntl.h>//_O_WTEXT
#include "MainScreen.h"
#include <io.h>//_setmode
#include "ModelUtils.h"
#include "Caro_CSLT.h"
#include "FileConfiguration.h"
using namespace std;
void FixConsoleWindow();
void ShowConsoleCursor(bool);
void GotoXY(int, int);
void clearLine(int);
void SetUpWindow();
#endif
