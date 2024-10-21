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
	while (i < 15) {
		if (a[i][j]) count++;
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
void drawPlayer(bool player, bool border, int x, int y, int color, int bgcolor) {
	if (player) {//turn x
		if (border) {
			printColoredText(x, y,     L"██╗  ██╗", color, bgcolor);
			printColoredText(x, y + 1, L"╚██╗██╔╝", color, bgcolor);
			printColoredText(x, y + 2, L" ╚███╔╝ ", color, bgcolor);
			printColoredText(x, y + 3, L" ██╔██╗ ", color, bgcolor);
			printColoredText(x, y + 4, L"██╔╝ ██╗", color, bgcolor);
			printColoredText(x, y + 5, L"╚═╝  ╚═╝", color, bgcolor);
		}
		else {
			printColoredText(x, y ,    L"         ", color, bgcolor);
			printColoredText(x, y+ 1,  L" ██   ██ ", color, bgcolor);
			printColoredText(x, y + 2, L"  ██ ██  ", color, bgcolor);
			printColoredText(x, y + 3, L"   ███   ", color, bgcolor);
			printColoredText(x, y + 4, L"  ██ ██  ", color, bgcolor);
			printColoredText(x, y + 5, L" ██   ██ ", color, bgcolor);
			printColoredText(x, y + 6, L"         ", color, bgcolor);
		}
	}
	else {
		if (border) {
			printColoredText(x, y,     L" ██████╗ ", color, bgcolor);
			printColoredText(x, y + 1, L"██╔═══██╗", color, bgcolor);
			printColoredText(x, y + 2, L"██║   ██║", color, bgcolor);
			printColoredText(x, y + 3, L"██║   ██║", color, bgcolor);
			printColoredText(x, y + 4, L"╚██████╔╝", color, bgcolor);
			printColoredText(x, y + 5, L" ╚═════╝ ", color, bgcolor);
		}
		else {
			printColoredText(x, y,     L"          ", color, bgcolor);
			printColoredText(x, y+1,   L"  ██████  ", color, bgcolor);
			printColoredText(x, y + 2, L" ██    ██ ", color, bgcolor);
			printColoredText(x, y + 3, L" ██    ██ ", color, bgcolor);
			printColoredText(x, y + 4, L" ██    ██ ", color, bgcolor);
			printColoredText(x, y + 5, L"  ██████  ", color, bgcolor);
			printColoredText(x, y + 6, L"          ", color, bgcolor);
		}
	}
}
void drawTurn(bool turn, int x, int y) {
	if (turn) {
		drawPlayer(true, true, x, y, 1, 14);//x
		printColoredText(x+1, y+6, "TURN X", 1, 14);
		drawPlayer(false, false, x, y+10, 9, 14);//o
	}
	else {
		drawPlayer(true, false, x, y, 9, 14);//x
		drawPlayer(false, true, x, y+10, 1, 14);//o
		printColoredText(x+1, y+10+5+1, "TURN O", 1, 14);
	}
}
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
	/////////
	printColoredText(80, 20, L"Ấn W/A/S/D để di chuyển", 13, 14);
	printColoredText(80, 21, L"Ấn 'SPACE' để đặt", 13, 14);
	printColoredText(80, 22, L"Ấn 'Q' để quay lại", 13   , 14);
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
			if (n == 32) {//space
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
							printColoredText(30, 4, "X WONNNNNNNNNN", 4, 14);
						} else
							printColoredText(30, 4, "O WONNNNNNNNNN", 4, 14);
					}
					else {
						turn = !turn;
						drawTurn(turn, 150, 10);
					}
				}
			}
			else if (c=='w' or c=='a' or c=='s' or  c== 'd') {
				if (enableSFX) playSound(3, 0);
				printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (board[loc_y][loc_x] == 0 ? " " : board[loc_y][loc_x] == 1 ? "X" : "O"),0,14);
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
void GameScreen(int state) {//state = 0: select mode, state = 1: in-game screen
	if (state == 0) {
		for (int i = 16; i < 30; i++) {
			clearLine(i);
		}
		string options[3] = {"Player vs Player", "Player vs Bot(Coming soon)", "BACK TO MAIN MENU"};
		int current = 0, previous = 0;
		drawOptions(options, 3, current, previous, 16);
		switch (current) {
		case 0:
			StartGame(0);
			break;
		case 1: 
			GameScreen(0);
			break;
		case 2:
			MainScreen(0,0);
			break;
		}
	}
	else if (state == 1) {
		//do st
	}
}