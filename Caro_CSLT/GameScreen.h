#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_
#include "terminalUtils.h"
#include "ModelUtils.h"
#include <filesystem>
#include <vector>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include "FileConfiguration.h"
#include <wchar.h>
using namespace std; 

namespace fs = std::experimental::filesystem;
struct GAME {
	string name;
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

bool fileExists(string);
bool loadGame(string);
bool saveGame();
void saveGameScreen(bool);

void fixKeyboard();
void updateScreen();
void drawTheScreen();

void StartGame(bool);
void setupGame(string, bool, short, short[2], short[2], vector<pair<short, short>>, vector<vector<int>>);
int loadAllSaves(vector<string>&);
string gameEditor_name(int, int, RGB, RGB, RGB);
void gameEditor_remove(string);
void loadSaveGameEditor(string, bool);

void newGameOptionsScreen();
void selectModeScreen();
void loadGameScreen();
void GameScreen(int);
#endif
