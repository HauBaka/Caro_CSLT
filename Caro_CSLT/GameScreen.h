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
#define BOARD_SIZE_HEIGHT 15
using namespace std; 
namespace fs = std::experimental::filesystem;
struct _POINT { int x, y, c; }; 
struct GAME {
	string name;
	bool turn;/*0: O, 1: X*/
	bool gamemode;/*0: PvP, 1: PvE*/
	short time;/*Thời gian còn lại*/
	short ratio[2];/*Tỉ số*/
	short hits[2];/*Số lượt đánh*/
	int _X, _Y;/*Vị trí con trỏ trên bảng*/
	vector<pair<short, short>> history;/*Lưu lại lịch xử đánh*/
	_POINT point[BOARD_SIZE_HEIGHT][BOARD_SIZE_WIDTH];/*Bảng*/
};

extern bool key_w, key_a, key_s, key_d, currentLang;

bool rowCheck(int, int, int&);
bool colCheck(int, int, int&);
bool leftDiagonalCheck(int, int, int&);
bool rightDiagonalCheck(int, int, int&);

void drawWinEffect(bool, int, int, int, int);
void drawContinueOption(bool);
bool checkWin();

bool fileExists(string);
bool saveGame();
bool loadGame(string);
void saveGameScreen(bool);
int loadAllSaves(vector<string>&);

bool DrawOption();
bool PauseOption();

void fixKeyboard();
void updateScreen();
void updateFullBoard();
void drawTheScreen();
void reRenderCursor(bool);

int getRandom(int, int);
bool botHitRandom();

bool boardTick();
bool inputProcessing(char);
void movementProcessing(char);
bool timeProcessing(int&);
void resetPosOnBoard();
void resetBoard();
void StartGame(bool, bool);

void setupGame(string, int, int, bool, bool, short, short[2], short[2], vector<pair<short, short>>);

string gameEditor_name(int, int, RGB, RGB, RGB);
void gameEditor_remove(string);
void loadSaveGameEditor(string, bool, int);

void newGameOptionsScreen();
void selectModeScreen();
void loadGameScreen();
void GameScreen(int);
#endif