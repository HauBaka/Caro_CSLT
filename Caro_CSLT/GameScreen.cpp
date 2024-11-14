#include "GameScreen.h"
#include "FileConfiguration.h"
GAME game;
bool rowCheck(int value, int i, int j) {
	int count = 0;
	while (i < game.board_heigh && j < game.board_width) {
		if (game.board[i][j] == value) count++;
		else return count >= 5;
		j++;
	}
	return count >= 5;
}
bool colCheck(int value, int i, int j) {
	int count = 0;
	while (i < game.board_heigh) {
		if (game.board[i][j]==value) count++;
		else return count >= 5;
		i++;
	}
	return count >= 5;
}
bool leftDiagonalCheck(int value, int i, int j) {
	int count = 0;
	while (i < game.board_heigh && j < game.board_width) {
		if (game.board[i][j] == value) count++;
		else return count >= 5;
		i++;
		j++;
	}
	return count >= 5;
}
bool rightDiagonalCheck(int value, int i, int j) {
	int count = 0;
	while (i < game.board_heigh && j >= 0) {
		if (game.board[i][j] == value) count++;
		else return count >= 5;
		i++;
		j--;
	}
	return count >= 5;
}
bool checkWin(int value, int& xpos, int& ypos) {//0=None,1=X,2=O
	for (int i = 0; i < game.board_heigh; i++) {
		for (int j = 0; j < game.board_width; j++) {
			if (rowCheck(value, i, j)) {
				xpos = j;
				ypos = i;
				return 1;
			}
			if (colCheck(value, i, j)) {
				xpos = j;
				ypos = i;
				return 1;
			}
			if (leftDiagonalCheck(value, i, j)) {
				xpos = j;
				ypos = i;
				return 1;
			}
			if (rightDiagonalCheck(value, i, j)) {
				xpos = j;
				ypos = i;
				return 1;
			}
		}
	}
	return 0;
}
bool fileExists(string filename) {
	FILE* file;
	fopen_s(&file, ("./Saves/" + filename + ".txt").c_str(), "r");
	if (file) {
		fclose(file); 
		return 1;
	}
	return 0;
}
bool loadGame(string filename) {
	if (!fileExists(filename)) return 0;
	FILE* savef;
	fopen_s(&savef, ("./Saves/" + filename + ".txt").c_str(), "r");
	if (loadConfiguration(savef)) {
		game = {};
		game.board_heigh = 10; game.board_width = 15;
		wstring text;
	   //load time & turn
		game.time = getInt(savef, L"time-left");
		game.turn = getInt(savef, L"turn");
	   //load ratio
		text = getString(savef, L"ratio");
		for (int i = 0; i < text.size(); i++) if (text[i] == ' ') {
			game.ratio[0] = stoi(text.substr(0, i).c_str());
			game.ratio[1] = stoi(text.substr(i + 1));
			break;
		};
	   //load hits
		text = getString(savef, L"hits");
		for (int i = 0; i < text.size(); i++) if (text[i] == ' ') {
			game.hits[0] = stoi(text.substr(0, i).c_str());
			game.hits[1] = stoi(text.substr(i + 1));
			break;
		};
	   //load history
		for (int i = 0; i < 5; i++) {
			text = getString(savef, L"history-" + to_wstring(i + 1));
			if (text == L"No data") break;
			game.history.resize(i + 1);
			game.history[i].first = text[0];
			game.history[i].second = stoi(text.substr(1));
		};
		//load board
		game.board  = vector<vector<int>>(game.board_heigh, vector<int>(game.board_width));
		for (int i = 0; i < game.board_heigh; i++) {
			text = getString(savef, (wstring(L"board-line-") + ((i < 9) ? L"0" : L"") + to_wstring(i + 1)));
			for (int j = 0; j < game.board_width; j++) {
				game.board[i][j] = stoi(text.substr(2*j,1));
			}
		}
		return 1;
	}
	return 0;
}
bool saveGame(string filename) {
	if (fileExists(filename)) return 0;
	FILE* savef;
	fopen_s(&savef, ("./Saves/" + filename + ".txt").c_str(), "w");

	fprintf_s(savef, ("time-left: " + to_string(game.time) + "\n").c_str());
	fprintf_s(savef, (game.turn == 1) ? "turn: 1\n" : "turn: 0\n");
	fprintf_s(savef, ("ratio: "+to_string(game.ratio[0]) + " " + to_string(game.ratio[1]) + "\n").c_str());
	fprintf_s(savef, ("hits: " +to_string(game.hits[0]) + " " + to_string(game.hits[1]) + "\n").c_str());
	for (int i = 0; i < 5; i++) {
		fprintf_s(savef, ("history-" + to_string(i + 1) + ": ").c_str());
		fprintf_s(savef, (i < game.history.size()) ?
			(game.history[i].first + to_string(game.history[i].second) + "\n").c_str() :
			((string)"No data\n").c_str());
	}
	for (int i = 0; i < game.board_heigh; i++) {
		fprintf(savef, (string("board-line-") + ((i < 9) ? "0" : "") + to_string(i+1) + ": ").c_str());
		for (int j = 0; j < game.board_width; j++) {
			fprintf_s(savef, (to_string(game.board[i][j]) + " ").c_str());
		}
		fprintf_s(savef, "\n");
	}
	fclose(savef);
	return 1;
}
void StartGame(int mode) {
	system("cls");
	int loc_x = 7;//[0,14]
	int loc_y = 5;//[0,14]
	int length = 61, width = 21;//10x15 cells
	int x = 55, y = 17;

	printColoredText(80, 20, L"Ấn W/A/S/D để di chuyển", 13, 15);
	printColoredText(80, 21, L"Ấn 'ENTER' để đặt", 13, 15);
	printColoredText(80, 22, L"Ấn 'Q' để quay lại", 13   , 15);

	fill(white_pink);
	drawInGameHeader(3, 2);
	drawGameBoard(x, y, length, width);
	GameScreen(1);

	//nếu game đc nạp lại thì load cả board
	for (int i =0;i<game.board_heigh;i++) 
		for (int j =0;j<game.board_width;j++) printColoredText(x + 2 + j * 4, y + 2 * i + 1, (game.board[i][j] == 0 ? L" " : game.board[i][j] == 1 ? L"✖":L"⚫"), 0, 15);
	printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (game.board[loc_y][loc_x] == 0 ? L" " : game.board[loc_y][loc_x] == 1 ? L"✖" : L"⚫"), 0, 7);
	drawTurn(game.turn, 150, 10);
	bool check = false;
	while (true) {
		if (_kbhit()) {
			int n = _getch();
			char c =(char) tolower(n);
			if (c == 'q') {
				if (enableSFX) playSound(3, 0);
				break;
			}
			if (c == 'l') {
				saveGame("base1");
				break;
			}
			if (n == 13) {
				if (enableSFX) playSound(3, 0);
				if (check) continue;
				if (game.board[loc_y][loc_x] == 0) {
					game.board[loc_y][loc_x] = game.turn ? 1 : 2;
					printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (game.board[loc_y][loc_x] == 0 ? L" " : game.board[loc_y][loc_x] == 1 ? L"✖":L"⚫"), 0, 7);
					int x, y;
					if (game.turn) check = checkWin(1,x,y);
					else  check = checkWin(2, x, y);
					if (check) {
						if (game.turn) {
							printColoredText(30, 4, "X WONNNNNNNNNN", 4, 15);
						} else
							printColoredText(30, 4, "O WONNNNNNNNNN", 4, 15);
					}
					else {
						game.turn = !game.turn;
						drawTurn(game.turn, 150, 10);
					}
				}
			}
			else if (c=='w' or c=='a' or c=='s' or  c== 'd') {
				if (enableSFX) playSound(3, 0);
				printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (game.board[loc_y][loc_x] == 0 ? L" " : game.board[loc_y][loc_x] == 1 ? L"✖":L"⚫"),0,15);
				switch (c) {
				case 'w': 
					loc_y = (loc_y == 0) ? loc_y : loc_y - 1;
					break;
				case 'a':
					loc_x = (loc_x == 0) ? loc_x : loc_x - 1;
					break;
				case 'd':
					loc_x = (loc_x == game.board_width-1) ? loc_x : loc_x + 1;
					break;
				case 's':
					loc_y = (loc_y == game.board_heigh-1) ? loc_y : loc_y + 1;
					break;
				}
				//GotoXY(0, 0);
				//cout << "                            ";
				//GotoXY(0, 0);
				//cout << loc_y << "|" << loc_x;
				//for (int i = 0; i < game.board.size(); i++) {

				//	GotoXY(0, i+1);
				//	cout << game.board.size() << "-" << game.board[i].size();
				//}
				printColoredText(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (game.board[loc_y][loc_x] == 0 ? L" " : (game.board[loc_y][loc_x] == 1 ? L"✖":L"⚫")), 0, 7);
			}
		}
	}
	system("cls");
	drawLOGO((172 - 73) / 2, 5);
	GameScreen(0);
}
void setupGame(bool turn, short time, short ratio[2], short hits[2], vector<pair<char, short>> history, vector<vector<int>> board) {
	game.turn = turn;
	game.time = time;
	game.ratio[0] = ratio[0]; game.ratio[1] = ratio[1];
	game.hits[0] = hits[0]; game.hits[1] = hits[1];
	game.history = history;
	game.board = board;
	game.board_heigh = 10; game.board_width = 15;
}
void GameScreen(int state) {//0: PVP, 1: PVE, 2:Load,3:Save
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
				RGBPrint(126- ((int)options[previousSelect].length()) / 2, 23 + 2 * previousSelect, L"   "+options[previousSelect] + L"   ", { 255,255,255 }, { 255,129,216 }, true);
				RGBPrint(126 - ((int)options[currentSelect].length()) / 2, 23 + 2 * currentSelect, L">> " + options[currentSelect] + L" <<", { 255,255,255 }, { 255,129,216 }, true);
			}
		}
		switch (currentSelect) {
		case 0: {
			short a[2] = { 0 };
			vector<vector<int>> board = vector<vector<int>>(10, vector<int>(15));
			setupGame(0, 15, a, a, {}, board);
			StartGame(0);
			break;
		}
		case 1: 
			GameScreen(0);
			break;
		case 2:
			loadGame("base1");
			StartGame(0);
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