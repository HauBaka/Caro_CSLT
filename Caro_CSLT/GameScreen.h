#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_
#include "terminalUtils.h"
#include "ModelUtils.h"
#include <filesystem>
#include <vector>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
using namespace std; 

namespace fs = std::experimental::filesystem;
struct GAME {
	bool turn;//luot danh
	short time;
	short ratio[2];//ti so
	short hits[2];//so luot danh
	vector<pair<short, short>> history;//lich su danh
	vector<vector<int>> board;
	short board_heigh, board_width;
};
bool rowCheck(int , int , int );
bool colCheck(int , int , int);
bool leftDiagonalCheck(int, int, int);
bool rightDiagonalCheck(int, int, int);
bool checkWin(int, int&, int&);
void StartGame(int);
void GameScreen(int);
bool fileExists(string);
bool loadGame(string);
bool saveGame(string);
void setupGame(bool, short, short[2], short[2], vector<pair<short, short>>, vector<vector<int>>);
#endif
