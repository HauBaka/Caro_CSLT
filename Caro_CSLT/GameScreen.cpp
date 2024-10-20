#include "GameScreen.h"
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
			printColoredText(x, y,     L"         ", color, bgcolor);
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
	int x = 10, y = 5, length = 61, width = 31;//15x15 cells
	drawGameBoard(x, y, length, width);
	GameScreen(1);
	//
	printColoredText(80, 30, "Press 'e' to go back", 1, 14);
	//
	int board[15][15] = { 0 };//1: X,2:O
	bool turn = true;//true:X, false: O
	int loc_x = 7;//[0,14]
	int loc_y = 7;//[0,14]
	printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (board[loc_x][loc_y] == 0 ? " " : board[loc_x][loc_y] == 1 ? "X" : "O"), 0, 7);
	drawTurn(turn, 150, 10);
	while (true) {
		if (_kbhit()) {
			int n = _getch();
			char c =(char) tolower(n);
			if (n == 101) {
				break;
			}
			if (n == 32) {//space
				if (board[loc_x][loc_y] == 0) {
					board[loc_x][loc_y] = turn ? 1 : 2;
					printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (board[loc_x][loc_y] == 0 ? " " : board[loc_x][loc_y] == 1 ? "X" : "O"), 0, 7);
					turn = !turn;
					drawTurn(turn, 150, 10);
				}
			}
			else {

				printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (board[loc_x][loc_y] == 0 ? " " : board[loc_x][loc_y] == 1 ? "X" : "O"),0,14);
				switch (c) {
				case 'w': //w
					loc_y = (loc_y == 0) ? loc_y : loc_y - 1;
					break;
				case 'a'://a
					loc_x = (loc_x == 0) ? loc_x : loc_x - 1;
					break;
				case 'd'://d
					loc_x = (loc_x == 14) ? loc_x : loc_x + 1;
					break;
				case 's'://s
					loc_y = (loc_y == 14) ? loc_y : loc_y + 1;
					break;
				case 'e':
					break;
				}
				printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (board[loc_x][loc_y] == 0 ? " " : (board[loc_x][loc_y] == 1 ? "X" : "O")), 0, 7);
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