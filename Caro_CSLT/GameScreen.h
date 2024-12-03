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
#define BOARD_SIZE_WIDTH 15
#define BOARD_SIZE_HEIGHT 10
using namespace std; 
namespace fs = std::experimental::filesystem;
struct _POINT { int x, y, c; };
struct GAME {
	string name;
	bool turn;//0:O, 1:X
	bool gamemode;//0:pvp, 1: pve
	short time;
	short ratio[2];//ti so
	short hits[2];//so luot danh, 0:O, 1:X
	vector<pair<short, short>> history;//lich su danh
	//vector<vector<int>> board;//X:1,O:2
	_POINT point[BOARD_SIZE_HEIGHT][BOARD_SIZE_WIDTH];
};
bool rowCheck(int , int , int& );
bool colCheck(int , int , int&);
bool leftDiagonalCheck(int, int, int&);
bool rightDiagonalCheck(int, int, int&);
bool checkWin();
void drawContinueOption();
bool fileExists(string);
bool loadGame(string);
bool saveGame();
void saveGameScreen(bool);

void fixKeyboard();
void updateFullBoard();
void updateScreen();
void drawTheScreen();

void StartGame(bool);
void setupBoard();
void clearBoard();
void setupGame(string, bool, bool, short, short[2], short[2], vector<pair<short, short>>);
int loadAllSaves(vector<string>&);
string gameEditor_name(int, int, RGB, RGB, RGB);
void gameEditor_remove(string);
void loadSaveGameEditor(string, bool);

void newGameOptionsScreen();
void selectModeScreen();
void loadGameScreen();
void GameScreen(int);
#endif