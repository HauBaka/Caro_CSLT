#include "GameScreen.h"

void drawGameBoard(int x, int y, int length, int width) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 && j == 0) printColoredText(x + i, y + j, L"╔", 3, 14);
			else if (i == 0 && j == width - 1) printColoredText(x + i, y + j, L"╚", 3, 14);
			else if (i == length - 1 && j == 0)  printColoredText(x + i, y + j, L"╗", 3, 14);
			else if (i == length - 1 && j == width - 1)  printColoredText(x + i, y + j, L"╝", 3, 14);
			else if ((i == 0 or i == length - 1) && (j != 0 && j != width - 1))  printColoredText(x + i, y + j, L"║", 3, 14);
			else if ((i != 0 && i != length - 1) && (j == 0 or j == width - 1))   printColoredText(x + i, y + j, L"═", 3, 14);
			else {
				if ((j % 2 == 1 && i % 4 == 1)) printColoredText(x + i, y + j, L"   │", 3, 14);
				if (j % 2 == 0 && i % 4 == 1) printColoredText(x + i, y + j, L"───┼", 3, 14);
			}
		}
	}
}
void StartGame(int mode) {
	system("cls");
	int x = 10, y = 5, length = 61, width = 31;//15x15 cells
	drawGameBoard(x, y, length, width);
	GameScreen(1);
	//
	int board[15][15];//1: X,2:O
	bool turn = true;//true:X, false: O
	int loc_x = 7;//[0,14]
	int loc_y = 7;//[0,14]
	while (true) {
		printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (board[loc_x][loc_y] == 0 ? " " : board[loc_x][loc_y] == 1 ? "X" : "O"), 0, 7);
		if (_kbhit()) {
			int n = _getch();
			char c = (char)n;
		}
	}
}
void GameScreen(int state) {//state = 0: select mode, state = 1: in-game screen
	if (state == 0) {
		for (int i = 16; i < 30; i++) {
			GotoXY(0, i);
			clearLine();
		}
		string options[3] = {"Player vs Player", "Player vs Bot(Coming soon)", "BACK TO MAIN MENU"};
		int current = 0, previous = 0;
		drawOptions(options, 3, current, previous, 16);
		switch (current) {
		case 0:
			StartGame(0);
			break;
		case 1: 
			break;
		case 2:
			MainScreen(0);
			break;
		}
	}
	else if (state == 1) {
		//do st
	}
}