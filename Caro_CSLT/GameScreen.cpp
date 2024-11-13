#include "GameScreen.h"

bool rowCheck(int a[][15], int value, int i, int j) {
	int count = 0;
	while (i < 15 && j < 15) {
		if (a[i][j] == value) count++;
		else return count >= 5;
		j++;
	}
	return count >= 5;
}
bool colCheck(int a[][15], int value, int i, int j) {
	int count = 0;
	while (j < 15) {
		if (a[i][j]==value) count++;
		else return count >= 5;
		i++;
	}
	return count >= 5;
}
bool leftDiagonalCheck(int a[][15], int value, int i, int j) {
	int count = 0;
	while (i < 15 && j < 15) {
		if (a[i][j] == value) count++;
		else return count >= 5;
		i++;
		j++;
	}
	return count >= 5;
}
bool rightDiagonalCheck(int a[][15], int value, int i, int j) {
	int count = 0;
	while (i < 15 && j >= 0) {
		if (a[i][j] == value) count++;
		else return count >= 5;
		i++;
		j--;
	}
	return count >= 5;
}
bool checkWin(int a[][15], int value, int& xpos, int& ypos) {//0=None,1=X,2=O
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (rowCheck(a, value, i, j)) {
				xpos = j;
				ypos = i;
				return 1;
			}
			if (colCheck(a, value, i, j)) {
				xpos = j;
				ypos = i;
				return 1;
			}
			if (leftDiagonalCheck(a, value, i, j)) {
				xpos = j;
				ypos = i;
				return 1;
			}
			if (rightDiagonalCheck(a, value, i, j)) {
				xpos = j;
				ypos = i;
				return 1;
			}
		}
	}
	return 0;
}
void StartGame(int mode) {
	system("cls");
	/////////
	printColoredText(80, 20, L"Ấn W/A/S/D để di chuyển", 13, 15);
	printColoredText(80, 21, L"Ấn 'ENTER' để đặt", 13, 15);
	printColoredText(80, 22, L"Ấn 'Q' để quay lại", 13   , 15);
	/////////
	int x = 10, y = 5, length = 61, width = 31;//15x15 cells
	drawGameBoard(x, y, length, width);
	GameScreen(1);
	//
	//
	int board[15][15] = { 0 };//1: X, 2: O
	bool turn = true;//true:X, false: O
	int loc_x = 7;//[0,14]
	int loc_y = 7;//[0,14]
	printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (board[loc_y][loc_x] == 0 ? " " : board[loc_y][loc_x] == 1 ? "X" : "O"), 0, 7);
	drawTurn(turn, 150, 10);
	bool check = false;
	while (true) {
		if (_kbhit()) {
			int n = _getch();
			char c =(char) tolower(n);
			if (c == 'q') {
				if (enableSFX) playSound(3, 0);
				break;
			}
			if (n == 13) {
				if (enableSFX) playSound(3, 0);
				if (check) continue;
				if (board[loc_y][loc_x] == 0) {
					board[loc_y][loc_x] = turn ? 1 : 2;
					printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (board[loc_y][loc_x] == 0 ? " " : board[loc_y][loc_x] == 1 ? "X" : "O"), 0, 7);
					int x, y;
					if (turn ) check = checkWin(board, 1,x,y);
					else  check = checkWin(board, 2, x, y);
					if (check) {
						if (turn) {
							printColoredText(30, 4, "X WONNNNNNNNNN", 4, 15);
						} else
							printColoredText(30, 4, "O WONNNNNNNNNN", 4, 15);
					}
					else {
						turn = !turn;
						drawTurn(turn, 150, 10);
					}
				}
			}
			else if (c=='w' or c=='a' or c=='s' or  c== 'd') {
				if (enableSFX) playSound(3, 0);
				printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (board[loc_y][loc_x] == 0 ? " " : board[loc_y][loc_x] == 1 ? "X" : "O"),0,15);
				switch (c) {
				case 'w': 
					loc_y = (loc_y == 0) ? loc_y : loc_y - 1;
					break;
				case 'a':
					loc_x = (loc_x == 0) ? loc_x : loc_x - 1;
					break;
				case 'd':
					loc_x = (loc_x == 14) ? loc_x : loc_x + 1;
					break;
				case 's':
					loc_y = (loc_y == 14) ? loc_y : loc_y + 1;
					break;
				}
				printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (board[loc_y][loc_x] == 0 ? " " : (board[loc_y][loc_x] == 1 ? "X" : "O")), 0, 7);
			}
		}
	}
	system("cls");
	drawLOGO((172 - 73) / 2, 5);
	GameScreen(0);
}
void GameScreen(int state) {//0: select mode,1: in-game screen
	if (state == 0) {
		drawPanel(100, 20, 5);

		wstring options[4] = {L"Player vs Player", L"Player vs Bot(Coming soon)", L"LOAD GAME", L"BACK TO MAIN MENU"};
		int currentSelect = 0, previousSelect = 0;
		int n, size = 4;
		for (int i = 0; i < size; i++) {
			if (i==0) RGBPrint(126 - ((int)options[i].length()) / 2, 23 + 2 * i, L">> " + options[i] + L" <<", {255,255,255}, { 255,129,216 }, true);
			else RGBPrint(126 - ((int)options[i].length()) / 2, 23 + 2 * i, L"   " + options[i] + L"   ", { 255,255,255 }, { 255,129,216 }, true);
		}
		while (true) {
			if (_kbhit()) {
				n = _getch();
				n = tolower(n);
				if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
				if (n == 13) break;
				previousSelect = currentSelect;
				if (n == 'w' or n == 'a') {//go up
					currentSelect--;
					currentSelect = (currentSelect < 0) ? size - 1 : currentSelect;
				}
				else if (n == 's' or n == 'd') {//go down
					currentSelect++;
					currentSelect = (currentSelect > size - 1) ? 0 : currentSelect;
				}
				//clearLine(y + 2 * previousSelect);
				RGBPrint(126- ((int)options[previousSelect].length()) / 2, 23 + 2 * previousSelect, L"   "+options[previousSelect] + L"   ", { 255,255,255 }, { 255,129,216 }, true);
				//clearLine(y + 2 * currentSelect);
				RGBPrint(126 - ((int)options[currentSelect].length()) / 2, 23 + 2 * currentSelect, L">> " + options[currentSelect] + L" <<", { 255,255,255 }, { 255,129,216 }, true);
			}
		}
		switch (currentSelect) {
		case 0:
			StartGame(0);
			break;
		case 1: 
			GameScreen(0);
			break;
		case 3:
			removePanel(100, 20, 5);
			MainScreen(0,0, false);
			break;
		}
	}
	else if (state == 1) {
		//do st
	}
}