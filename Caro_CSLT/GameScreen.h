#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_
#include "terminalUtils.h"
bool rowCheck(int a[][15], int , int , int );
bool colCheck(int a[][15], int , int , int);
bool leftDiagonalCheck(int a[][15], int, int, int);
bool rightDiagonalCheck(int a[][15], int, int, int);
bool checkWin(int a[][15], int, int&, int&);
void StartGame(int);
void GameScreen(int);
#endif
